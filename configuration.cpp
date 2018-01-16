#include "configuration.h"

#include <iostream>
#include <algorithm>


using namespace std;

Configuration::Configuration(int n_machines, int n_jobs , vector<vector<int> > cost, vector<vector<int> > a, vector<int>  bound)
{

  this -> n = n_machines;
  this-> m = n_jobs;
  this-> c = cost;
  this-> a = a;
  this-> b = bound;
}

// c[n_machines][n_job] and same for a 

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


  int total = 0;

  for(int i = 0; i < this-> n; i++){

    total += c[sol.affectation[i]][i];
  }

  // This is for the cost of the master problem, now we add the cost for violating the constraints

  int P = 0;
  vector<int> constraintViolation = vector<int>(this->m);
  bool aConstraintIsViolated = false;
  for (int j = 0; j < this->m; j++){

    int  totalForLignJ = 0;
    for(int i = 0 ; i < this->n ; i++){

      if (sol.affectation[i] == j){
     totalForLignJ += a[j][i]; 
      }

    }
    int si = b[j] - totalForLignJ;
    aConstraintIsViolated = (si > 0) && aConstraintIsViolated;
    constraintViolation[j] = max(si, 0);
    P += si;
    }
  // Technically we should add 
  
  total += P;

  return total;
}

Solution Configuration::generateSol(){

  Solution result = Solution(this-> n, this ->m);

  for (int i = 0; i < this->n; i++){

    int bestAffectation = 0;
    for (int j = 0; j < this -> m; j++){

      if (c[j][i] < c[bestAffectation][i]){

        bestAffectation = j;

      }
    }
    result.affectation[i] = bestAffectation;
  }

// Then it is evident that the cost of this solution is a inferior bound for the solution of the problem, but probably it does not match the constraints
}