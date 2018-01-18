#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <vector>

using namespace std;

class Solution
{

    // There should be one more modification, adding a boolean for 'violated constraint'

  public:
    vector<int> affectation;
    vector<int> violationOfConstraint;
    int numberOfJobs;
    int numberOfMAchines;

    Solution(int n_jobs, int n_machines);

    Solution swap(int i, int j);

    bool isEqual(Solution sol);

    bool isAConstraintViolated();

    void print();

    void shift(int job, int machine);

    void generate();
};

#endif
