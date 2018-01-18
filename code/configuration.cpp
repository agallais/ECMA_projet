#include "configuration.h"

#include <iostream>
#include <algorithm>

using namespace std;

Configuration::Configuration(int n_machines, int n_jobs, vector<vector<int> > cost, vector<vector<int> > a, vector<int> bound)
{

  this->n = n_machines;
  this->m = n_jobs;
  this->c = cost;
  this->a = a;
  this->b = bound;
}

// c[n_machines][n_job] and same for a

void Configuration::print()
{
  cout << "n = " << this->n << endl;
  cout << "m = " << this->m << endl;
  cout << "c =";
  for (int j = 0; j < m; j++)
  {
    for (int i = 0; i < n; ++i)
    {
      cout << c[j][i] << " ";
    }
    cout << endl;
  }
  cout << "b =  ";
  for (int j = 0; j < m; ++j)
  {

    cout << this->b[j] << " ";
  }
  cout << endl;
  return;
}

int Configuration::cost(Solution& sol, float rho)
{

  int total = 0;

  for (int i = 0; i < this->n; i++)
  {

    total += c[sol.affectation[i]][i];
  }

  // This is for the cost of the master problem, now we add the cost for violating the constraints

  int P = 0;

  bool aConstraintIsViolated = false;

  for (int j = 0; j < this->m; j++)
  {

    int totalForLignJ = 0;

    for (int i = 0; i < this->n; i++)
    {

      if (sol.affectation[i] == j)
      {
        totalForLignJ += this->a[j][i];
      }
    }

    int si = totalForLignJ - this->b[j];

    //cout<< totalForLignJ<<" "<<si<< " "<< endl;

    aConstraintIsViolated = (si > 0) || aConstraintIsViolated;
    sol.violationOfConstraint[j] = si;
    //cout<< si << endl;

    P += max(si, 0);
  }

  // There should be a \rho to multiply the P
  total += rho * P;

  return total;
}

int Configuration::trueCost(Solution sol)
{

  int total = 0;

  for (int i = 0; i < this->n; i++)
  {

    total += c[sol.affectation[i]][i];
  }
  return total;
}

Solution Configuration::generateSol()
{

  Solution result = Solution(this->n, this->m);

  for (int i = 0; i < this->n; i++)
  {

    int bestAffectation = 0;
    for (int j = 0; j < this->m; j++)
    {

      if (this->c[j][i] < this->c[bestAffectation][i])
      {

        bestAffectation = j;
      }
    }

    result.affectation[i] = bestAffectation;
  }

  // Then it is evident that the cost of this solution is a inferior bound for the solution of the problem, but probably it does not match the constraints
  return result;
}


void Configuration::improveConstraints(Solution solution){

  int violation = solution.violationOfConstraint[0];
  int indexOfConstraint = 0;
  for (int j = 1; j < solution.numberOfMAchines; j++)
  {

    if (solution.violationOfConstraint[j] > violation)
    {
      violation = solution.violationOfConstraint[j];
      indexOfConstraint = j;
    }
  }

  // Ensuite trouver x i j tel que x_ij = 1 et aij est important

  int indexOfJob = -1;
  int aij = 0;
  for (int i = 1; i < this->n; i++)
  {
    if (this->a[indexOfConstraint][i] > aij && solution.affectation[i] == indexOfConstraint)
    {
      indexOfJob = i;
      aij = this->a[indexOfConstraint][i];
    }
  }

  //Then find the second smallest cost for this job

  int costOfTheJob = 15000000;

  // In fact the "tabu" search reveals useful here precisely

  // In fact the "tabu" search reveals useful here precisely
  int bestMachine = indexOfConstraint;

  for (int j = 0; j < this->m; j++)
  {
    if (this->c[j][indexOfJob] < costOfTheJob && j != indexOfConstraint)
    {
      bestMachine = j;
      costOfTheJob = this->c[j][indexOfJob];
    }
  }
  //Now we can proceed to the shift of the indexOfJob job to the bestMachine machine

  solution.shift(indexOfJob, bestMachine);
}
