#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <mlpack/core.hpp>
#include <mlpack/methods/pca/pca.hpp>
#include "team_id_processing.cpp"
#include "month_id_processing.cpp"
#include "data_IO.cpp"
#include "feature_label_processing.cpp"


using namespace std;
using namespace mlpack;
using namespace mlpack::pca;

std::vector<double> search_row(double date, std::vector<std::vector<double> >& data_matrix) {
	std::vector<double> record;
	for (unsigned i = 0; i < data_matrix.size(); i++) {
			if ((int)data_matrix[i][0] == (int)date) {
				for (unsigned j = 0; j < data_matrix[i].size(); j++) {
					record.push_back(data_matrix[i][j]);
				}
				break;
			} 
	}
	return record;
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

void realTrain_set(const std::string &year, std::string &type) {

	
	string input_dir = "schedule";
	string output_dir = type + "_data";
    	string fileformat = ".csv";
	if (type.compare("cluster") == 0) {
		string input_filename = input_dir + "/" + "output" + "/" + year + "schedule_foramtion" +fileformat;
	} else {
		
	}	
	string input_filename = input_dir + "/" + "output" + "/" + year + "schedule_foramtion" +fileformat;
	std::vector<std::vector<double> > schedule_matrix = file_read_formation_double(input_filename);
	std::vector<std::vector<double> > record_set;
	std::vector<double> result_set;
 
	int times = 0;
	for (unsigned i = 0; i < schedule_matrix.size(); i++) {
		double date = schedule_matrix[i][0];
		double host_teamid = double(schedule_matrix[i][1]); 
		double visitor_teamid = double(schedule_matrix[i][3]);
		string host_team = team_idTOname(schedule_matrix[i][1]);
		string visitor_team = team_idTOname(schedule_matrix[i][3]);
		double result = -1;
		if (schedule_matrix[i][2] > schedule_matrix[i][4]) {
			result = 1;
		}
		//std::cout<<host_team<<" VS "<<visitor_team<<" "<<result<<" "<<date<<endl;
		string host_team_file;
		string visitor_team_file;
		if (type.compare("simulation") == 0) {
			host_team_file = "data_set/" + year + "/" + year + host_team + "_data_set_real" + fileformat;
			visitor_team_file = "data_set/" + year + "/" + year + visitor_team + "_data_set_real" + fileformat;
		} else if (type.compare("host_visitor") == 0) {
			host_team_file = output_dir + "/" + year + "/" + year + host_team + "_host" + fileformat;
			visitor_team_file = output_dir + "/" + year + "/" + year + visitor_team + "_visitor" + fileformat;
		} else if (type.compare("lastN") == 0) { 
			host_team_file = output_dir + "/" + year + "/" + year + host_team + "_last_8" + fileformat;
			visitor_team_file = output_dir + "/" + year + "/" + year + visitor_team + "_last_8" + fileformat;		
		} else if(type.compare("cluster") == 0) {
			string cluster_team_file = "season_summary/" + year + "/" + "output" + "/" + year + "_cluster_team_output" + fileformat;	
			std::vector<std::vector<double> > team_clusters = file_read_formation_double (cluster_team_file);
			int host_clusterid, visitor_clusterid;
			for (unsigned cluster_index = 0; cluster_index < team_clusters.size(); cluster_index ++) {
				if ( std::find(team_clusters[cluster_index].begin(), team_clusters[cluster_index].end(), host_teamid) != team_clusters[cluster_index].end() ) {
							   	host_clusterid = (int)cluster_index;
				}
				if ( std::find(team_clusters[cluster_index].begin(), team_clusters[cluster_index].end(), visitor_teamid) != team_clusters[cluster_index].end() ) {
							   	visitor_clusterid = (int)cluster_index;
				}
			}
			host_team_file = type + "_team_data" + "/" + year + "/" + year + host_team + "_" + type + "_" + std::to_string(visitor_clusterid) + fileformat;
			visitor_team_file = type + "_team_data" + "/" + year + "/" + year + visitor_team + "_" + type + "_" + std::to_string(host_clusterid) + fileformat;
		} else {
			host_team_file = output_dir + "/" + year + "/" + year + host_team + "_" + type + fileformat;
			visitor_team_file = output_dir + "/" + year + "/" + year + visitor_team + "_" + type + fileformat;
		}


		std::vector<std::vector<double> > host_data = file_read_formation_double (host_team_file);
		std::vector<std::vector<double> > visitor_data = file_read_formation_double (visitor_team_file); 
		std::vector<double> host_record = search_row(date, host_data);
		std::vector<double> visitor_record = search_row(date, visitor_data);


		

			if (host_record.size() > 0 && visitor_record.size() > 0) {
				times++;
				std::vector<double> host_visitor = concatenate_record(host_record, visitor_record);
				result_set.push_back(result);
				record_set.push_back(host_visitor);
			times++;
			} 
	}
	//std::cout<<times<<endl; 

	//std::cout<<schedule_matrix.size()<<" "<<times<<endl;
	string training_file = "wholeTrainingset/" + year + "training_set_whole" + fileformat; 
	
	std::vector<std::vector<double> > trainData;
	trainData.resize(record_set.size(), std::vector<double>(record_set[0].size() - 6, 0));
	
	for (unsigned i = 0; i < trainData.size(); i++) {
		for (unsigned j = 0; j < trainData[i].size(); j++) {
			if (j < 8) {
				trainData[i][j] = record_set[i][j + 3];
			} else {
				trainData[i][j] = record_set[i][j + 6];
			}
		}
	}
	file_write_formation_double (training_file, trainData);
	arma::mat dataset;
  	data::Load(training_file, dataset, true);
	arma::mat normalise_mat =normalise(dataset);
	string training_normalise_file = "wholeTrainingset/" + year + "training_set_normalise_whole" + fileformat; 
	data::Save(training_normalise_file, normalise_mat);
	string label_file = "wholeTrainingset/" + year + "label_set_whole" + fileformat; 
	file_write_formation_double_line (label_file, result_set); 
}

int main () {
	std::vector<string> years = {"2010", "2011", "2012", "2013", "2014"};
	std::vector<string> teams = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};
	//read_schedule (year);
	for (unsigned year = 0; year < years.size(); year++){
	  for (unsigned team = 0; team < teams.size(); team++) {

		}
	}
	return 1;
}
