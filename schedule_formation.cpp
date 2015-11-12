#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
//#include "team_id_processing.cpp"
//#include "data_IO.cpp"
//#include "feature_label_processing.cpp"


using namespace std;

void read_schedule (const std::string &year) {
	string dir = "schedule";
    	string fileformat = ".csv";	
	string input_filename = dir + "/" + "input" + "/" + year + "schedule" +fileformat;
  	string output_filename = dir + "/" + "output" + "/" + year + "schedule_foramtion" +fileformat;
	std::vector<std::vector<double> > data_matrix = schedulefile_read(input_filename);
	file_write_formation_double (output_filename, data_matrix);	
}
/*
int main (){
	string year = "2014";
	read_schedule (year);	
    return 1;
}
*/
// g++ -std=c++11 -Wall main.cpp -o main
