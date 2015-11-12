#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
//#include "team_id_processing.cpp"
//#include "data_IO.cpp"
//#include "feature_label_processing.cpp"

using namespace std;

void data_formation_processing(std::string &year, std::string &team) {
	string dir_input = "raw_data";
	string dir_output = "formation_data";
    	string fileformat = ".csv";	
	string intput_filename = dir_input + "/" + year + "/" + year + team + "_raw" +fileformat;
  	string output_filename = dir_output + "/" + year + "/" + year + team + "_formation" +fileformat;
	std::vector<std::vector<double> > data_matrix = raw_data_read(intput_filename);
	file_write_formation_double (output_filename, data_matrix);	
	// get win(1)-loss(0) label 
	string output_label = dir_output + "/" + year + "/" + year + team + "_label" +fileformat;
	std::vector<double> label = label_processing (data_matrix);
	file_write_formation_double_line(output_label, label);
}
/*
int main (){
	string year = "2014";
	string team = "GSW";
	data_formation_processing(year, team);
    return 1;
}
*/
// g++ -std=c++11 -Wall main.cpp -o main
