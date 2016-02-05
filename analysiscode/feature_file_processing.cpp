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

void feature_file_processing (std::string &year,std::string &team) {
	string input = "formation_data";
	string output = "feature_data";
	string fileformat = ".csv";
	string inputfile = input + "/" + year + "/" + year + team +"_formation" + fileformat;
	string outputfile = output + "/" + year + "/" + year + team + "_feature" + fileformat;
	// get feature data only
	std::vector<std::vector<double> > formation_data =  file_read_formation_double (inputfile);
	std::vector<std::vector<double> > feature_data = feature_processing (formation_data);
	file_write_formation_double (outputfile, feature_data);
}


void date_file_processing (std::string &year,std::string &team) {
	string input = "formation_data";
	string output = "feature_data";
	string fileformat = ".csv";
	string inputfile = input + "/" + year + "/" + year + team +"_formation" + fileformat;
	string outputfile = output + "/" + year + "/" + year + team + "_date" + fileformat;
	// get date data only
	std::vector<std::vector<double> > formation_data =  file_read_formation_double (inputfile);
	std::vector<std::vector<double> > date_data = date_processing (formation_data);
	file_write_formation_double (outputfile, date_data);
}
/*

int main (){
	string year = "2014";
	//string team = "GSW";
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		feature_file_processing(year, team[i]);
		date_file_processing(year, team[i]);
	}
    return 1;
}
*/
// g++ -std=c++11 -Wall main.cpp -o main
