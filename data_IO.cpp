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
	int row = 0;
        while (getline ( file, data_line)) { 
		if (row == 0) { 
			
		} else {
			//std::cout<<data_line<<endl;
			int att_index = 0;
			std::istringstream is(data_line);
			std::vector<double> items;
			while(std::getline(is, number, ',')) 
			{
				if (att_index == 0) {
					
				} else if (att_index == 1) {
					int vteam;
					if (number.find("@") != string::npos) {
						items.push_back(0.0);
						std::size_t pos = number.find("@");						
						vteam = teamid(number.substr(pos + 2));
						items.push_back((double)vteam);
					} else {
						items.push_back(1.0);
						std::size_t pos = number.find("vs.");
						vteam = teamid(number.substr(pos + 4));
						items.push_back((double)vteam);
					}	
					if (vteam == -1) {
						std::cout<<data_line<<endl;
					}		
				} else if (att_index == 2) {
					//std::cout<<number<<endl;
					if (number.find("-") != string::npos) {
						std::size_t first = number.find("-");
						std::size_t second = number.find("-",first + 1);
						string year = number.substr(0, first);
						string month = number.substr(first + 1, 2);
						string day = number.substr(second + 1);
						string zero = "0";
						if (month.length() == 1) {
							month = zero + month;
						}
						if (day.length() == 1) {
							day = zero + day;
						}
						string date = year+month+day;
						items.push_back(std::stod(date,&sz));
					} else if (number.find("/") != string::npos) {
						std::size_t first = number.find("/");
						std::size_t second = number.find("/",first + 1);
						string year = number.substr(second + 1);
						string month = number.substr(0, first);
						string day = number.substr(first + 1, second - first - 1);
						//std::cout<<year<<"/"<<month<<"/"<<day<<endl;
						string zero = "0";
						if (month.length() == 1) {
							month = zero + month;
						}
						if (day.length() == 1) {
							day = zero + day;
						}
						string date = year+month+day;
						items.push_back(std::stod(date,&sz));
					}
				} else if (att_index == 3){
					if (number.compare("W") == 0) {
						items.push_back(1.0);
					} else {
						items.push_back(0.0);
					}
				} else {
					items.push_back(std::stod(number,&sz));
				}
				//std::cout<<att_index<<endl;
				att_index++;
			}
			data_matrix.push_back(items);
		}
		row += 1;
		//std::cout<<row<<endl;
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
				string year = number.substr(third + 1);
				string month = std::to_string(month_id(number.substr(first + 1, 3)));
				string day = number.substr(second + 1, third - second - 1);
				string date;
				string zero = "0";
				if (month.length() == 1) {
					month = zero + month;
				}
				if (day.length() == 1) {
					day = zero + day;
				}
					date = year+month+day;
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

std::vector<std::vector<int> > file_read_formation_int (const std::string &filename) {
	ifstream file (filename); 
    	std::string data_line;
    	std::vector<std::vector<int> > data_matrix;
    	std::string::size_type sz;
   	std::string number;
    	while ( file.good() )
    	{
        	while (getline ( file, data_line)) { 
			std::istringstream is(data_line);
			std::vector<int> items;
        		while(std::getline(is, number, ',')) 
        		{
				items.push_back(std::stoi(number,&sz));
        		}
			data_matrix.push_back(items);
		}
    	}
	return data_matrix;
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

std::vector<double> read_line_double (const std::string &filename) {
	ifstream file (filename); 
    	std::string::size_type sz;
    	std::string data_line;
    	std::vector<double> data_matrix;
    	std::string data_line_num;
    	while (file.good() )
    	{
		while(std::getline(file, data_line_num, ',')) {
			double item = std::stod(data_line_num,&sz);
			data_matrix.push_back(item);	
		}	
    	}
	/*for (unsigned i = 0; i < data_matrix.size(); i++) {
		std::cout<<data_matrix[i]<<",";
	}
	std::cout<<endl;*/
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

void file_write_formation_double_svm (const std::string &filename, std::vector<std::vector<double> >& featureData, std::vector<double> &labelData) {
	int rows = featureData.size();
	int cols = featureData[0].size() + 1;
	std::vector<std::vector<double> > data_matrix;
	data_matrix.resize(rows, std::vector<double>(cols, 0));
	std::cout<<data_matrix.size()<<" "<<data_matrix[0].size()<<endl;
	std::cout<<rows<<" "<<cols<<endl;
	for (int i = 0; i < rows; i++) {
		data_matrix[i][0] = labelData[i];
		for (int j = 1; j < cols; j ++) {
			data_matrix[i][j] = featureData[i][j - 1];
		}
	}
	std::remove(filename.c_str()); 
	ofstream outputFile;
	outputFile.open(filename);
	for (unsigned i = 0; i < data_matrix.size(); i++)
	{
	    for (unsigned j = 0; j < data_matrix[i].size(); j++)
	    {
		if (j == 0) {
			if (data_matrix[i][j] > 0) {
				outputFile <<std::fixed<< showpos<<(int)data_matrix[i][j]<<" ";
			} else {
				outputFile <<std::fixed<<(int)data_matrix[i][j]<<" ";
			}
		} else if ( j < data_matrix[i].size() - 1 && j > 0) {
			outputFile <<std::fixed<< j << ":" << noshowpos<<data_matrix[i][j]<<" ";
		} else {
			outputFile <<std::fixed<< j << ":" << noshowpos<< data_matrix[i][j]<<"\n";
		}
	    }
	}
	outputFile.close();
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

void file_write_formation_int_line (const std::string &filename, std::vector<int>& data_matrix) {
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

void file_write_formation_int_col (const std::string &filename, std::vector<int>& data_matrix) {
	std::remove(filename.c_str()); 
	ofstream outputFile;
	outputFile.open(filename);
	for (unsigned i = 0; i < data_matrix.size(); i++) {
		if ( i != data_matrix.size() - 1) { 
			outputFile <<std::fixed << data_matrix[i]<<"\n";
		} else {
			outputFile <<std::fixed << data_matrix[i];
		}
	}
	outputFile.close();
}

void file_write_formation_double_col (const std::string &filename, std::vector<double>& data_matrix) {
	std::remove(filename.c_str()); 
	ofstream outputFile;
	outputFile.open(filename);
	for (unsigned i = 0; i < data_matrix.size(); i++) {
		if ( i != data_matrix.size() - 1) { 
			outputFile <<std::fixed << data_matrix[i]<<"\n";
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

