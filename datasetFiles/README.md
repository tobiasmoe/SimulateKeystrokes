# Dataset Files

## Description
This folder contains the dataset used in [Keystroke Dynamics - Benchmark Data Set](https://www.cs.cmu.edu/~keystroke/) (DSL-StrongPasswordData.csv) divided into 4 txt files. All of these files have been parsed in Matlab to accomodate the SimulateKeystrokes.cpp script.

The reasoning for dividing it into 4 files is because the run time of the cpp script can be quite long (6 hours for just one file).

## Format

The format of the txt files are:
user_id | session | repetition | typeOfKey:keyCode:timeSinceLastKey
------------ | ------------- | ------------- | -------------
1 | 1 | 1 | 0:190:0,1:190:149,0:84:249,1:84:107,0:73:61,1:73:117,0:69:104
1 | 1 | 2 | 0:190:0,1:190:111,0:84:234,1:84:69,0:73:59,1:73:91,0:69:45,1:69:83
1 | 1 | 3 | 0:190:0,1:190:133,0:84:74,1:84:73,0:73:56,1:73:82,0:69:72,1:69:81

The last entry is repeating until the password phrase is complete (i.e. it is longer than the example)
