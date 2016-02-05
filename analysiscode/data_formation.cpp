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

std::vector<std::vector<double> > data_calculation (std::vector<std::vector<double> >& raw_data) {
	std::vector<std::vector<double> > data_matrix;
	data_matrix.resize(raw_data.size(), std::vector<double>(9,0));
	for (unsigned i = 0; i < data_matrix.size(); i++) {
		//date		
		data_matrix[i][0] = raw_data[i][2];
		//v/h		
		data_matrix[i][1] = raw_data[i][0];	
		//opp		
		data_matrix[i][2] = raw_data[i][1];
		//eFG%		
		data_matrix[i][3] = (raw_data[i][6] + 0.5 * raw_data[i][9]) / raw_data[i][7];
		//TOV%
		data_matrix[i][4] = raw_data[i][21]/(raw_data[i][7] + 0.44 * raw_data[i][12] + raw_data[i][21]);
		//ORB	
		data_matrix[i][5] = raw_data[i][15];
		//DRB	
		data_matrix[i][6] = raw_data[i][16];
		// FT/FGA	
		data_matrix[i][7] = raw_data[i][12] / raw_data[i][7];
		// win or loss
		data_matrix[i][8] = raw_data[i][3];			
	}
	return data_matrix;
} 

void data_formation_processing(std::string &year, std::string &team) {
	string dir_input = "raw_data";
	string dir_output = "formation_data";
    	string fileformat = ".csv";	
	string input_filename = dir_input + "/" + year + "/" + year + team + "_raw" +fileformat;
	//string input_filename = "datadata.csv";  	
	string output_filename = dir_output + "/" + year + "/" + year + team + "_formation" +fileformat;
	//string output_filename = "datadata_out.csv";	
	std::vector<std::vector<double> > data_matrix = raw_data_read(input_filename);
	/*if (team.compare("ATL") == 0) {	
		for (unsigned i = 29; i < data_matrix.size(); i++) {
			for (unsigned j = 0; j < data_matrix[i].size(); j++) {
				if (j == data_matrix[i].size() - 1) {
					std::cout<<data_matrix[i][j]<<"\n";
				} else {			
					std::cout<<data_matrix[i][j]<<",";
				}
			}
		}
	}*/
	std::vector<std::vector<double> > data_cal = data_calculation(data_matrix);

	file_write_formation_double (output_filename, data_cal);	
	// get win(1)-loss(0) label 
	string output_label = dir_output + "/" + year + "/" + year + team + "_label" +fileformat;
	
	std::vector<double> label = label_processing (data_cal);
	file_write_formation_double_line(output_label, label);
}



/*
int main (){
	string year = "2014";
	//string team = "HOU";
	//data_formation_processing(year, team);
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		data_formation_processing(year, team[i]);
	}
    return 1;
}*/

// g++ -std=c++11 -Wall main.cpp -o main
