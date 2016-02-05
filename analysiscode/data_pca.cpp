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

void NBA_pca(std::string &year,std::string &team, const bool scaleData, double var_to_retain) {
	string input = "feature_data";
	string output = "pca_data";
	string fileformat = ".csv";
	string inputfile = input + "/" + year + "/" + year + team +"_feature" + fileformat;
 	arma::mat dataset;
  	data::Load(inputfile, dataset, true);
	//const size_t newDimension,
	//size_t newDimension = newDimension;
  	PCA p(scaleData);
  	//double varRetained;
 	//varRetained = p.Apply(dataset, var_to_retain);
	double varRetained = p.Apply(dataset, var_to_retain);
	std::cout<<varRetained<<" = ";
 	//varRetained = p.Apply(dataset, newDimension);
	string outputfile = output + "/" + year + "/" + year + team + "_pca" + fileformat;
  	data::Save(outputfile, dataset);	
}

void NBA_pca_nonscale(std::string &year,std::string &team, const bool scaleData, const size_t newDimension) {
	string input = "feature_data";
	string output = "pca_data";
	string fileformat = ".csv";
	string inputfile = input + "/" + year + "/" + year + team +"_feature" + fileformat;
 	arma::mat dataset;
  	data::Load(inputfile, dataset, true);
	//const size_t newDimension,
	//size_t newDimension = newDimension;
  	PCA p(scaleData);
  	//double varRetained;
 	//varRetained = p.Apply(dataset, var_to_retain);
	//p.Apply(dataset, var_to_retain);
 	double varRetained = p.Apply(dataset, newDimension);
	string outputfile = output + "/" + year + "/" + year + team + "_pca_nonscale" + fileformat;
  	data::Save(outputfile, dataset);
	std::cout<<varRetained<<endl;	
}

void mean_process (std::string &year,std::string &team) {
	string input = "pca_data";
	string output = "pca_data";
	string fileformat = ".csv";
	string inputfile = input + "/" + year + "/" + year + team +"_pca_nonscale" + fileformat;
	string outputfile = output + "/" + year + "/" + year + team +"_mean" + fileformat;
	arma::mat dataset;
  	data::Load(inputfile, dataset, true);
	arma::mat mean_mat = mean(trans(dataset));
	data::Save(outputfile, mean_mat);
}

int main() {
	string year = "2014";
	//string team = "GSW";
	bool scaleData = true;
	double var_to_retain = 0.99;
	//NBA_pca(year, team, scaleData, var_to_retain);
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		NBA_pca(year, team[i], scaleData, var_to_retain);
		NBA_pca_nonscale(year, team[i], false, 14);
		mean_process (year, team[i]);
	}
	return 1;
}
