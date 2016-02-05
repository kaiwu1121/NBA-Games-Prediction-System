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

void testingDatePrepare(const std::string &date, const std::string &hostTeam,  const std::string &visitorTeam) {
	string year = date.substr(0, 4);
	string inputFileHost = "data_set/" +  year + "/" + year + hostTeam + "_data_set.csv";
	string inputFileVisitor = "data_set/" +  year + "/" + year + visitorTeam + "_data_set.csv";
	std::vector<std::vector<double> > hostData = file_read_formation_double (inputFileHost);
	std::vector<std::vector<double> > visitorData = file_read_formation_double (inputFileVisitor);
	std::vector<double> hostRecord = search_row(date, hostData);
	std::vector<double> visitorRecord = search_row(date, visitorData);
	std::vector<double> host_visitor;
	if (host_record.size() > 0 && visitor_record.size() > 0) {
				host_visitor = concatenate_record(host_record, visitor_record);
	} 	
	string testFile = "testFile.csv"; 
	std::vector<double> trainData;
	trainData.resize(host_visitor.size() - 3, 0);
	
	for (unsigned i = 0; i < trainData.size(); i++) {
		if (i < 8) {
			trainData[i] = host_visitor[i + 3];
		} else {
			trainData[i] = host_visitor[i + 6];
		}
	}
	file_write_formation_double_line (testFile, trainData);
}
/*
void LDA_train (const std::string &year) {
	  mat regressors;
	  mat responses;

	  //LinearRegression lr;
	  //lr.Lambda() = lambda;
	//string year = "2014";
	  string type = "simulation"; 
	//string training_file = "wholeTrainingset/" + year + "training_set_normalise_whole.csv";	
	  string training_file = "training_set/" + type + "/" + year + "/" + year + "training_set_normalise" + ".csv"; 
	//  string label_file = "wholeTrainingset/" + year + "label_set_whole.csv";
	string label_file = "training_set/" + type + "/" + year + "/" + year + "label_set" + ".csv"; 
	  data::Load(training_file, regressors, true);
	  data::Load(label_file, responses, true);
	   // LinearRegression lr;
	  //  lr = LinearRegression(regressors, responses.unsafe_col(0));

	//LinearRegression lr(training_set,label_set);
		// Get the parameters, or coefficients.
		//arma::vec parameters = lr.Parameters();

	    // Save the parameters.
	//mat regressors_norm = normalise(regressors);
	LinearRegression lr(regressors,responses.unsafe_col(0));
	string outputFile = "LDA_result/" + year + "LDA_model.csv";
	data::Save(outputFile, lr.Parameters(), true);

}

void LDA_predict(const std::string &year) {
	string type = "simulation";	
	//string modelFile = "LDA_result/" + year + "LDA_model_whole.csv";	
	string modelFile = "LDA_result/" + year + "LDA_model.csv";
	string testFile = "training_set/" + type + "/" + year + "/" + year + "training_set_normalise" + ".csv"; 
 	string label_file = "training_set/" + type + "/" + year + "/" + year + "label_set" + ".csv"; 
	// string label_file = "wholeTrainingset/" + year + "label_set_whole.csv";	
	LinearRegression lr;
  	lr = LinearRegression(modelFile);
	
	arma::mat points;
    	data::Load(testFile, points, true);
    	
    // Load the test file data.
   // arma::mat points;
   // data::Load(training_file, points, true);
  
    // Perform the predictions using our model.
    arma::vec predictions;
    lr.Predict(points, predictions);

    // Save predictions.
    //predictions = arma::trans(predictions);
	string predictFile = "LDA_result/" + year + "LDA_prediction.csv";
    data::Save(predictFile, predictions, true);

	std::vector<int> labels = read_line(label_file);
	std::vector<int> p = read_line (predictFile);
	int num = 0;
	if (p.size() == labels.size()) {
		for (unsigned i = 0; i < p.size(); i++) {
			if (p[i] > 0) {
				p[i] = 1;
			} else {
				p[i] = -1;
			}
			if (p[i] == labels[i]) {
				num++;
			}
		}
	}
	double rate = (double)num/(double)p.size();
	std::cout<<num<<"/"<<p.size()<<" "<<rate<<endl;
}


int main(int argc, char* argv[])
{	
	string year = "2014";
	LDA_train (year);
	LDA_predict(year);
	return 1;

}

*/
int main(int argc, char *argv[]) {
	  if (argc > 4) {
		string date = argv[1];
		string hostTeam = argv[2];
		string visitorTeam = argv[3];
		testingDatePrepare(date, hostTeam, visitorTeam);
		// std::cout<<"Date: "<<input<<endl; 
		/* std::vector<std::vector<double> > games = seachGamesbyDate(date);
		  if (games.size() > 0) {
			  for (unsigned i = 0; i < games.size(); i++) {
				for(unsigned j = 0; j < games[i].size(); j++) {
					if (j != games[i].size() - 1) {
						if (j == 1 || j == 3) {
							std::cout<<std::fixed<<team_idTOname(games[i][j])<<" ";
						} else {
							std::cout<<std::fixed<<(int)games[i][j]<<" ";
						}
					} else {
						std::cout<<std::fixed<<(int)games[i][j]<<endl;
					}
				}
			  }
		  } else {
		  	std::cout<<"No games today! Please choose another date!"<<endl;
		  }*/
	  } else {
	  	std::cout<<"Please choosing a correct game to predict!"<<endl;
	  }
	
	//string date = "20101026";
	
    return 1;
}
