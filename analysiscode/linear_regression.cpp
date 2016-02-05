#include <iostream>
#include <mlpack/core.hpp>
#include <mlpack/methods/linear_regression/linear_regression.hpp>
#include <cmath>  
//#include "team_id_processing.cpp"
//#include "month_id_processing.cpp"
//#include "data_IO.cpp"

using namespace std;
using namespace mlpack;
using namespace mlpack::regression;
using namespace arma;

void LDA_train_whole () {
	  mat regressors;
	  mat responses;
	
	  string training_file = "wholeTrainingset/wholetraining_set_normalise_whole.csv"; 
	  string label_file = "wholeTrainingset/wholetraining_set_label_whole.csv"; 
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
	string outputFile = "LDA_result/LDA_model_whole.csv";
	data::Save(outputFile, lr.Parameters(), true);

}

void LDA_predict_whole(const std::string &year) {
	string type = "simulation";	
	string modelFile = "LDA_result/LDA_model_whole.csv";
	string testFile = "training_set/" + type + "/" + year + "/" + year + "training_set_normalise" + ".csv"; 
 string label_file = "training_set/" + type + "/" + year + "/" + year + "label_set" + ".csv"; 
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

/*
int main(int argc, char* argv[])
{	
	string year = "2014";
	LDA_train (year);
	LDA_predict(year);
	return 1;

}
*/




/*#include <iostream>
#include <mlpack/methods/linear_regression/linear_regression.hpp>
#include "team_id_processing.cpp"
#include "month_id_processing.cpp"
#include "data_IO.cpp"

using namespace std;
using namespace mlpack;
using namespace mlpack::regression;


void linear_regression (const std::string &year, const std::string &type) {
	//Generating a model.....
	string training_file = "training_set/" + type + "/" + year + "/" + year + "training_set" + ".csv"; 
	string label_file = "training_set/" + type + "/" + year + "/" + year + "label_set" + ".csv"; 
	arma::mat training_set; // The dataset itself.
	data::Load(training_file, training_set, true);


	std::vector<int> labels = read_line(label_file);
	arma::vec label_set(labels.size()); // The responses, one row for each row in data.
	int j = 0; 	
	for(vector<int>::const_iterator it = labels.begin(); it != labels.end(); ++it) {
    		label_set(j++) =  *it; 
		
	}
	label_set
	//data::Load(label_file, label_set, true);
	// Regress.
	LinearRegression lr(training_set,label_set);
	// Get the parameters, or coefficients.
	arma::vec parameters = lr.Parameters();
	
	//Prediction.....
	// The dataset we want to predict on; each row is a data point.
	arma::mat points;
	data::Load(training_file, points, true);
	// This will store the predictions; one row for each point.
	arma::vec predictions;
	lr.Predict(points, predictions); // Predict.
	// Now, the vector 'predictions' will contain the predicted values.
	string outputfile = "pre_results.csv";
	data::Save(outputfile, predictions);
	std::vector<int> p = read_line (outputfile);
	std::cout<<p.size()<<" "<<labels.size()<<endl;
	int num = 0;
	if (p.size() == labels.size()) {
		for (unsigned i = 0; i < p.size(); i++) {
			if (p[i] == labels[i]) {
				num++;
			}
		}
	}
	double rate = (double)num/(double)p.size();
	std::cout<<num<<"/"<<p.size()<<" "<<rate<<endl;
}

int main() {
	string year = "2014";
	string type = "overall";
	linear_regression (year, type);
	return 1;
}
*/




