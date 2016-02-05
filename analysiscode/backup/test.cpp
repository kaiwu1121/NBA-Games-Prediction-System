#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "team_id_processing.cpp"
//#include "data_IO.cpp"
//#include "feature_label_processing.cpp"


using namespace std;
/*

int month_id (std::string month) {
	if (month.compare("Jan") == 0) {
		return 1;
	} else if (month.compare("Feb") == 0) {
		return 2;
	} else if (month.compare("Mar") == 0) {
		return 3;
	} else if (month.compare("Apr") == 0) {
		return 4;
	} else if (month.compare("May") == 0) {
		return 5;
	} else if (month.compare( "Jun") == 0) {
		return 6;
	} else if (month.compare("Jul") == 0) {
		return 7;
	} else if (month.compare("Aug") == 0) {
		return 8;
	} else if (month.compare("Sep") == 0) {
		return 9;
	} else if (month.compare("Oct") == 0) {
		return 10;
	} else if (month.compare("Nov") == 0) {
		return 11;
	} else if (month.compare("Dec") == 0) {
		return 12;
	} 
	return -1;
}

std::vector<std::vector<double> > schedulefile_read (const std::string &filename) {
    ifstream file (filename); 
    std::string data_line;
    std::vector<std::vector<double> > data_matrix;
    std::string::size_type sz;
    std::string number;
    while ( file.good() )
    {
        while (getline ( file, data_line)) { 
		//std::cout<<data_line<<endl;
		int att_index = 0;
		std::istringstream is(data_line);
		std::vector<double> items;
        	while(std::getline(is, number, ',')) 
        	{
			if (att_index == 0) {
				std::size_t first = number.find(" ");
				std::size_t second = number.find(" ",first + 1);
				std::size_t third = number.find(" ",second + 1);
				string year = number.substr(third,4);
				string month = number.substr(first + 1, 3);
				string day = number.substr(second + 1, third - second - 1);
				string date;
				if (std::stod(day,&sz) < 10) {
					date = year+month+"0"+day;
				} else {
					date = year+month+day;
				}
				
				items.push_back(std::stod(date,&sz));
			} else if (att_index == 1 || att_index == 3) {
				int teamid = teamid_full (number);
				items.push_back((double)teamid);
			} else {
				items.push_back(std::stod(number,&sz));
			}
			att_index++;
        	}
		data_matrix.push_back(items);
	}
    }
	return data_matrix;
}

void read_schedule (const std::string &year) {
	string dir = "schedule";
    	string fileformat = ".csv";	
	string input_filename = dir + "/" + "input" + "/" + year + "schedule" +fileformat;
  	string output_filename = dir + "/" + "output" + "/" + year + "schedule_foramtion" +fileformat;
	std::cout<<input_filename<<endl;
	//std::vector<std::vector<double> > data_matrix = raw_data_read(input_filename);
	//file_write_formation_double (output_filename, data_matrix);	
}*/

int main (){
	string year = "2014";
	//read_schedule (year);	
    return 1;
}

// g++ -std=c++11 -Wall main.cpp -o main
