#include <iostream>
#include <mlpack/core.hpp>
#include <mlpack/methods/linear_regression/linear_regression.hpp>
#include <cmath>  
#include "team_id_processing.cpp"
#include "month_id_processing.cpp"
#include "data_IO.cpp"

using namespace std;
using namespace mlpack;
using namespace mlpack::regression;
using namespace arma;

int dateTOseason (const std::string &date) {
	std::string::size_type sz;
	double year = std::stod(date.substr(0, 4),&sz);
	double month = std::stod(date.substr(4, 2),&sz);
	if (month > 6) {
 		return (int)year;
	} else {
		return (int)(year - 1);
	}
}

std::vector<double> search_row(double date, std::vector<std::vector<double> >& data_matrix) {
	std::vector<double> record;
	for (unsigned i = 0; i < data_matrix.size(); i++) {
			if ((int)data_matrix[i][0] == (int)date) {
				for (unsigned j = 0; j < data_matrix[i].size(); j++) {
					//std::cout<<data_matrix[i][j]<<" ";
					record.push_back(data_matrix[i][j]);
				}
				break;
			} 
	}
	return record;
}

std::vector<double> concatenate_record(std::vector<double>& host_record, std::vector<double>& visitor_record){
		std::vector<double> host_visitor;
		host_visitor.resize(host_record.size() + visitor_record.size());
		std::merge (host_record.begin(),host_record.end(),visitor_record.begin(),visitor_record.end(),host_visitor.begin());
	return host_visitor;
}

void testingDatePrepare(const std::string &date, const std::string &hostTeam,  const std::string &visitorTeam) {
	std::string::size_type sz;
	string year = std::to_string(dateTOseason (date));
	//std::cout<<year<<endl;	
	
	string inputFileHost = "dataSet/" +  year + "/" + year + hostTeam + "_data_set.csv";
	string inputFileVisitor = "dataSet/" +  year + "/" + year + visitorTeam + "_data_set.csv";
	
	std::vector<std::vector<double> > hostData = file_read_formation_double (inputFileHost);
	std::vector<std::vector<double> > visitorData = file_read_formation_double (inputFileVisitor);
	std::vector<double> hostRecord = search_row(std::stod(date,&sz), hostData);
	std::vector<double> visitorRecord = search_row(std::stod(date,&sz), visitorData);
	std::vector<double> host_visitor;
	if (hostRecord.size() > 0 && visitorRecord.size() > 0) {
				host_visitor = concatenate_record(hostRecord, visitorRecord);
	} 	
	string testFile = "dataSet/testFile.csv"; 
	std::vector<double> trainData;
	trainData.resize(host_visitor.size() - 6, 0);
	//std::cout<<host_visitor.size()<<endl;
	//std::cout<<trainData.size()<<endl;
	for (unsigned i = 0; i < trainData.size(); i++) {
		if (i < 8) {
			trainData[i] = host_visitor[i + 3];
		} else {
			trainData[i] = host_visitor[i + 6];
		}
		std::cout<<trainData[i]<<endl;
	}
	file_write_formation_double_line (testFile, trainData); 
	arma::mat dataset;
  	data::Load(testFile, dataset, true);
	arma::mat normalise_mat =normalise(dataset);
	data::Save(testFile, normalise_mat);
}


std::vector<double> LDA_predict_single(const std::string &date) {
	string year = std::to_string(dateTOseason (date));	
	string modelFile = "dataSet/LDA_result/" + year + "LDA_model.csv";
	//std::cout<<modelFile<<endl;
	string testFile = "dataSet/testFile.csv"; 
	
	LinearRegression lr;
  	lr = LinearRegression(modelFile);
	
	arma::mat points;
	//arma::vec points;    	
	data::Load(testFile, points, true);
    	
  	arma::vec predictions;
    	lr.Predict(points, predictions);

	string predictFile = "dataSet/testResultFile.csv";
   	data::Save(predictFile, predictions, true);

	std::vector<double> predictResult = read_line_double (predictFile);

	return predictResult;
}


int main(int argc, char *argv[]) {
	  if (argc > 1) {
		//std::cout<<argc<<endl;
		string input = argv[1];
		string date = input.substr(0, 8);
		string hostTeam = input.substr(8, 3);
		string visitorTeam = input.substr(11);
		//std::cout<<date<<endl;
		testingDatePrepare(date, hostTeam, visitorTeam);
		std::vector<double> predictResult = LDA_predict_single(date);
			if (predictResult.size() > 0) {
				std::cout<<predictResult[0]<<endl;
			} else {
				std::cout<<"No Prediction!"<<endl;
			}

	  } else {
	  	std::cout<<"Please choosing a correct game to predict!"<<endl;
	  }
    return 1;
}
