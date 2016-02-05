#include <iostream>
#include <mlpack/core.hpp>

#include <mlpack/methods/hmm/hmm.hpp>
#include <mlpack/methods/hmm/hmm_util.hpp>

#include <mlpack/methods/gmm/gmm.hpp>



using namespace mlpack;
using namespace mlpack::hmm;
using namespace mlpack::distribution;
using namespace mlpack::util;
using namespace mlpack::gmm;
using namespace mlpack::math;
using namespace arma;
using namespace std;

int main()
{
  string year = "2014";
  string team = "GSW";
  string col = "0";

	string inputFile = "state_data/" + year + "/" + year + team + "_state_col" + col + ".csv";
	string hmm_model = "simulation_data/" + year + "/" + year + team + "sim_col" + col + ".xml";
  vector<mat> trainSeq;
 
   
    trainSeq.resize(1);
    data::Load(inputFile, trainSeq[0], true);
	std::cout<<trainSeq[0].n_rows <<endl;
for (size_t i = 0; i < trainSeq.size(); ++i)
      if (trainSeq[i].n_rows > 1)
       std::cout << "Error in training sequence " << i << ": only "<< "one-dimensional discrete observations allowed for discrete "<< "HMMs!" << endl;

      size_t maxEmission = 0;
      for (vector<mat>::iterator it = trainSeq.begin(); it != trainSeq.end();
           ++it)
      {
        size_t maxSeq = size_t(as_scalar(max(trainSeq[0], 1))) + 1;
        if (maxSeq > maxEmission){
          maxEmission = maxSeq;
	}
      }

	std::cout<<maxEmission<<endl;
   HMM<DiscreteDistribution> hmm(1, DiscreteDistribution(1), 1e-5);
     hmm = HMM<DiscreteDistribution>(size_t(2),DiscreteDistribution(maxEmission));

      hmm.Train(trainSeq); 
    SaveRestoreUtility sr;
    SaveHMM(hmm, sr);
    sr.WriteFile(hmm_model);
	return 1;


}
