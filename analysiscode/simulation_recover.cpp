#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
//#include "team_id_processing.cpp"
//#include "month_id_processing.cpp"
//#include "data_IO.cpp"
//#include "data_formation.cpp"
#include <mlpack/core.hpp>
#include <mlpack/methods/pca/pca.hpp>

using namespace std;
using namespace mlpack;
using namespace mlpack::pca;

void NBA_pca(std::string &year,std::string &team, const bool scaleData, double var_to_retain) {
	string fileformat = ".csv";
	string inputfile = "simulation_data/"  + year + "/" + year + team + "_sim_re" + fileformat; 
        string outputfile = "simulation_data/" + year + "/" + year + team + "_sim_re_pca" + fileformat; 
 	arma::mat dataset;
  	data::Load(inputfile, dataset, true);
	//const size_t newDimension,
	//size_t newDimension = newDimension;
  	PCA p(scaleData);
  	//double varRetained;
 	//varRetained = p.Apply(dataset, var_to_retain);
	p.Apply(dataset, var_to_retain);
 	//varRetained = p.Apply(dataset, newDimension);
  	data::Save(outputfile, dataset);	
}

void simulation_roecover (std::string &year,std::string &team) {
	string dateFile = "feature_data/" + year + "/" + year + team +"_date.csv";
	std::vector<std::vector<double> > date_data = file_read_formation_double (dateFile);

	string output = "simulation_data/" + year + "/" + year + team + "_sim_re.csv";
	std::vector<std::vector<double> > sim_re;
	sim_re.resize(date_data.size() - 1, std::vector<double>(5,0));
	string meanFile = "norm_data/" + year + "/" + year + team +"_mean.csv";
	std::vector<std::vector<double> > mean_data = file_read_formation_double (meanFile);
	for (int col = 0 ; col < 5; col++) {
		string col_index = std::to_string(col);
		string hmmFile = "hmm_data/hmm_prediction/" + year + "/" + year + team + "_sim_col" + col_index + "_data" + ".csv";
		string diffFile = "state_data/" + year + "/" + year + team + "_state_diff_col" + col_index + ".csv";
		std::vector<int> hmm_data = read_line (hmmFile);
		std::vector<std::vector<double> > state_data = file_read_formation_double (diffFile);
		int diff_min = state_data[4][0];
		for (unsigned i = 0; i < hmm_data.size(); i++) {
			sim_re[i][col] = hmm_data[i] + diff_min + mean_data[col][0]; 
		}
	}
	file_write_formation_double(output, sim_re);
	NBA_pca(year,team, true, 1);
	std::vector<std::vector<double> > performance;

	performance.resize(date_data.size(),std::vector<double> (8,0));
	for (unsigned i = 0; i < performance.size(); i++) {
		for (unsigned j = 0; j < performance[i].size(); j++) {
			if (j < 3) {
				performance[i][j] = date_data[i][j];
			} else {
				if (i != 0) {
					performance[i][j] = sim_re[i - 1][j - 3];
				}
			}
		}
	}
	string performanceFile = "simulation_data/" + year + "/" + year + team + "_performance.csv";
	file_write_formation_double(performanceFile, performance);
}

/*
int main (){
	string year = "2014";
	//string team = "GSW";
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		simulation_roecover(year, team[i]);
	}
    return 1;
}*/
