#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
//#include "team_id_processing.cpp"
//#include "month_id_processing.cpp"
//#include "data_IO.cpp"
//#include "data_formation.cpp"


using namespace std;

double find_max_min(std::vector<double> &A) {
	double max_value = A[0];
	double min_value = A[0];
	for (unsigned i = 0; i < A.size(); i++) {
		if (max_value < A[i]) {
			max_value = A[i];
		}
		if (min_value > A[i]) {
			min_value = A[i];
		}
	}
	return max_value - min_value;
}

double find_min(std::vector<double> &A) {
	double min_value = A[0];
	for (unsigned i = 0; i < A.size(); i++) {
		if (min_value > A[i]) {
			min_value = A[i];
		}
	}
	return min_value;
}

double find_max(std::vector<double> &A) {
	double max_value = A[0];
	for (unsigned i = 0; i < A.size(); i++) {
		if (max_value < A[i]) {
			max_value = A[i];
		}
	}
	return max_value;
}

void standardization(std::string &year,std::string &team, std::vector<std::vector<double> >& feature_data) {
	string fileformat = ".csv";
	string meanFile = "norm_data/" + year + "/" + year + team +"_mean" + fileformat;
	string stddevFile = "norm_data/" + year + "/" + year + team +"_stddev" + fileformat;
	std::vector<std::vector<double> > mean_data =  file_read_formation_double (meanFile);
	std::vector<std::vector<double> > stddev_data =  file_read_formation_double (stddevFile);
	for (unsigned i = 0; i < feature_data.size(); i++) {
		for (unsigned j = 0; j < feature_data[i].size(); j++) {
			feature_data[i][j] = (feature_data[i][j] - mean_data[j][0]) / stddev_data[j][0];
		}
	}
	string output = "norm_data/" + year + "/" + year + team +"_standardization" + fileformat;
	file_write_formation_double (output, feature_data);
}

void state_processing (std::string &year,std::string &team) {
	string input = "feature_data";
	string output = "state_data";
	string fileformat = ".csv";
	string inputfile = input + "/" + year + "/" + year + team +"_feature" + fileformat;
	string outputfile = output + "/" + year + "/" + year + team + "_state" + fileformat;
	// get feature data only
	std::vector<std::vector<double> > feature_data =  file_read_formation_double (inputfile);
	standardization(year, team, feature_data);
	//std::vector<std::vector<int> > binary_data;
	int rows = feature_data.size();
	int cols = feature_data[0].size();
	//binary_data.resize(rows, std::vector<int>(cols, 0));
	/*for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (feature_data[i][j] > 0) {
				binary_data[i][j] = 1;
			} else {
				binary_data[i][j] = 0;
			}
			
		}
	}*/
	//file_write_formation_int (outputfile, binary_data);
	for (int i = 0; i < cols; i++) {
		//observed sequence data
		std::vector<double> col_data;
		col_data.resize(rows - 1,0);
		for (int j = 0; j < rows - 1; j++) {
			col_data[j] = round(feature_data[j][i]);
		}
		//move equal to 0
		double min_value_seq = find_min(col_data);
		for (int j = 0; j < rows - 1; j++) {
			//double data = feature_data[j][i] - min_value_seq;
			col_data[j] -= min_value_seq;
		}
		string output_col = output + "/" + year + "/" + year + team + "_state_col" + std::to_string(i) + fileformat;
		file_write_formation_double_col (output_col, col_data);

		//label data	
		std::vector<double> label_data;
		label_data.resize(rows - 1,0);
		for (int j = 1; j < rows; j++) {
			//double data = feature_data[j][i] - min_value;
			label_data[j - 1] = round(feature_data[j][i] );
		}
		double min_value_label = find_min(label_data);
		for (int j = 1; j < rows; j++) {
			//double data = feature_data[j][i] - min_value;
			label_data[j - 1] -= min_value_label;
		}
		//std::cout<<min_value<<endl;
		string output_label = output + "/" + year + "/" + year + team + "_state_label_col" + std::to_string(i) + fileformat;
		file_write_formation_double_col (output_label, label_data);
		
		//number of state on each feature
		std::vector<double> diff;
		diff.resize(5,0);
		diff[0] = find_max_min(label_data);
		diff[1] = find_max(label_data) + 1;
		diff[2] = ceil(fabs(diff[0]));
		diff[3] = min_value_seq;
		diff[4] = min_value_label;
		string output_diff_col = output + "/" + year + "/" + year + team + "_state_diff_col" + std::to_string(i) + fileformat;
		file_write_formation_double_col (output_diff_col, diff);
	}
}

/*
int main (){
	string year = "2014";
	//string team = "GSW";
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		state_processing(year, team[i]);
	}
    return 1;
}*/
