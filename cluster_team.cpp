#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector> 
#include <cstdio>
#include <mlpack/core.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <mlpack/methods/pca/pca.hpp>
//#include "team_id_processing.cpp"
//#include "data_IO.cpp"

using namespace std;
using namespace mlpack;
using namespace mlpack::kmeans;
using namespace mlpack::pca;

std::vector<std::vector<double> > data_matrix_cat(std::vector<std::vector<double> >& data_matrix1, std::vector<std::vector<double> >& data_matrix2, std::vector<std::vector<double> >& data_matrix3, std::vector<std::vector<double> >& data_matrix4) {
	std::vector<std::vector<double> > data_matrix_all;
	if (data_matrix1.size() == data_matrix2.size() && data_matrix1.size() == data_matrix3.size() && data_matrix1.size() == data_matrix4.size()) {
		int col_size = data_matrix1[0].size() + data_matrix2[0].size() + data_matrix3[0].size() + data_matrix4[0].size() - 3;
		data_matrix_all.resize(data_matrix1.size(), std::vector<double> (col_size, 0));
		for (unsigned i = 0; i < data_matrix1.size(); i++) {
			for (int j = 0; j < col_size; j++) {
				if((unsigned)j < data_matrix1[0].size()) {
					data_matrix_all[i][j] = data_matrix1[i][j];
				} else if ((unsigned)j >= data_matrix1[0].size() && (unsigned)j < data_matrix1[0].size() + data_matrix2[0].size() - 1) {
					data_matrix_all[i][j] = data_matrix2[i][j - data_matrix1[0].size() + 1];
				} else if ((unsigned)j >= data_matrix1[0].size() + data_matrix2[0].size() - 1 && (unsigned)j < data_matrix1[0].size() + data_matrix2[0].size() - 1 + data_matrix3[0].size()  - 1) {
					data_matrix_all[i][j] = data_matrix3[i][j - data_matrix1[0].size() + 1 - data_matrix2[0].size() + 1];
				} else if ((unsigned)j >= data_matrix1[0].size() + data_matrix2[0].size() - 1 + data_matrix3[0].size()  - 1 && j < col_size) {
					data_matrix_all[i][j] = data_matrix4[i][j - data_matrix1[0].size() + 1 - data_matrix2[0].size() + 1 - data_matrix3[0].size() + 1];
				}
				
			}
		}
	}		
	return data_matrix_all;
}

void NBA_pre_cluster(std::string &year) {
	string dir = "season_summary";
	string input = "input";
	string output = "output";
    	string fileformat = ".csv";
    	string table1 = "TRADITIONAL_STATS";
    	string table2 = "CLUTCH_TRADITIONAL_STATS";
    	string table3 = "SHOOTING_STATS";
    	string table4 = "OPPONENT_SHOOTING_STATS";
        string file1 = dir + "/" + year + "/" + input + "/" + year+ table1 + fileformat;
	string file2 = dir + "/" + year + "/" + input + "/" + year+ table2 + fileformat;
	string file3 = dir + "/" + year + "/" + input + "/" + year+ table3 + fileformat;
 	string file4 = dir + "/" + year + "/" + input + "/" + year+ table4 + fileformat;
   	std::vector<std::vector<double> > data_matrix1 = summary_data_read(file1);
	std::vector<std::vector<double> > data_matrix2 = summary_data_read(file2);
	std::vector<std::vector<double> > data_matrix3 = summary_data_read(file3);
	std::vector<std::vector<double> > data_matrix4 = summary_data_read(file4);
	std::vector<std::vector<double> > data_set = data_matrix_cat(data_matrix1,data_matrix2,data_matrix3,data_matrix4);
	string summary_file = dir + "/" + year + "/" + output + "/" + year + "_season_summary" + fileformat;
	file_write_formation_double (summary_file, data_set);	
	std::vector<double> team_order;	
	for (unsigned i = 0; i < data_set.size(); i++)
    	{
		team_order.push_back(data_set[i][0]);
   	 }
	 string teamorder_file = dir + "/" + year + "/" + output + "/" + year +"_summary_team_order" + fileformat;
	 file_write_formation_double_line (teamorder_file, team_order); 
}

void NBA_pca(std::string &year, const bool scaleData, double var_to_retain) {
	string dir = "season_summary";
	string input = "input";
	string output = "output";
	string fileformat = ".csv";
	string inputfile = dir + "/" + year + "/" + output + "/" + year + "_season_summary" + fileformat;
 	arma::mat dataset;
  	data::Load(inputfile, dataset, true);
	//const size_t newDimension,
	//size_t newDimension = newDimension;
  	PCA p(scaleData);
  	//double varRetained;
 	//varRetained = p.Apply(dataset, var_to_retain);
	p.Apply(dataset, var_to_retain);
 	//varRetained = p.Apply(dataset, newDimension);
	string outputfile = dir + "/" + year + "/" + output + "/" + year + "_pca_output" + fileformat;
  	data::Save(outputfile, dataset);	
}

void NBA_k_means(std::string &year, size_t num_cluster) {
	string dir = "season_summary";
	string input = "input";
	string output = "output";
	string fileformat = ".csv";
	string inputfile = dir + "/" + year + "/" + output + "/" + year + "_pca_output" + fileformat;
	arma::mat dataset;
  	data::Load(inputfile, dataset, true);
	arma::Col<size_t> assignments;
	KMeans<> k;
	k.Cluster(dataset, num_cluster, assignments);
	string outputfile = dir + "/" + year + "/" + output + "/" + year + "_k_means_output" + fileformat;	
	data::Save(outputfile, assignments);
}

void NBA_cluster_teams(std::string &year, size_t num_cluster) {
	string dir = "season_summary";
	string input = "input";
	string output = "output";
	string fileformat = ".csv";
	string clusterfile = dir + "/" + year + "/" + output + "/" + year + "_k_means_output" + fileformat;
	string orderfile = dir + "/" + year + "/" + output + "/" + year + "_summary_team_order" + fileformat;
	std::vector<std::vector<int> > team_clusters((int)num_cluster);
	std::vector<int> cluster_result = read_line (clusterfile);
	std::vector<int> team_id_order = read_line (orderfile);
	int num = num_cluster;
	for (int index = 0; index < num; index++) {
		for (unsigned i = 0; i < cluster_result.size(); i++) {
			if (cluster_result[i] == index) {
				team_clusters[index].push_back(team_id_order[i]);
			}
		}	
	}
	string cluster_team = dir + "/" + year + "/" + output + "/" + year + "_cluster_team_output" + fileformat;	
	file_write_formation_int (cluster_team, team_clusters);
}
/*
int main(){
	std::string year = "2014";
	NBA_pre_cluster(year);
	double var_to_retain = 1.0;
	NBA_pca(year, true, var_to_retain);
	size_t num_cluster = 5;
	NBA_k_means(year, num_cluster);
	NBA_cluster_teams(year, num_cluster); 
	return 1;
}
*/
//g++ -std=c++11 -Wall test.cpp -lmlpack -O1 -larmadillo -o test
