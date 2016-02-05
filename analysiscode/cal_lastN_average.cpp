#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
//#include "team_id_processing.cpp"
//#include "month_id_processing.cpp"
//#include "data_IO.cpp"
//#include "feature_label_processing.cpp"

using namespace std;

std::vector<std::vector<double> > lastN_processing (std::vector<std::vector<double> >& data_matrix, int N) {
  int rows = data_matrix.size();
  int cols = data_matrix[0].size();
  std::vector<std::vector<double> > lastN_data;
  lastN_data.resize(rows, std::vector<double> (cols, 0));
  std::vector<double> sum_lastN_less;
  sum_lastN_less.resize(cols, 0);
  std::vector<double> sum_lastN;
  sum_lastN.resize(cols, 0);
  for (int i = 0; i < rows; i++) {
	if (i < N){
		for(int j = 0; j < cols; j++){
			if (i == 0) {
				if (j < 3) {
					sum_lastN_less[j] = data_matrix[i][j];
				} else {
					sum_lastN_less[j] = 0;
				}
				lastN_data[i][j] = sum_lastN_less[j];
			} else {
				if (j < 3) {
					lastN_data[i][j] = data_matrix[i][j]; 
				} else {
					sum_lastN_less[j] += data_matrix[i - 1][j];
					lastN_data[i][j] = sum_lastN_less[j] / i;	
				} 
			}
		}		
	} else {
		std::fill(sum_lastN.begin(), sum_lastN.end(), 0);
		for (int index = i - N; index < i; index ++) {
			for (int j = 0; j < cols; j++) {
				if (j >= 3) {
					sum_lastN[j] += data_matrix[index][j];
				}
			}
		}
		for(int j = 0; j < cols; j++){
			if (j < 3) {
				lastN_data[i][j] = data_matrix[i][j];
			} else {
				lastN_data[i][j] = sum_lastN[j] / N; 
			}
		}

	}
  }
  return lastN_data;
}

std::vector<std::vector<double> > lastN_rate (std::vector<std::vector<double> >& data_matrix) {
	std::vector<std::vector<double> > lastN;
	lastN.resize(data_matrix.size(), std::vector<double>(4,0));
	for (unsigned i = 0; i < data_matrix.size(); i++) {
		for (unsigned j = 0; j < 4; j++) {
			if (j == 3) {
				lastN[i][j] = data_matrix[i][data_matrix[i].size() - 1];
			} else {
				lastN[i][j] = data_matrix[i][j];				
			}
		}
	}
	return lastN;
}

void lastN_average_processing (const std::string &year, const std::string &team, int N) {
	string input_dir = "formation_data";
	string output_dir = "lastN_data";
    	string fileformat = ".csv";	
  	string input_filename = input_dir + "/" + year + "/" + year + team + "_formation" +fileformat;
	string output_filename = output_dir + "/" + year + "/" + year + team + "_last_" + std::to_string(N) + fileformat;
	std::vector<std::vector<double> > data_matrix_formation = file_read_formation_double (input_filename);
	std::vector<std::vector<double> > lastN_data = lastN_processing (data_matrix_formation, N);
	file_write_formation_double (output_filename, lastN_data);
	std::vector<std::vector<double> > lastN = lastN_rate (lastN_data); 
	string lastNFile = output_dir + "/" + year + "/" + year + team + "_lastN" + fileformat;
	file_write_formation_double (lastNFile, lastN);
}

/*
int main (){
	string year = "2014";
	//string team = "GSW";
	int N = 8;
	//lastN_average_processing (year, team, N);
		std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		lastN_average_processing (year, team[i], N);
	}
    return 1;
}
*/
// g++ -std=c++11 -Wall main.cpp -o main
