#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "team_id_processing.cpp"
#include "month_id_processing.cpp"
#include "data_IO.cpp"
#include "feature_label_processing.cpp"


using namespace std;


std::vector<std::vector<double> > search_row(double date, std::vector<std::vector<double> >& data_matrix) {
	std::vector<std::vector<double> > recordSet;
	for (unsigned i = 0; i < data_matrix.size(); i++) {
			if ((int)data_matrix[i][0] == (int)date) {
				recordSet.push_back(data_matrix[i]);
			} 
	}
	return recordSet;
}

std::vector<double> concatenate_record(std::vector<double>& host_record, std::vector<double>& visitor_record){
		std::vector<double> host_visitor;
		//host_visitor.resize(1);
		//double data = host_record[0] - visitor_record[0];
		//host_visitor[0] = data;
		host_visitor.resize(host_record.size() + visitor_record.size());
		std::merge (host_record.begin(),host_record.end(),visitor_record.begin(),visitor_record.end(),host_visitor.begin());
	return host_visitor;
}




std::vector<std::vector<double> > seachGamesbyDate (const std::string &date) {
	
	std::string::size_type sz;
	string input = "dataSet/schedule/wholeSchedule.csv";
	string output = "dataSet/schedule/wholeSchedule_formation.csv";
	std::vector<std::vector<double> > scheduleMatrix = schedulefile_read(input);
	file_write_formation_double (output, scheduleMatrix);	
	std::vector<std::vector<double> > games = search_row(std::stod(date,&sz), scheduleMatrix);
	return games;
}





int main(int argc, char *argv[]) {
	  if (argc > 1) {
		string date = argv[1];

		// std::cout<<"Date: "<<input<<endl; 
		 std::vector<std::vector<double> > games = seachGamesbyDate(date);
		  if (games.size() > 0) {
			  for (unsigned i = 0; i < games.size(); i++) {
				for(unsigned j = 0; j < games[i].size(); j++) {
					if (j != games[i].size() - 1) {
						if (j == 1 || j == 3) {
							std::cout<<std::fixed<<team_idTOname(games[i][j])<<" ";
						} else {
							std::cout<<std::fixed<<(int)games[i][j]<<" ";
						}
					} else {
						std::cout<<std::fixed<<(int)games[i][j]<<endl;
					}
				}
			  }
		  } else {
		  	std::cout<<"No games today! Please choose another date!"<<endl;
		  }
	  } else {
	  	std::cout<<"Please choosing a correct date!"<<endl;
	  }
	
	//string date = "20101026";
	
    return 1;
}

// g++ -std=c++11 -Wall main.cpp -o main
