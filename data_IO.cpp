#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


std::vector<std::vector<double> > raw_data_read(const std::string &filename) {
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
				std::size_t first = number.find("-");
				std::size_t second = number.find("-",first + 1);
				string year = number.substr(0, first);
				string month = number.substr(first + 1, 2);
				string day = number.substr(second + 1);
				string date = year+month+day;
				items.push_back(std::stod(date,&sz));
			} else if (att_index == 1) {
				if (number.find("@") != string::npos) {
					items.push_back(0.0);
					std::size_t pos = number.find("@");						
					int vteam = teamid(number.substr(pos + 2));
					items.push_back((double)vteam);
				} else {
					items.push_back(1.0);
					std::size_t pos = number.find("vs.");
					int vteam = teamid(number.substr(pos + 4));
					items.push_back((double)vteam);
				}			
			} else if (att_index == 22){
				if (number.compare("W") == 0) {
					items.push_back(1.0);
				} else {
					items.push_back(0.0);
				}
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
				//std::cout<<first<<" "<<second<<" "<<third<<endl;
				string year = number.substr(third);
				string month = std::to_string(month_id(number.substr(first + 1, 3)));
				string day = number.substr(second + 1, third - second - 1);
				string date;
				if (third - second - 1 == 1) {
					date = year+month+std::to_string(0)+day;
				} else {
					date = year+month+day;
				}
				//std::cout<<date<<endl;
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

std::vector<std::vector<double> > file_read_formation_double (const std::string &filename) {
	ifstream file (filename); 
    	std::string data_line;
    	std::vector<std::vector<double> > data_matrix;
    	std::string::size_type sz;
   	std::string number;
    	while ( file.good() )
    	{
        	while (getline ( file, data_line)) { 
			std::istringstream is(data_line);
			std::vector<double> items;
        		while(std::getline(is, number, ',')) 
        		{
				items.push_back(std::stod(number,&sz));
        		}
			data_matrix.push_back(items);
		}
    	}
	return data_matrix;
}

void file_write_formation_double (const std::string &filename, std::vector<std::vector<double> >& data_matrix) {
	std::remove(filename.c_str()); 
	ofstream outputFile;
	outputFile.open(filename);
	for (unsigned i = 0; i < data_matrix.size(); i++)
	{
	    for (unsigned j = 0; j < data_matrix[i].size(); j++)
	    {
		
		if ( j != data_matrix[i].size() - 1) {
			outputFile <<std::fixed<< data_matrix[i][j]<<",";
		} else {
			outputFile <<std::fixed<< data_matrix[i][j]<<"\n";
		}
	    }
	}
	outputFile.close();
}

void file_write_formation_double_line (const std::string &filename, std::vector<double>& data_matrix) {
	std::remove(filename.c_str()); 
	ofstream outputFile;
	outputFile.open(filename);
	for (unsigned i = 0; i < data_matrix.size(); i++) {
		if ( i != data_matrix.size() - 1) { 
			outputFile <<std::fixed << data_matrix[i]<<",";
		} else {
			outputFile <<std::fixed << data_matrix[i];
		}
	}
	outputFile.close();
}

void file_write_formation_int (const std::string &filename, std::vector<std::vector<int> >& data_matrix) {
	std::remove(filename.c_str()); 
	ofstream outputFile;
	outputFile.open(filename);
	for (unsigned i = 0; i < data_matrix.size(); i++)
	{
	    for (unsigned j = 0; j < data_matrix[i].size(); j++)
	    {
		if ( j != data_matrix[i].size() - 1) {
			outputFile <<std::fixed << data_matrix[i][j]<<",";
		} else {
			outputFile <<std::fixed << data_matrix[i][j]<<"\n";
		}
	    }
	}
	outputFile.close();
}


std::vector<std::vector<double> > summary_data_read(const std::string &filename) {
    ifstream file (filename); 
    std::string::size_type sz;
    std::string data_line;
    std::vector<std::vector<double> > data_matrix;
    std::string data_line_num;
    while ( file.good() )
    {
        while (getline ( file, data_line)) { 
		std::istringstream data_line_str(data_line);
            	std::vector<double> items;
		int att_index = 0;
        	while(std::getline(data_line_str, data_line_num, ',')) {
			if (att_index == 0) {
				int teamID = teamid_full(data_line_num);
				items.push_back(teamID);
			} else {
				items.push_back(std::stod(data_line_num,&sz));
			}
			att_index ++;			
		}
		data_matrix.push_back(items);		
	}
    }
	return data_matrix;
}

std::vector<int> read_line (const std::string &filename) {
	ifstream file (filename); 
    	std::string::size_type sz;
    	std::string data_line;
    	std::vector<int> data_matrix;
    	std::string data_line_num;
    	while (file.good() )
    	{
		while(std::getline(file, data_line_num, ',')) {
			int item = std::stoi(data_line_num,&sz);
			data_matrix.push_back(item);	
		}	
    	}
	/*for (unsigned i = 0; i < data_matrix.size(); i++) {
		std::cout<<data_matrix[i]<<",";
	}
	std::cout<<endl;*/
	return data_matrix;
}
