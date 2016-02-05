#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "team_id_processing.cpp"
#include "month_id_processing.cpp"
#include "data_IO.cpp"
#include "feature_label_processing.cpp"
#include "schedule_formation.cpp"
#include "data_formation.cpp"
#include "cal_vh_average.cpp"
#include "cal_overall_average.cpp"
#include "cal_lastN_average.cpp"
#include "cluster_team.cpp"
#include "cal_cluster_average.cpp"

using namespace std;


int main (){
	string year = "2014";
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};
	read_schedule (year);
	for (unsigned i = 0; i < team.size(); i++) {
	//string team = "MEM";
		data_formation_processing(year, team[i]);
		overall_average_processing (year, team[i]); 
		vh_average_processing (year, team[i]);
		int N = 8;
		lastN_average_processing (year, team[i], N);
		NBA_pre_cluster(year);
		double var_to_retain = 1.0;
		NBA_pca(year, true, var_to_retain);
		size_t num_cluster = 5;
		NBA_k_means(year, num_cluster);
		NBA_cluster_teams(year, num_cluster); 
		cluster_average_processing(year, team[i], num_cluster);	
	}	

    return 1;
}

// g++ -std=c++11 -Wall main.cpp -o main
//g++ -std=c++11 -Wall test.cpp -lmlpack -O1 -larmadillo -o test
