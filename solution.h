#ifndef SOLUTION_H
#define SOLUTION_H


#include <iostream>
#include <vector>

using namespace std;

class Solution{

    public :

    vector<int> affectation;
    int numberOfJobs;
    int numberOfMAchines;

    Solution(int n_jobs, int n_machines);


    Solution swap(int i, int j);
    
    void print();

    void shift(int i);

    void generate();
};




#endif