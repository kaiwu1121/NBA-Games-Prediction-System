# NBA-Games-Prediction-System
NBA Prediction System Instruction

1. install Armadillo library, pack included in source code floder.
2. install MLPACK library, pack included in source code floder.
3. if just testing system, click the index.php file.
4. if want to check back-end code using command: g++ -std=c++11 -Wall <FILENAME> -lmlpack -O1 -larmadillo -o <OUTPUTNAME>
 

Code file usage:
1. data_formation.cpp -> formation_data   label
2. feature_file_processing.cpp -> feature_data  date
3. norm_processing.cpp -> stddev, normalise, mean data

hmm:
4. state_processing.cpp -> standardization, state data(obeservation sequence, label sequence)
5. hmm.cpp -> hmm model, hmm prediction data
6. simulation_recover.cpp -> sim_re data, performance data, pca data

win rate:
7. cal_overall_average.cpp -> overal average running
8. cal_vh_average.cpp -> host / visitor average running
9. cal_lastN_average.cpp -> last N games average running

10. team_data_connection.cpp -> data set each team
11  schedule_formation.cpp -> schedule_formation data
12. training_test_set_processing.cpp -> training/test data set
13. linear_regression.cpp -> prediction model and result


NBA system CODE
1. searchGame.cpp -> return games scheduel on search date
2. linearRegressionPredict-> return preidction according to date and team  example "20141225LALCHI"

