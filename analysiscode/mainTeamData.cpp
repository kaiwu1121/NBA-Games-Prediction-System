#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "team_id_processing.cpp"
#include "month_id_processing.cpp"
#include "data_IO.cpp"
#include "feature_label_processing.cpp"
#include "data_formation.cpp"
#include "cal_vh_average.cpp"
#include "cal_overall_average.cpp"
#include "cal_lastN_average.cpp"
//#include "cluster_team.cpp"
//#include "cal_cluster_average.cpp"
#include "feature_file_processing.cpp"
#include "norm_processing.cpp"
#include "state_processing.cpp"
#include "hmm.cpp"
#include "simulation_recover.cpp"
#include "team_data_connection.cpp"
#include "schedule_formation.cpp"
#include "training_test_set_processing.cpp"
#include "linear_regression.cpp"

using namespace std;



int main (){
        std::vector<string> years = {"2010", "2011", "2012", "2013", "2014"};
	std::vector<string> teams = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};

	/*for (unsigned year = 0; year < years.size(); year++){
	  for (unsigned team = 0; team < teams.size(); team++) {
		//std::cout<<teams[team]<<endl;
	//string team = "MEM";
	        data_formation_processing(years[year], teams[team]);
		overall_average_processing (years[year], teams[team]); 
		vh_average_processing (years[year], teams[team]);
		int N = 8;
		lastN_average_processing (years[year], teams[team], N);
		//NBA_pre_cluster(year);
		//double var_to_retain = 1.0;
		//NBA_pca(year, true, var_to_retain);
		//size_t num_cluster = 5;
		//NBA_k_means(year, num_cluster);
		//NBA_cluster_teams(year, num_cluster); 
		//cluster_average_processing(year, team[i], num_cluster);	
		
		// feature_file_processing.cpp
		feature_file_processing(years[year], teams[team]);
		date_file_processing(years[year], teams[team]);

		//norm_processing.cppy
		standardization_processing(years[year], teams[team]);		
		mean_process (years[year], teams[team]);

		//state_processing.cpp
		state_processing(years[year], teams[team]);

		//hmm.cpp
		// 5 simulate features
		for (int j = 0; j < 5; j ++) {
			string col = std::to_string(j);
			hmm_train(years[year], teams[team], col);
			hmm_simulation(years[year], teams[team], col);
		}

		//simulation_recover.cpp
		simulation_roecover(years[year], teams[team]);

		//team_data_connection.cpp
		data_connection(years[year], teams[team]);
		real_training_data_connection (years[year], teams[team]);

	  }
		//schedule_formation.cpp
		read_schedule(years[year]);		
			
		//training_test_set_processing.cpp
		string type = "simulation";
		pre_training_testing (years[year], type);
		realTrain_set (years[year], type);
		
		
		//linear_regression.cpp
		//LDA_train (years[year]);
		//LDA_predict(years[year]);
	}
	string File2010 = "wholeTrainingset/2010training_set_normalise_whole.csv"; 
	string File2011 = "wholeTrainingset/2011training_set_normalise_whole.csv"; 
	string File2012 = "wholeTrainingset/2012training_set_normalise_whole.csv"; 
	string File2013 = "wholeTrainingset/2013training_set_normalise_whole.csv"; 
	string File2014 = "wholeTrainingset/2014training_set_normalise_whole.csv";  
	
	string label2010 = "wholeTrainingset/2010label_set_whole.csv"; 
	string label2011 = "wholeTrainingset/2011label_set_whole.csv"; 
	string label2012 = "wholeTrainingset/2012label_set_whole.csv"; 
	string label2013 = "wholeTrainingset/2013label_set_whole.csv"; 
	string label2014 = "wholeTrainingset/2014label_set_whole.csv"; 
   
	
	std::vector<std::vector<double> > Data2010 = file_read_formation_double (File2010);
	std::vector<std::vector<double> > Data2011 = file_read_formation_double (File2011);
	std::vector<std::vector<double> > Data2012 = file_read_formation_double (File2012);
	std::vector<std::vector<double> > Data2013 = file_read_formation_double (File2013);
	std::vector<std::vector<double> > Data2014 = file_read_formation_double (File2014); 
	std::vector<int> label2010Data = read_line(label2010);
	std::vector<int> label2011Data = read_line(label2011);
	std::vector<int> label2012Data = read_line(label2012);
	std::vector<int> label2013Data = read_line(label2013);
	std::vector<int> label2014Data = read_line(label2014);
	
	int a = Data2010.size();
	int b = Data2011.size();
	int c = Data2012.size();
	int d = Data2013.size();
	int e = Data2014.size();
	
	std::vector<std::vector<double> > wholeData;
	std::vector<int> wholeLabel;
	wholeData.resize(a+ b + c + d + e, std::vector<double>(Data2010[0].size(),0));
	wholeLabel.resize(a + b + c + d + e, 0);
	for (int i = 0; i < (int)wholeData.size(); i++) {
		for (int j = 0; j < (int)wholeData[i].size(); j++) {
			if (i < a) {
				wholeData[i][j] = Data2010[i][j];
				wholeLabel[i] = label2010Data[i];
			} else if (i >= a && i < a + b) {
				wholeData[i][j] = Data2011[i - a][j];
				wholeLabel[i] = label2011Data[i - a];
			} else if (i >= a + b && i < a + b + c) {
				wholeData[i][j] = Data2012[i - a - b][j];
				wholeLabel[i] = label2012Data[i - a - b];
			} else if (i >= a + b + c && i < a + b + c + d) {
				wholeData[i][j] = Data2013[i - a - b - c][j];
				wholeLabel[i] = label2013Data[i - a - b - c];
			} else if (i >= a + b + c + d && i < a + b + c + d + e) {
				wholeData[i][j] = Data2014[i - a - b - c - d][j];
				wholeLabel[i] = label2014Data[i - a - b - c - d];
			}
		}
	}
	string wholeFile = "wholeTrainingset/wholetraining_set_normalise_whole.csv"; 
	string wholeFileLabel = "wholeTrainingset/wholetraining_set_label_whole.csv"; 
	file_write_formation_double (wholeFile, wholeData);
	file_write_formation_int_line (wholeFileLabel, wholeLabel);
	LDA_train_whole ();*/
	for (unsigned i = 0; i < years.size(); i++) {
		//LDA_predict_whole(years[i]);
		LDA_train (years[i]);
		LDA_predict(years[i]);
	}
    return 1;
}

// g++ -std=c++11 -Wall main.cpp -o main
//g++ -std=c++11 -Wall test.cpp -lmlpack -O1 -larmadillo -o test
