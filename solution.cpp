#include "solution.h"

#include <vector>

using namespace std;

Solution::Solution(int n_jobs, int n_machines){
        this -> affectation = vector<int> (n_jobs);
        for (int i = 0; i < n_jobs; i++){
            this-> affectation[i] = 0;
        }
        this->numberOfJobs = n_jobs;
        this->numberOfMAchines = n_machines;
    }


    
    void Solution::swap(int jobA, int jobB){
        int swapMachine = this-> affectation[jobA];
        this-> affectation[jobA] = this->affectation[jobB];
        this-> affectation[jobB] = swapMachine;
        return;
    };
    void Solution::shift(int i){
        
        
        return;
    };

    void Solution::generate(){
        return;
    };

