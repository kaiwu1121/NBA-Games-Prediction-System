#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <eigen/Eigen/Dense>
#include <eigen/Eigen/Eigenvalues>

using namespace std;
using namespace Eigen;  

int teamid (std::string team) {
	if (team.compare("BOS") == 0) {
		return 1;
	} else if (team.compare("BKN") == 0) {
		return 2;
	} else if (team.compare("NYK") == 0) {
		return 3;
	} else if (team.compare("PHI") == 0) {
		return 4;
	} else if (team.compare("TOR") == 0) {
		return 5;
	} else if (team.compare( "CHI") == 0) {
		return 6;
	} else if (team.compare("CLE") == 0) {
		return 7;
	} else if (team.compare("DET") == 0) {
		return 8;
	} else if (team.compare("IND") == 0) {
		return 9;
	} else if (team.compare("MIL") == 0) {
		return 10;
	} else if (team.compare("ATL") == 0) {
		return 11;
	} else if (team.compare("CHA") == 0) {
		return 12;
	} else if (team.compare("MIA") == 0) {
		return 13;
	} else if (team.compare("ORL") == 0) {
		return 14;
	} else if (team.compare("WAS") == 0) {
		return 15;
	} else if (team.compare("DEN") == 0) {
		return 16;
	} else if (team.compare("MIN") == 0) {
		return 17;
	} else if (team.compare("OKC") == 0) {
		return 18;
	} else if (team.compare("POR") == 0) {
		return 19;
	} else if (team.compare("UTA") == 0) {
		return 20;
	} else if (team.compare("GSW") == 0) {
		return 21;
	} else if (team.compare("LAC") == 0) {
		return 22;
	} else if (team.compare("LAL") == 0) {
		return 23;	
	} else if (team.compare("PHX") == 0) {
		return 24;
	} else if (team.compare("SAC") == 0) {
		return 25;
	} else if (team.compare("DAL") == 0) {
		return 26;
	} else if (team.compare("HOU") == 0) {
		return 27;
	} else if (team.compare("MEM") == 0) {
		return 28;
	} else if (team.compare("NOP") == 0) {
		return 29;
	} else if (team.compare("SAS") == 0) {
		return 30;
	}
	return -1;
}

std::vector<std::vector<double> > data_read(const std::string &filename) {
    ifstream file (filename); 
    std::string data_line;
    std::vector<std::vector<double> > data_matrix;
    std::string::size_type sz;
    std::string number;
    while ( file.good() )
    {
        while (getline ( file, data_line)) { 
		//std::cout<<data_line<<endl;
		int att_index = 0;
		std::istringstream is(data_line);
		std::vector<double> items;
        	while(std::getline(is, number, ',')) 
        	{
			if (att_index == 0) {
				std::size_t first = number.find("-");
				std::size_t second = number.find("-",first + 1);
				string year = number.substr(0, first);
				string month = number.substr(first + 1, 2);
				string day = number.substr(second + 1);
				string date = year+month+day;
				items.push_back(std::stof(date,&sz));
				//std::cout<<date<<endl;
			} else if (att_index == 1) {
				if (number.find("@") != string::npos) {
					items.push_back(0.0);
					std::size_t pos = number.find("@");						
					int vteam = teamid(number.substr(pos + 2));
					items.push_back((double)vteam);
				} else {
					items.push_back(1.0);
					std::size_t pos = number.find("vs.");
					int vteam = teamid(number.substr(pos + 4));
					items.push_back((double)vteam);
				}			
			} else if (att_index == 22){
				if (number.compare("W") == 0) {
					items.push_back(1.0);
				} else {
					items.push_back(0.0);
				}
			} else {
				items.push_back(std::stof(number,&sz));
			}
			att_index++;
			
            		//cout << number << "  ";
        	}
		data_matrix.push_back(items);
        	//cout << endl;
	}
    }
	return data_matrix;
}


/*
std::vector<std::vector<double> >data_read(const std::string &filename){
  std::ifstream data_file(filename.c_str());
  std::vector<std::vector<double> > data_matrix;
  std::string data_line;
  if (data_file.is_open()) {
    while (!data_file.eof()) {
      while( std::getline(data_file,data_line)) {
	//if (!data_file.eof()) {
	  std::istringstream iss_data(data_line);
	  std::vector<double> data;
	  double str_data;
	  while (iss_data>>str_data) {
	    // double str_data;
	    //iss_data>>str_data;
	    data.push_back(str_data);
	  }
	  data_matrix.push_back(data);
	  //}
	}
    }
  }
   return data_matrix;
}*/

std::vector<double> cal_MeanVector(std::vector<std::vector<double> >& matrix) {
  int row = matrix.size();
  int col = matrix[0].size();
  std::vector<double> mean_vector;
  mean_vector.resize(col, 0);
  for (int i = 0; i < row; i++) {
	for (int j = 0; j < col; j++) {
		mean_vector[j] += matrix[i][j];
	}	
  }
  for (unsigned i = 0 ;i < mean_vector.size(); i++){
    mean_vector[i] = mean_vector[i] / row;
  }
  return mean_vector;
}

std::vector<std::vector<double> > substract_meanVector (std::vector<std::vector<double> >& matrix, std::vector<double>& mean_vector) {
  int row = matrix.size();
  int col = matrix[0].size();
  std::vector<std::vector<double> > sub_matrix;
  sub_matrix.resize(row, std::vector<double>(col, 0));
  for (unsigned i = 0; i < matrix.size(); i++) {
    for(unsigned j = 0; j < matrix[0].size(); j++) {
      sub_matrix[i][j] = matrix[i][j] - mean_vector[j];
    }
  }
  return sub_matrix;
}

std::vector<std::vector<double> > cal_covMatrix (std::vector<std::vector<double> >& sub_matrix) {
  int row = sub_matrix.size();
  int col = sub_matrix[0].size();
  std::vector<std::vector<double> > cov_matrix;
  std::vector<std::vector<double> > work_matrixT;
  cov_matrix.resize(col, std::vector<double>(col, 0));
  work_matrixT.resize(col, std::vector<double>(row,0));
  for (int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++) {
      work_matrixT[j][i] = sub_matrix[i][j];
    }
  }
std::cout<<"sub_matrix_T"<<endl;
  for (int i = 0; i < col; i++) {
    for(int j = 0; j < row; j++) {
      std::cout<<work_matrixT[i][j]<<" ";
    }
	std::cout<<endl;
  }

 for (int index = 0; index < col; index++) {
    for (int i = 0; i < col; i++) {
      double sum = 0;
      double cov = 0;
      for (int j = 0; j < row; j++) {
        sum = sum + (work_matrixT[i][j] * sub_matrix[j][index]);
      }
      cov = sum / (row - 1);
      cov_matrix[index][i] = cov;
     }
  }
  return cov_matrix;
} 


void eigen_value_vector (std::vector<std::vector<double> >& cov_matrix) {
	MatrixXd A(cov_matrix.size(),cov_matrix[0].size());
	A.fill(0); 
	for (unsigned i = 0; i < cov_matrix.size(); i++) {
		for (unsigned j = 0; j < cov_matrix[0].size(); j++) {
			A(i,j) = cov_matrix[i][j];
		}
	} 
	EigenSolver<MatrixXd> eig(A);
	A.eigenvalues();  
	std::cout<<"eigenvalue"<<endl;
	std::cout<<eig.eigenvalues()<<endl;
	std::cout<<eig.eigenvectors()<<endl;
	std::pair<double, std::vector<double> > eigen;
	//write eigenvalues and eigenvectors into file
	std::remove("eigenvalues.csv"); 
	ofstream outputFile;
	outputFile.open("eigenvalues.csv");
  	outputFile << eig.eigenvalues();
	outputFile.close();
	std::remove("eigenvectors.csv"); 
	outputFile.open("eigenvectors.csv");
  	outputFile << eig.eigenvectors();
	outputFile.close();
	// read into vector array
	ifstream file ("eigenvalues.csv"); 
    	std::string data_line;
    	std::vector<double> eigenvalue_matrix;
    	std::string::size_type sz;
    	while ( file.good() )
    	{
        	while (getline ( file, data_line)) { 
			std::size_t start = data_line.find("(");
			std::size_t end = data_line.find(","); 
			std::string str = data_line.substr (start + 1, end - start - 1);
			eigenvalue_matrix.push_back(std::stof(str,&sz));
		}
    	}
	for(unsigned i = 0; i < eigenvalue_matrix.size(); i++) {
		std::cout<<eigenvalue_matrix[i]<<"  ";
	}
	std::cout<<endl;
	/*ifstream file2 ("eigenvectors.csv"); 
    	std::string data_line2;
    	std::vector<std::vector<double> > eigenvector_matrix;
    	//std::string::size_type sz;
    	//std::string number;
    	while ( file2.good() )
    	{
        	while (getline ( file2, data_line2)) { 
			//std::cout<<data_line2<<"++++"<<endl;
			std::vector<double> items;
			//std::string data_str = data_line2;
			//std::pair<size_t, size_t> positions; // holds all the positions that sub occurs within str
			size_t start = data_line2.find("(", 0);
			std::size_t end = data_line2.find(",",0); 
			while(start != string::npos && end != string::npos)
			{
				std::string str = data_line2.substr(start, end - start -1);
				std::cout<<str<<endl;
				items.push_back(std::stof(str,&sz));
   				//positions.push_back(start,end);
    				start = data_line2.find("(",end+1);
				end = data_line2.find(",",end+1);
			}
			eigenvector_matrix.push_back(items);
		}
    	}*/
/*	for(unsigned i = 0; i < eigenvector_matrix.size(); i++) {
		for(unsigned j = 0; j < eigenvector_matrix[0].size(); j++) {
			std::cout<<eigenvector_matrix[i][j]<<"  ";
		}	
		std::cout<<endl;
	}*/
}

std::vector<std::vector<double> > preprocessing (std::vector<std::vector<double> >& data_matrix) {
	int rows = data_matrix.size();
	int cols = data_matrix[0].size();
	std::vector<std::vector<double> > pre_data;
	pre_data.resize(rows, std::vector<double>(cols, 0));
	std::vector<double> sum;	
	sum.resize(cols,0);
	for (int i = 0; i < rows; i++) {	
		for (int j = 0 ; j < cols; j++) {
			if (j == 0 || j == 1 || j == 2) {
				pre_data[i][j] = data_matrix[i][j];
			} else {
				if (i == 0) {
					sum[j] = 0;
					pre_data[i][j] = sum[j];
				} else {
					sum[j] += data_matrix[i - 1][j];
					pre_data[i][j] = sum[j] / (i + 1);
				}	
			}
		}
	}
	return pre_data;
}

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

std::vector<std::vector<double> > vh_processing (std::vector<std::vector<double> >& data_matrix, int vh) {
  int rows = data_matrix.size();
  int cols = data_matrix[0].size();
  std::vector<std::vector<double> > vh_data;
  vh_data.resize(rows, std::vector<double> (cols, 0));
  std::vector<double> sum_vh;
  sum_vh.resize(cols, 0);
  int num_vh = 0;
  for (int i = 0; i < rows; i++) {
    if (data_matrix[i][1] == vh) { 
	num_vh ++;
	for (int j = 0; j < cols; j++){
		if (i == 0 || j < 3) {
			// sum_vh[j] = 0;	
			if (j < 3) {
				vh_data[i][j] = data_matrix[i][j];
			} else {
				vh_data[i][j] = 0;
			}
			
		} else {
			sum_vh[j] += data_matrix[i - 1][j];
	 	        vh_data[i][j] = sum_vh[j] / (num_vh - 1);		
		}	
	}
    } else {
	for (int j = 0; j < cols; j++){
		if (i == 0) {
			if (j < 3) {
				vh_data[i][j] = data_matrix[i][j];
			} else {
		  		vh_data[i][j] = 0;
			}
		} else {
			if (j < 3) {
				vh_data[i][j] = data_matrix[i][j];	
			} else {
				vh_data[i][j] = vh_data[i - 1][j];
			}
		}	
	}
    }
  }
 // std::cout<<sum_vh[cols - 1]<<endl;
  return vh_data;
}

std::vector<std::vector<double> > lastN_processing (std::vector<std::vector<double> >& data_matrix, int N) {
  int rows = data_matrix.size();
  int cols = data_matrix[0].size();
  std::vector<std::vector<double> > lastN_data;
  lastN_data.resize(rows, std::vector<double> (cols, 0));
  std::vector<double> sum_lastN_less;
  sum_lastN_less.resize(cols, 0);
  std::vector<double> sum_lastN;
  sum_lastN.resize(cols, 0);
  for (int i = 0; i < rows; i++) {
	if (i < N){
		for(int j = 0; j < cols; j++){
			if (i == 0) {
				if (j < 3) {
					sum_lastN_less[j] = data_matrix[i][j];
				} else {
					sum_lastN_less[j] = 0;
				}
				lastN_data[i][j] = sum_lastN_less[j];
			} else {
				if (j < 3) {
					lastN_data[i][j] = data_matrix[i][j]; 
				} else {
					sum_lastN_less[j] += data_matrix[i - 1][j];
					lastN_data[i][j] = sum_lastN_less[j] / i;	
				} 
			}
		}		
	} else {
		std::fill(sum_lastN.begin(), sum_lastN.end(), 0);
		for (int index = i - N; index < i; index ++) {
			for (int j = 0; j < cols; j++) {
				if (j > 3) {
					sum_lastN[j] += data_matrix[index][j];
				}
			}
		}
		for(int j = 0; j < cols; j++){
			if (j < 3) {
				lastN_data[i][j] = data_matrix[i][j];
			} else {
				lastN_data[i][j] = sum_lastN[j] / N; 
			}
		}

	}
  }
  return lastN_data;
}

int main (){
	// chose original data file	
  	string filename = "GSW2014";
	string fileformat = ".csv";
	string file = filename + fileformat;
	std::vector<std::vector<double> > data_matrix = data_read(file);
	string olddata = "_old";
	string olddatafile = filename + olddata + fileformat;
	std::cout<<olddatafile<<endl;
	std::remove("GSW2014_old.csv"); 
	ofstream outputFile;
	outputFile.open("GSW2014_old.csv");
 	std::cout<<"data_matrix:"<<endl;
	for (unsigned i = 0; i < data_matrix.size(); i++)
	{
	    for (unsigned j = 0; j < data_matrix[i].size(); j++)
	    {
		if ( j != data_matrix[i].size() - 1) {
			outputFile << data_matrix[i][j]<<",";
			//std::cout<<data_matrix[i][j]<<" ";
		} else {
			outputFile << data_matrix[i][j]<<"\n";
			//std::cout<<data_matrix[i][j]<<endl;
		}
	    }
	}
	outputFile.close();
	// calculate pre_data and write into pre data file.
	std::remove("GSW2014_overall.csv"); 
	outputFile.open("GSW2014_overall.csv");
	std::vector<std::vector<double> > overall_data = preprocessing (data_matrix);
	for (unsigned i = 0; i < overall_data.size(); i++)
	{
	    for (unsigned j = 0; j < overall_data[i].size(); j++)
	    {
		if ( j != overall_data[i].size() - 1) {
			outputFile << overall_data[i][j]<<",";
		} else {
			outputFile << overall_data[i][j]<<"\n";
		}
	    }
	}
	outputFile.close();
	// get feature data only
	std::vector<std::vector<double> > feature_data = feature_processing (overall_data);
	std::remove("GSW2014_feature.csv"); 
	outputFile.open("GSW2014_feature.csv");
	for (unsigned i = 0; i < feature_data.size(); i++)
	{
	    for (unsigned j = 0; j < feature_data[i].size(); j++)
	    {
		if ( j != feature_data[i].size() - 1) {
			outputFile << feature_data[i][j]<<",";
		} else {
			outputFile << feature_data[i][j]<<"\n";
		}
	    }
	}
	outputFile.close();
	// get win(1)-loss(0) label 
	std::vector<double> label = label_processing (data_matrix);
	std::remove("GSW2014_label.csv"); 
	outputFile.open("GSW2014_label.csv");
	for (unsigned i = 0; i < label.size(); i++)
	{
		outputFile << label[i]<<"\n";
	}
	outputFile.close();
	// calculating visitor games data;
	std::vector<std::vector<double> > visitor_data = vh_processing (data_matrix, 0);
	std::remove("GSW2014_visitor.csv"); 
	outputFile.open("GSW2014_visitor.csv");
	for (unsigned i = 0; i < visitor_data.size(); i++)
	{
	    for (unsigned j = 0; j < visitor_data[i].size(); j++)
	    {
		if ( j != visitor_data[i].size() - 1) {
			outputFile << visitor_data[i][j]<<",";
		} else {
			outputFile << visitor_data[i][j]<<"\n";
		}
	    }
	}
	outputFile.close();
	// calculating host games data;
	std::vector<std::vector<double> > host_data = vh_processing (data_matrix, 1);
	std::remove("GSW2014_host.csv"); 
	outputFile.open("GSW2014_host.csv");
	for (unsigned i = 0; i < host_data.size(); i++)
	{
	    for (unsigned j = 0; j < host_data[i].size(); j++)
	    {
		if ( j != host_data[i].size() - 1) {
			outputFile << host_data[i][j]<<",";
		} else {
			outputFile << host_data[i][j]<<"\n";
		}
	    }
	}
	outputFile.close();
	// calculating last N games data;
	std::vector<std::vector<double> > lastN_data = lastN_processing (data_matrix, 8); 
	std::cout<<lastN_data.size()<<" "<<lastN_data[0].size()<<endl;
	std::remove("GSW2014_lastN.csv"); 
	outputFile.open("GSW2014_lastN.csv");
	for (unsigned i = 0; i < lastN_data.size(); i++)
	{
	    for (unsigned j = 0; j < lastN_data[i].size(); j++)
	    {
		if ( j != lastN_data[i].size() - 1) {
			outputFile << lastN_data[i][j]<<",";
		} else {
			outputFile << lastN_data[i][j]<<"\n";
		}
	    }
	}
	outputFile.close();






  /*std::cout<<data_matrix.size()<<" "<<data_matrix[0].size()<<endl;
   std::vector<double> mean_vector;
  mean_vector = cal_MeanVector(data_matrix);
  //std::cout<<mean_vector.size()<<endl;
  std::cout<<"mean_vector:"<<endl;
    for (unsigned i = 0; i < mean_vector.size(); i++) {
    std::cout<<mean_vector[i]<<" ";
    }
    std::cout<<endl;

    std::cout<<endl<<"sub_matrix:"<<endl;
    std::vector<std::vector<double> >sub_matrix = substract_meanVector(data_matrix, mean_vector);
    for(unsigned i = 0; i < sub_matrix.size(); i++) {
      for(unsigned j = 0; j < sub_matrix[0].size(); j++) {
	std::cout<<sub_matrix[i][j]<<" ";
      }
      std::cout<<endl;
    }
    std::vector<std::vector<double> > covmatrix = cal_covMatrix(sub_matrix);
        std::cout<<"covMatrix:"<<endl;
    for(unsigned i = 0; i < covmatrix.size(); i++) {
      for(unsigned j = 0; j < covmatrix[0].size(); j++) {
	std::cout<<covmatrix[i][j]<<" ";
      }
      std::cout<<endl;
      }
	
    eigen_value_vector (covmatrix);*/
    return 1;
}

// g++ -std=c++11 -Wall main.cpp -o main
