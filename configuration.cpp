#include "configuration.h"

#include <iostream>

using namespace std;

Configuration::Configuration(int n_machines, int n_jobs)
{

  cout << "Hello getting in the constructor"<< endl;
  this -> n = n_machines;
  this-> m = n_jobs;

  cout << "exiting the constructor" << endl;
}


void Configuration::print(){
  cout << "n = " << this -> n <<endl;
  cout << "m = " << this -> m <<endl;
}
