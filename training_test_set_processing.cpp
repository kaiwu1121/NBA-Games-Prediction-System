#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include<numeric>
#include "team_id_processing.cpp"
#include "month_id_processing.cpp"
#include "data_IO.cpp"
#include "feature_label_processing.cpp"


using namespace std;

std::vector<double> search_row(double date, std::vector<std::vector<double> >& data_matrix) {
	std::vector<double> record;
	for (unsigned i = 0; i < data_matrix.size(); i++) {
		if (data_matrix[i][0] == date) {
			if (i == 0) {
				for (unsigned j = 3; j < data_matrix[i].size(); j++) {
					record.push_back(data_matrix[i][j]);
				}
			} else {
				for (unsigned j = 3; j < data_matrix[i].size(); j++) {
					record.push_back(-9999);
				}
			}

			return record;
		}	
	}
	return record;
}

std::vector<double> concatenate_record(std::vector<double>& host_record, std::vector<double>& visitor_record){
		std::vector<double> host_visitor;
		host_visitor.reserve( host_record.size() + visitor_record.size() ); 
		host_visitor.insert( host_visitor.end(), host_record.begin(), host_record.end() );
		host_visitor.insert( host_visitor.end(), visitor_record.begin(), visitor_record.end() );
	return host_visitor;
}


void pre_training_testing (const std::string &year, std::string &type) {
	string input_dir = "schedule";
	string output_dir = "overall_data";
    	string fileformat = ".csv";	
	string input_filename = input_dir + "/" + "output" + "/" + year + "schedule_foramtion" +fileformat;
	std::vector<std::vector<double> > schedule_matrix = file_read_formation_double(input_filename);
	std::vector<std::vector<double> > record_set;
	std::vector<double> result_set;
	for (unsigned i = 0; i < schedule_matrix.size(); i++) {
		double date = schedule_matrix[i][0];
		string host_team = team_idTOname(schedule_matrix[i][1]);
		string visitor_team = team_idTOname(schedule_matrix[i][3]);
		double result = 0;
		if (schedule_matrix[i][2] > schedule_matrix[i][4]) {
			result = 1;
		}
		result_set.push_back(result);
		//std::cout<<host_team<<" VS "<<visitor_team<<" "<<result<<endl;
		string host_team_file = output_dir + "/" + year + "/" + year + host_team + "_" + type + fileformat;
		string visitor_team_file = output_dir + "/" + year + "/" + year + visitor_team + "_" + type + fileformat;
		//std::cout<<host_team_file<<endl;
		//std::cout<<visitor_team_file<<endl;
		std::vector<std::vector<double> > host_data = file_read_formation_double (host_team_file);
		std::vector<std::vector<double> > visitor_data = file_read_formation_double (visitor_team_file);
		std::vector<double> host_record = search_row(date, host_data);
		std::vector<double> visitor_record = search_row(date, visitor_data);
		if (host_record[0] != -9999 && visitor_record[0] != -9999) {
			std::vector<double> host_visitor = concatenate_record(host_record, visitor_record);
			record_set.push_back(host_visitor);
		} 
	}
	
	string training_file = "training_set/" + type + "/" + year + "/" + year + "training_set" + fileformat; 
	file_write_formation_double (training_file, record_set);
	string label_file = "training_set/" + type + "/" + year + "/" + year + "label_set" + fileformat; 
	file_write_formation_double_line (label_file, result_set); 

		/*string host_team_file = output_dir + "/" + year + "/" + year + "BOS" + "_" + type + fileformat;
		string visitor_team_file = output_dir + "/" + year + "/" + year + "HOU" + "_" + type +fileformat;
		std::vector<std::vector<double> > host_data = file_read_formation_double (host_team_file);
		std::vector<std::vector<double> > visitor_data = file_read_formation_double (visitor_team_file);
		std::vector<double> host_record = search_row(20141101, host_data);
		std::vector<double> visitor_record = search_row(20141101, visitor_data);
		std::vector<double> host_visitor = concatenate_record(host_record, visitor_record);
		record_set.push_back(host_visitor);*/
	//file_write_formation_double (output_filename, data_matrix);	
}

int main (){
	string year = "2014";
	string type = "overall";
	pre_training_testing (year, type);
    return 1;
}

// g++ -std=c++11 -Wall main.cpp -o main
