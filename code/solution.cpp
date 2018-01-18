#include "solution.h"

#include <vector>

using namespace std;

Solution::Solution(int n_jobs, int n_machines){
        this -> affectation = vector<int> (n_jobs);
        this -> violationOfConstraint = vector<int> (n_machines);
        for (int i = 0; i < n_jobs; i++){
            this-> affectation[i] = 0;
        }
        for (int j = 0; j < n_machines; j++){
            this-> violationOfConstraint[j] = 0;
        }
        this->numberOfJobs = n_jobs;
        this->numberOfMAchines = n_machines;
        //cout << "Constructor OK" << endl;
    }


bool Solution::isEqual(Solution sol){
  // We just need to check if the two vectors are equals. It is not enough, but should work to get improvement
  bool result = true;
  std::vector<int>::iterator solIterator = sol.affectation.begin();
  for(std::vector<int>::iterator v = this-> affectation.begin(); v != this->affectation.end(); v++){
    std::cout << *solIterator << '\n';
    std::cout << *v << '\n';
  }
  return result;

}

    Solution Solution::swap(int jobA, int jobB){
        int swapMachine = this-> affectation[jobA];

        Solution swappedSolution = Solution(this-> numberOfJobs, this->numberOfMAchines);
        for(int i = 0; i < this-> numberOfJobs; ++i){
            swappedSolution.affectation[i] = this->affectation[i];
        }
        swappedSolution.affectation[jobA] = swappedSolution.affectation[jobB];
        swappedSolution.affectation[jobB] = swapMachine;
        return swappedSolution;
    }


    void Solution::shift(int job, int machine){

        this-> affectation[job] = machine;

        return ;
    }

    void Solution::print(){

        for( int i = 0 ; i < this->numberOfJobs; ++i){
            cout << this->affectation[i] << " ";
        }
        cout <<endl;

        for(int j = 0 ; j < this->numberOfMAchines; j++){
            cout << "Machine "<< j << endl;
            for( int i = 0 ; i < this->numberOfJobs; ++i){
            if(this->affectation[i] == j){
            cout << i << " ";
            }

        }
        cout << endl;
        }

        for(int j = 0 ; j < this->numberOfMAchines; j++){
          std::cout<< this->violationOfConstraint[j] << endl;
        }

        return;
    }

    bool Solution::isAConstraintViolated(){
      bool result = false;
      for(int i = 0; i < this->numberOfMAchines; i++){
        if(this->violationOfConstraint[i] > 0){
          result = true;
          return true;
        }
      }
      return result;
    }





    void Solution::generate(){
        return;
    }
