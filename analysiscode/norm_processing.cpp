#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector> 
#include <cstdio>
#include <mlpack/core.hpp>
#include <mlpack/methods/pca/pca.hpp>
//#include "team_id_processing.cpp"
//#include "data_IO.cpp"

using namespace std;
using namespace mlpack;
using namespace mlpack::pca;

void NBA_norm(std::string &year,std::string &team) {
	string input = "feature_data";
	string output = "norm_data";
	string fileformat = ".csv";
	string inputfile = input + "/" + year + "/" + year + team +"_feature" + fileformat;
	string outputfile_normalise = output + "/" + year + "/" + year + team + "_normalise" + fileformat;
	//string outputfile_norm = output + "/" + year + "/" + year + team + "_norm" + fileformat;
 	arma::mat dataset;
  	data::Load(inputfile, dataset, true);
	arma::mat normalise_mat =normalise(dataset);
	data::Save(outputfile_normalise, normalise_mat);
	//arma::mat norm_mat =norm(dataset);
  	//data::Save(outputfile_norm, norm_mat);	
}

void standardization_processing(std::string &year,std::string &team) {
	string input = "feature_data";
	string output = "norm_data";
	string fileformat = ".csv";
	string inputfile = input + "/" + year + "/" + year + team +"_feature" + fileformat;
	string outputfile_standardization = output + "/" + year + "/" + year + team + "_stddev" + fileformat;
	
 	arma::mat dataset;
  	data::Load(inputfile, dataset, true);
	arma::mat standardization_mat =stddev(trans(dataset));
	data::Save(outputfile_standardization, standardization_mat);
}

void mean_process (std::string &year,std::string &team) {
	string input = "feature_data";
	string output = "norm_data";
	string fileformat = ".csv";
	string inputfile = input + "/" + year + "/" + year + team +"_feature" + fileformat;
	string outputfile = output + "/" + year + "/" + year + team +"_mean" + fileformat;
	arma::mat dataset;
  	data::Load(inputfile, dataset, true);
	arma::mat mean_mat = mean(trans(dataset));
	data::Save(outputfile, mean_mat);
}

/*
int main() {
	string year = "2014";
	//string team = "GSW";
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		NBA_norm(year, team[i]);
		standardization_processing(year, team[i]);		
		mean_process (year, team[i]);
	}
	return 1;
}*/
//g++ -std=c++11 -Wall test.cpp -lmlpack -O1 -larmadillo -o test
