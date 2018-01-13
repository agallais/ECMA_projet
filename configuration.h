#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
using namespace std;


// This class should describe the data file, once it is read
class Configuration{

public :

int n;
int m;

Configuration(int n_machines, int n_jobs);

// To display the main points of the configuration
void print();


};
#endif
