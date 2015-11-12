#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std; 

std::vector<std::vector<double> > feature_processing (std::vector<std::vector<double> >& pre_data) {
	int rows = pre_data.size();
	int cols = pre_data[0].size();
	std::vector<std::vector<double> > feature_data;
	feature_data.resize(rows, std::vector<double>(cols - 4, 0));
	for (int i = 0; i < rows; i++) {	
		for (int j = 0 ; j < cols - 4; j++) {
			feature_data[i][j] = pre_data[i][j + 3];
		}
	}
	return feature_data;
}


std::vector<double> label_processing (std::vector<std::vector<double> >& data_matrix) {
	int rows = data_matrix.size();
	int cols = data_matrix[0].size();
	std::vector<double> label;
	label.resize(rows, 0);
	for (int i = 0; i < rows; i++) {	
		label[i] = data_matrix[i][cols - 1];
	}
	return label;
}


