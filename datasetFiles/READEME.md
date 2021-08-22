# Dataset Files

## Description
This folder contains the dataset used in [Keystroke Dynamics - Benchmark Data Set](https://www.cs.cmu.edu/~keystroke/) (DSL-StrongPasswordData.csv) divided into 4 txt files.
All of these files have been parsed in Matlab to accomodate the SimulateKeystrokes.cpp script.

The reasoning for dividing it into 4 files is because the run time of the cpp script can be quite long (6 hours for just one file).


## Format
The format of the files are the following:

user_id  |   session  |    repetition   |   typeOfKey:keyCode:timeSinceLastKey,typeOfKey:keyCode:timeSinceLastKey,typeOfKey:keyCode:timeSinceLastKey,............

