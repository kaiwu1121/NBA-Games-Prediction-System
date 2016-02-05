#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
//#include "team_id_processing.cpp"
//#include "month_id_processing.cpp"
//#include "data_IO.cpp"
//#include "feature_label_processing.cpp"

using namespace std;  

std::vector<std::vector<double> > vh_processing (std::vector<std::vector<double> >& data_matrix, int vh) {
  int rows = data_matrix.size();
  int cols = data_matrix[0].size();
  std::vector<std::vector<double> > vh_data;
  vh_data.resize(rows, std::vector<double> (cols, 0));
  std::vector<double> sum_vh;
  sum_vh.resize(cols, 0);
  int num_vh = 0;
  for (int i = 0; i < rows; i++) {
	if (i > 0 && data_matrix[i - 1][1] == vh) {
		num_vh++;
	}
	//int index = i+1;
	//std::cout<<index<<" "<<data_matrix[i][0]<<" ";
	for (int j = 0; j < cols; j++) {
	    if (j < 3 || i == 0) {
		if (j < 3) {
			vh_data[i][j] = data_matrix[i][j];	
		} else {
			vh_data[i][j] = 0;
		}
	    } else {
			if (data_matrix[i - 1][1] == vh) {
				sum_vh[j] += data_matrix[i - 1][j];
				vh_data[i][j] = sum_vh[j] / num_vh;
			} else {
				vh_data[i][j] = vh_data[i - 1][j];
			}	
		}
	}
	//std::cout<<sum_vh[cols - 1]<<" "<<num_vh<<endl;
  }
  return vh_data;
}

std::vector<std::vector<double> > vh_connection (std::vector<std::vector<double> > & hostData, std::vector<std::vector<double> > &visitorData) {
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

void vh_average_processing (const std::string &year, const std::string &team) {
	// setting input and output filename
	string input_dir = "formation_data";
	string output_dir = "host_visitor_data";
    	string fileformat = ".csv";	
	string input_filename = input_dir + "/" + year + "/" + year + team + "_formation" +fileformat;
  	string output_filename_host = output_dir + "/" + year + "/" + year + team + "_host" +fileformat;
	string output_filename_visitor = output_dir + "/" + year + "/" + year + team + "_visitor" +fileformat;
	//read formation data from file
	std::vector<std::vector<double> > data_matrix = file_read_formation_double (input_filename);
	//calculate vh rate
	std::vector<std::vector<double> > host_data = vh_processing(data_matrix, 1);
	std::vector<std::vector<double> > visitor_data = vh_processing(data_matrix, 0);
	//feature_label
	std::vector<std::vector<double> > feature_data_host = feature_processing (host_data);
	std::vector<std::vector<double> > feature_data_visitor = feature_processing (visitor_data);
	string output_filename_feature_h = output_dir + "/" + year + "/" + year + team + "_host_" + "_featureOnly" +fileformat;
	string output_filename_feature_v = output_dir + "/" + year + "/" + year + team + "_visitor_" + "_featureOnly" +fileformat;
	//write vh rate into file
	file_write_formation_double (output_filename_host, host_data);
	file_write_formation_double (output_filename_visitor, visitor_data);
	file_write_formation_double (output_filename_feature_h, feature_data_host);
	file_write_formation_double (output_filename_feature_v, feature_data_visitor);

	//vh record connection
	std::vector<std::vector<double> >  vh_data = vh_connection (host_data, visitor_data);
	string vhFile = output_dir + "/" + year + "/" + year + team + "_vh" +fileformat;	
	file_write_formation_double (vhFile, vh_data);
}

/*
int main (){
	string year = "2014";
	//string team = "GSW";
	//vh_average_processing (year, team);
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		vh_average_processing (year, team[i]); 
	}
    return 1;
}*/

// g++ -std=c++11 -Wall main.cpp -o main
