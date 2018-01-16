#include "configuration.h"

#include <iostream>

using namespace std;

Configuration::Configuration(int n_machines, int n_jobs , vector<vector<int> > cost, vector<vector<int> > a, vector<int>  bound)
{

  this -> n = n_machines;
  this-> m = n_jobs;
  this-> c = cost;
  this-> a = a;
  this-> b = bound;
}


void Configuration::print(){
  cout << "n = " << this -> n <<endl;
  cout << "m = " << this -> m <<endl;
  cout << "a =" ;
  for(int j = 0; j < m ; j ++){
    for(int i = 0; i < n ; ++i){
      cout << a[j][i] << " ";
    }
    cout << endl;
  }
  cout << "b =  ";
  for (int j = 0; j < m; ++j){


    cout << this->b[j] << " ";
  }
cout << endl;

}


int Configuration::cost(Solution sol){


  return 0;
}