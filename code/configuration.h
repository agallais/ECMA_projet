#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <vector>

#include "solution.h"

using namespace std;


// This class should describe the data file, once it is read
class Configuration{

public :

//This must go private
// n is machines, m is jobs
int n;

int m;
vector<vector<int> > c;
vector<vector<int> > a;
vector<int>  b;


Configuration(int n_machines, int n_jobs , vector<vector<int> > cost,vector<vector<int> > a, vector<int> bound );


// This function is to compute the cost for the heuristic problem, not the cost in the sense of the master problem
int cost(Solution& solution, float rho);

int trueCost(Solution solution);

Solution generateSol();


void improveConstraints(Solution solution);
// To display the main points of the configuration
void print();


};
#endif
