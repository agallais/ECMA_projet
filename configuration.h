#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <vector>

#include "Solution.h"

using namespace std;


// This class should describe the data file, once it is read
class Configuration{

public :

//This must go private
int n;
int m;
vector<vector<int> > c;
vector<vector<int> > a;
vector<int>  b;


Configuration(int n_machines, int n_jobs , vector<vector<int> > cost,vector<vector<int> > a, vector<int> bound );

int cost(Solution solution);
// To display the main points of the configuration
void print();

};
#endif
