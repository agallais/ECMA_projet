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


    
    Solution Solution::swap(int jobA, int jobB){
        int swapMachine = this-> affectation[jobA];
        
        Solution swappedSolution = Solution(this-> numberOfJobs, this->numberOfMAchines);
        for(int i = 0; i < this-> numberOfJobs; ++i){
            swappedSolution.affectation[i] = this->affectation[i];
        }
        swappedSolution.affectation[jobA] = swappedSolution.affectation[jobB];
        swappedSolution.affectation[jobB] = swapMachine;
        return swappedSolution;
    };


    void Solution::shift(int i){
        
        
        return ;
    };

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

        return;
    };

    void Solution::generate(){
        return;
    };

