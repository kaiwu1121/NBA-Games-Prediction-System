#include <iostream>
#include <mlpack/core.hpp>
#include <mlpack/methods/naive_bayes/naive_bayes_classifier.hpp>
#include <cmath>  
#include "team_id_processing.cpp"
#include "month_id_processing.cpp"
#include "data_IO.cpp"

using namespace mlpack;
using namespace mlpack::naive_bayes;
using namespace std;
using namespace arma;

int main(int argc, char* argv[])
{

	string year = "2014";
	string type = "host_visitor";	
  	string training_file = "training_set/" + type + "/" + year + "/" + year + "training_set" + ".csv"; 
	string label_file = "training_set/" + type + "/" + year + "/" + year + "label_set" + ".csv"; 
	mat trainingData;        
	data::Load(training_file, trainingData, true);
	
	  // Normalize labels.
	  Col<size_t> labels;
	  Row<size_t> labelst;
	  vec mappings;

	mat rawLabels;
    	data::Load(label_file, rawLabels, true, false);
	
       // Do the labels need to be transposed?
       if (rawLabels.n_rows == 1){
          rawLabels = rawLabels.t();
       }
	size_t n = 2;
	NaiveBayesClassifier<> nbc(trainingData, rawLabels, n);
      /*  data::NormalizeLabels(rawLabels.unsafe_col(0), labels, mappings);
	labelst = labels.t();

	 const bool incrementalVariance = true;

  // Create and train the classifier.
  	NaiveBayesClassifier<> nbc(trainingData, labelst, mappings.n_elem,incrementalVariance);
	Row<size_t> results;
  	nbc.Classify(trainingData, results);

  // Un-normalize labels to prepare output.
  vec rawResults;
  data::RevertLabels(results.t(), mappings, rawResults);*/



/*
    data::Save("p_result.csv", predictions, true);

	std::vector<int> labels = read_line(label_file);
	std::vector<int> p = read_line ("p_result.csv");
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
	std::cout<<num<<"/"<<p.size()<<" "<<rate<<endl;*/
}





