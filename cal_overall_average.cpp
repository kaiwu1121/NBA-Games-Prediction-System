#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
//#include "team_id_processing.cpp"
//#include "data_IO.cpp"
//#include "feature_label_processing.cpp"

using namespace std;

std::vector<std::vector<double> > overall_preprocessing (std::vector<std::vector<double> >& data_matrix) {
	int rows = data_matrix.size();
	int cols = data_matrix[0].size();
	std::vector<std::vector<double> > pre_data;
	pre_data.resize(rows, std::vector<double>(cols, 0));
	std::vector<double> sum;	
	sum.resize(cols,0);
	for (int i = 0; i < rows; i++) {	
		for (int j = 0 ; j < cols; j++) {
			if (j == 0 || j == 1 || j == 2) {
				pre_data[i][j] = data_matrix[i][j];
			} else {
				if (i == 0) {
					sum[j] = 0;
					pre_data[i][j] = sum[j];
				} else {
					sum[j] += data_matrix[i - 1][j];
					pre_data[i][j] = sum[j] / i;
				}	
			}
		}
	}
	return pre_data;
}

void overall_average_processing (const std::string &year, const std::string &team) {
	string input_dir = "formation_data";
	string output_dir = "overall_data";
    	string fileformat = ".csv";	
  	string input_filename = input_dir + "/" + year + "/" + year + team + "_formation" +fileformat;
	string output_filename = output_dir + "/" + year + "/" + year + team + "_overall" +fileformat;
	std::vector<std::vector<double> > data_matrix_formation = file_read_formation_double (input_filename);
	std::vector<std::vector<double> > overall_data = overall_preprocessing (data_matrix_formation);
	file_write_formation_double (output_filename, overall_data);
}
/*
int main (){
	string year = "2014";
	string team = "GSW";
	overall_average_processing (year, team); 
    return 1;
}*/

// g++ -std=c++11 -Wall main.cpp -o main
