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


    void swap();
    void shift();

    void generate();
};




#endif