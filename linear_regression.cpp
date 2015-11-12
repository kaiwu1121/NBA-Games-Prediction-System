#include <mlpack/methods/linear_regression/linear_regression.hpp>

using namespace std;
using namespace mlpack::regression;


void pre_LDA(const std::string &year) {
	
}

void linear_regression (const std::string team1) {
	//Generating a model.....
	arma::mat data; // The dataset itself.
	arma::vec responses; // The responses, one row for each row in data.
	// Regress.
	LinearRegression lr(data,responses);
	// Get the parameters, or coefficients.
	arma::vec parameters = lr.Parameters();
	
	//Prediction.....
	// The dataset we want to predict on; each row is a data point.
	arma::mat points;
	// This will store the predictions; one row for each point.
	arma::vec predictions;
	lr.Predict(points, predictions); // Predict.
	// Now, the vector 'predictions' will contain the predicted values.
}
