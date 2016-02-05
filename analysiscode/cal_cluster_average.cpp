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

std::vector<std::vector<double> > cluster_formation_processing (std::string &year, std::vector<std::vector<double> >& data_matrix_formation, size_t num_cluster) {
	int size = (int)num_cluster;
	string input_dir = "season_summary";
	string fileformat = ".csv";	
	string cluster_team_file = input_dir + "/" + year + "/" + "output" + "/" + year + "_cluster_team_output" + fileformat;	
	std::vector<std::vector<double> > team_clusters = file_read_formation_double (cluster_team_file);
	std::vector<std::vector<double> > data_matrix_cluster = data_matrix_formation;
	for (unsigned i = 0; i < data_matrix_formation.size(); i++) {
		for (int clusterID = 0 ; clusterID < size; clusterID++) {
			if ( std::find(team_clusters[clusterID].begin(), team_clusters[clusterID].end(), data_matrix_cluster[i][2]) != team_clusters[clusterID].end() ) {
			   	data_matrix_cluster[i][2] = clusterID;
				break;
			}
		}
	}
	return data_matrix_cluster;
}

std::vector<std::vector<double> > cluster_processing (std::vector<std::vector<double> >& data_matrix, int clusterID) {
  int rows = data_matrix.size();
  int cols = data_matrix[0].size();
  std::vector<std::vector<double> > cluster_data;
  cluster_data.resize(rows, std::vector<double> (cols, 0));
  std::vector<double> sum_cluster;
  sum_cluster.resize(cols, 0);
  int num_cluster = 0;
  for (int i = 0; i < rows; i++) {
	if (i > 0 && data_matrix[i - 1][2] == clusterID) {
		num_cluster++;
	}
	for (int j = 0; j < cols; j++) {
	    if (j < 3 || i == 0) {
		if (j < 3) {
			cluster_data[i][j] = data_matrix[i][j];	
		} else {
			cluster_data[i][j] = 0;
		}
	    } else {
			if (data_matrix[i - 1][2] == clusterID) {
				sum_cluster[j] += data_matrix[i - 1][j];
				cluster_data[i][j] = sum_cluster[j] / num_cluster;
			} else {
				cluster_data[i][j] = cluster_data[i - 1][j];
			}	
		}
	}
  }
  return cluster_data;
}

std::vector<std::vector<double> > cluster_connection (std::vector<std::vector<double> > & hostData, std::vector<std::vector<double> > &clusterData) {
	std::vector<std::vector<double> > vh_data;  
	if (hostData.size() == visitorData.size()) {
		vh_data.resize(hostData.size(), std::vector<double>(4,0));
		for (unsigned i = 0; i < hostData.size(); i++) {
			if (hostData[i][0] == visitorData[i][0]) {
				for (unsigned j = 0; j < 4; j++) {
					if (j < 3) {
						vh_data[i][j] = hostData[i][j];
					} else {
						if (hostData[i][1] == 1 && visitorData[i][1] == 1) {
							vh_data[i][j] = hostData[i][hostData[i].size() - 1];
						} else if (visitorData[i][1] == 0 && hostData[i][1] == 0) {
							vh_data[i][j] = visitorData[i][visitorData[i].size() - 1];
						}
					}
				}
			}
		}
	}
  return vh_data;
}


void cluster_average_processing(std::string &year, std::string &team, size_t num_cluster) {
	int size = (int)num_cluster;
	string input_dir = "formation_data";
	string output_dir = "cluster_team_data";
    	string fileformat = ".csv";	
  	string input_filename = input_dir + "/" + year + "/" + year + team + "_formation" +fileformat;
        std::vector<std::vector<double> > data_matrix_formation = file_read_formation_double (input_filename);
	std::vector<std::vector<double> > data_matrix_cluster = cluster_formation_processing (year, data_matrix_formation, num_cluster);
	for (int clusterID = 0; clusterID < size; clusterID++) {
		std::vector<std::vector<double> > cluster_data = cluster_processing (data_matrix_cluster, clusterID);
		std::vector<std::vector<double> > feature_data = feature_processing (cluster_data);
		string output_filename = output_dir + "/" + year + "/" + year + team + "_cluster_" +  std::to_string(clusterID) +fileformat;
		string output_filename_feature = output_dir + "/" + year + "/" + year + team + "_cluster_" +  std::to_string(clusterID) + "_featureOnly" +fileformat;
		//write data into file		
		file_write_formation_double (output_filename, cluster_data);
		file_write_formation_double (output_filename_feature, feature_data);	
	}
	
}

int main (){
	string year = "2014";
	//string team = "GSW";
	size_t num_cluster = 5;
	//cluster_average_processing(year, team, num_cluster);
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		cluster_average_processing(year, team[i], num_cluster);
	}
    return 1;
}

// g++ -std=c++11 -Wall main.cpp -o main
