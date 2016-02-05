#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <mlpack/core.hpp>
#include <mlpack/methods/pca/pca.hpp>
//#include "team_id_processing.cpp"
//#include "month_id_processing.cpp"
//#include "data_IO.cpp"
//#include "feature_label_processing.cpp"


using namespace std;
using namespace mlpack;
using namespace mlpack::pca;

void real_training_data_connection (const std::string &year, std::string &team) {
	// datafile name
    	string fileformat = ".csv";	
	string dateFile = "feature_data/" + year + "/" + year + team +"_date" + fileformat;
	string overallFile = "overall_data/" + year + "/" + year + team + "_overall" +fileformat;
	string host_visitorFile = "host_visitor_data/" + year + "/" + year + team + "_vh" +fileformat;
	string lastNFile = "lastN_data/" + year + "/" + year + team + "_lastN" +fileformat;
	string real4File = "feature_data/" + year + "/" + year + team +"_feature" + fileformat;
	
	//data read
	std::vector<std::vector<double> > dateData = file_read_formation_double (dateFile);
	std::vector<std::vector<double> > overallData =  file_read_formation_double (overallFile);
	std::vector<std::vector<double> > host_visitorData =  file_read_formation_double (host_visitorFile);
	std::vector<std::vector<double> > lastNData =  file_read_formation_double (lastNFile);
	std::vector<std::vector<double> > real4Data =  file_read_formation_double (real4File);
	//std::cout<<simulationData[0].size()<<endl;
	//how many features		
	//int cols = (int)dateData[0].size() + ((int)overallData[0].size() - 3) + ((int)host_visitorData[0].size() - 3) + ((int)simulationData[0].size() - 3);
	int cols = (int)dateData[0].size() + ((int)overallData[0].size() - 3) + ((int)host_visitorData[0].size() - 3) + ((int)lastNData[0].size() - 3) + ((int)real4Data[0].size());
	//int cols = 3 + 1 + 20;	     
	//std::cout<<cols<<endl;
	//dataset matrix
	std::vector<std::vector<double> > data_matrix;
	data_matrix.resize(dateData.size() - 1, std::vector<double>(cols, 0));

	for (int i = 0; i < (int)dateData.size() - 1; i++) {
		for (int j = 0; j < cols; j++) {
			if (j < 3) {
				data_matrix[i][j] = dateData[i + 1][j];
			} else if (j < (int)real4Data[i + 1].size() + 3) { 
					data_matrix[i][j] = real4Data[i + 1][j - 3];
			} else if (j == cols - 3) {
				if (data_matrix[i][0] == overallData[i + 1][0]) {
					data_matrix[i][j] = overallData[i + 1][3];
				}
			} else if (j == cols - 2) {
				if (data_matrix[i][0] == host_visitorData[i + 1][0]) {
					data_matrix[i][j] = host_visitorData[i + 1][3];
				}			
			} else if (j == cols - 1) {
				if (data_matrix[i][0] == lastNData[i + 1][0]) {
					data_matrix[i][j] = lastNData[i + 1][3];
				}
			} 
		}
	}
	string real_datasetFile = "data_set/" + year + "/" + year + team + "_data_set_real.csv";
	file_write_formation_double(real_datasetFile, data_matrix);
}

void data_connection (const std::string &year, std::string &team) {
	// datafile name
    	string fileformat = ".csv";	
	string dateFile = "feature_data/" + year + "/" + year + team +"_date" + fileformat;
	string overallFile = "overall_data/" + year + "/" + year + team + "_overall" +fileformat;
	string host_visitorFile = "host_visitor_data/" + year + "/" + year + team + "_vh" +fileformat;
	string lastNFile = "lastN_data/" + year + "/" + year + team + "_lastN" +fileformat;
	string simulationFile = "simulation_data/" + year + "/" + year + team + "_performance" + fileformat;
	
	//data read
	std::vector<std::vector<double> > dateData = file_read_formation_double (dateFile);
	std::vector<std::vector<double> > overallData =  file_read_formation_double (overallFile);
	std::vector<std::vector<double> > host_visitorData =  file_read_formation_double (host_visitorFile);
	std::vector<std::vector<double> > lastNData =  file_read_formation_double (lastNFile);
	std::vector<std::vector<double> > simulationData =  file_read_formation_double (simulationFile);
	//std::cout<<simulationData[0].size()<<endl;
	//how many features		
	//int cols = (int)dateData[0].size() + ((int)overallData[0].size() - 3) + ((int)host_visitorData[0].size() - 3) + ((int)simulationData[0].size() - 3);
	int cols = (int)dateData[0].size() + ((int)overallData[0].size() - 3) + ((int)host_visitorData[0].size() - 3) + ((int)lastNData[0].size() - 3) + ((int)simulationData[0].size() - 3);
	//int cols = 3 + 1 + 20;	     
	//std::cout<<cols<<endl;
	//dataset matrix
	std::vector<std::vector<double> > data_matrix;
	data_matrix.resize(dateData.size() - 1, std::vector<double>(cols, 0));

	for (int i = 0; i < (int)dateData.size() - 1; i++) {
		for (int j = 0; j < cols; j++) {
			if (j < 3) {
				data_matrix[i][j] = dateData[i + 1][j];
			} else if (j < (int)simulationData[i + 1].size()) { 
				if (data_matrix[i][0] == simulationData[i + 1][0]) {
					data_matrix[i][j] = simulationData[i + 1][j];
				}
			} else if (j == cols - 3) {
				if (data_matrix[i][0] == overallData[i + 1][0]) {
					data_matrix[i][j] = overallData[i + 1][3];
				}
			} else if (j == cols - 2) {
				if (data_matrix[i][0] == host_visitorData[i + 1][0]) {
					data_matrix[i][j] = host_visitorData[i + 1][3];
				}			
			} else if (j == cols - 1) {
				if (data_matrix[i][0] == lastNData[i + 1][0]) {
					data_matrix[i][j] = lastNData[i + 1][3];
				}
			} 
		}
	}
	string datasetFile = "data_set/" + year + "/" + year + team + "_data_set.csv";
	file_write_formation_double(datasetFile, data_matrix);
}

/*
int main (){
	string year = "2014";
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		data_connection(year, team[i]);
	}
    return 1;
 }
*/
// g++ -std=c++11 -Wall main.cpp -o main
