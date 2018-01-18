//We probably don't need to use IBM CPLEX on this one, we will implement a first Tabu search from scratch

#include <iostream>
#include <fstream>

#include <vector>

#include "configuration.h"
#include "solution.h"

//#include <ilcplex/ilocplex.h>
//ILOSTLBEGIN

using namespace std;
//First a bunch of utilitarian functions :

typedef basic_ifstream<char> ifstream;
//typedef IloArray<IloNumArray> DataMatrix;

//TODO Penser à ajouter la borne de la relaxation continue
//Configuration* readDataFile(char* nom_de_fichier , IloModel model, IloNumVarArray varArray, IloRangeArray con){


Configuration *readDataFile(char *nom_de_fichier)
{
  char un_char;
  char deuxieme_char;
  //int nb_lu;
  int n;
  int m;
  vector<vector<int> > c;
  vector<vector<int> > a;
  vector<int> b;

  //IloEnv env = model.getEnv();

  // Remember n is jobs, m is machines
  ifstream fichier(nom_de_fichier);

  if (fichier)
  {
    //Lecture de n
    fichier >> un_char >> deuxieme_char >> n >> un_char;

    fichier >> un_char >> deuxieme_char >> m >> un_char;

    //Now reading c b and a

    fichier >> un_char >> un_char >> un_char;

    // C preambule should be read at this point
    // For each machine there is a line so :

    c = vector<vector<int> >(m);
    //DataMatrix c1 = DataMatrix(env, n);

    for (int j = 0; j < m; j++)
    {

      vector<int> tab(n);
      fichier >> un_char;
      //c1[j] = IloNumArray(env);
      for (int i = 0; i < n; i++)
      {
        int u;

        fichier >> u;
        tab[i] = u;
        //c1[j].add(u);
      }
      fichier >> un_char >> un_char;
      c[j] = tab;
    }
    fichier >> un_char;

    //Now reading a
    fichier >> un_char >> un_char >> un_char;
    a = vector<vector<int> > (m);
    //DataMatrix a1 = DataMatrix(env, n);
    for (int j = 0; j < m; j++)
    {
      vector<int> tab(n);
      fichier >> un_char;
      //a1[j] = IloNumArray(env);
      for (int i = 0; i < n; i++)
      {
        int u;

        fichier >> u;
        tab[i] = u;
        //a1[j].add(u);
      }
      fichier >> un_char >> un_char;
      a[j] = tab;
    }
    fichier >> un_char >> un_char;
  }

  fichier >> un_char >> un_char;
  b = vector<int>(m);
  //IloNumArray b1 = IloNumArray(env);

  for (int j = 0; j < m; ++j)
  {
    int u;
    fichier >> u;
    b[j] = u;
    //b1.add(u);
  }

  Configuration *config = new Configuration(n, m, c, a, b);
  //cout << "Everything is Fine"<< endl;
  return config;
}

// HERE BEGINS THE MAIN ///

int main(int argv, char **args)
{

  bool DEBUG = true;

  //IloEnv env;
  try
  {
    //IloModel model(env);

    //IloNumVarArray var(env);
    //IloRangeArray con(env);
    //cout << "First step"<< endl;

    char fileName[] = "../data/GAP-a05100.dat";
    //Configuration* config  = readDataFile(fileName,model, var, con);
    Configuration *config = readDataFile(fileName);
    //cout<< "Everything OK"<< endl;
    if (DEBUG)
    {
      config->print();
    }
    // Now starts the tabu search

    //First find an admissible solution
    Solution sol = config->generateSol();

    //cout << "Hello"<< endl;

    //Now we store a number things that must not appear twice


    vector<Solution> tabuList = vector<Solution>();

    tabuList.push_back(sol);

    float rho = 1.5;

    int threshold = config->cost(sol, rho);

    Solution bestSolSoFar = sol;
    //Second find a way to improve it
    //For now the swap is working OK, but we need to be able to shift a job from a machine to another

    //cout << "OK until now"<< endl;
    cout << config->trueCost(sol) << endl;

    for (int loop = 0; loop < 10; ++loop)
    {

      sol = bestSolSoFar;
      threshold = config->cost(sol, rho);

      for (int i = 0; i < config->n; i++)
      {
        for (int j = 0; j < config->n; j++)
        {
          if (i != j)
          {
            Solution candidat = sol.swap(i, j);
            if (config->cost(candidat, rho) < threshold)
            {
              threshold = config->cost(candidat, rho);

              cout << "Better candidate found : " << threshold << endl;

              bestSolSoFar = candidat;
            }
          }
        }
      }
      //TODO : something intelligent with the shift thing
      // Now that we have

      //Now we look at the maximum of the constraint violation
      int violation = bestSolSoFar.violationOfConstraint[0];
      int indexOfConstraint = 0;
      for (int j = 1; j < config->m; j++)
      {

        if (bestSolSoFar.violationOfConstraint[j] > violation)
        {
          violation = bestSolSoFar.violationOfConstraint[j];
          indexOfConstraint = j;
        }
      }

      // Ensuite trouver x i j tel que x_ij = 1 et aij est important

      int indexOfJob = -1;
      int aij = 0;
      for (int i = 1; i < config->n; i++)
      {
        if (config->a[indexOfConstraint][i] > aij && bestSolSoFar.affectation[i] == indexOfConstraint)
        {
          indexOfJob = i;
          aij = config->a[indexOfConstraint][i];
        }
      }

      //Then find the second smallest cost for this job

      int costOfTheJob = 15000000;

      // In fact the "tabu" search reveals useful here precisely

      // In fact the "tabu" search reveals useful here precisely
      int bestMachine = indexOfConstraint;

      for (int j = 0; j < config->m; j++)
      {
        if (config->c[j][indexOfJob] < costOfTheJob && j != indexOfConstraint)
        {
          bestMachine = j;
          costOfTheJob = config->c[j][indexOfJob];
        }
      }
      //Now we can proceed to the shift of the indexOfJob job to the bestMachine machine

      sol.shift(indexOfJob, bestMachine);

      std::cout<< config->cost(sol, rho) << endl;

      rho = 2 * rho;

      std::cout << "Now rho is equal to : " << rho <<  std::endl;
      int function_this_way;
      std::cin >> function_this_way;


    }

    /* The value of this int should never go up*/

    cout << threshold << endl;

    bestSolSoFar.print();
    return 0;
  }
  /*catch (IloException& e) {
    cerr << "Concert exception caught: " << e << endl;
  }*/
  catch (...)
  {
    cerr << "Unknown exception caught" << endl;
  }

  //env.end();
  return 1;

  //
}
