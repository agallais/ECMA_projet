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

cout<< "Hello"<< endl;
  bool DEBUG = false;

  //IloEnv env;
  try
  {
    //IloModel model(env);

    //IloNumVarArray var(env);
    //IloRangeArray con(env);

    cout << args[0] << endl;
    char fileName[] = args[0];



    // best sol for GAP-a05100.dat is 1678

    //Configuration* config  = readDataFile(fileName,model, var, con);
    Configuration *config = readDataFile(fileName);

    //cout<< "Everything OK"<< endl;
    if (DEBUG)
    {
      //      config->print();
    }
    // Now starts the tabu search

    //First find an admissible solution
    Solution sol = config->generateSol();

    //cout << "Hello"<< endl;

    //Now we store a number things that must not appear twice


    vector<Solution> tabuList = vector<Solution>();
    vector<pair<int,int> > tabuShiftList = std::vector<pair<int,int> >();
    tabuList.push_back(sol);

    float rho = 1.5;

    int threshold = config->cost(sol, rho);

    Solution bestSolSoFar = sol;
    //Second find a way to improve it
    //For now the swap is working OK, but we need to be able to shift a job from a machine to another

    //cout << "OK until now"<< endl;
    cout << config->trueCost(sol) << endl;

    for (int loop = 0; loop < 15; ++loop)
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
              if(DEBUG){
                cout << "Better candidate found : " << threshold << endl;
              }
              bestSolSoFar = candidat;
            }
          }
        }
      }

      config->cost(bestSolSoFar, rho);

      if(bestSolSoFar.isAConstraintViolated()){
        //      cout<<"Hello2"<< endl;
        config->improveConstraints(bestSolSoFar);

        if(DEBUG){
          std::cout << "Now the violated constraints : " << '\n';

          for(std::vector<int>::iterator v = sol.violationOfConstraint.begin();v != sol.violationOfConstraint.end(); ++v){
            std::cout << *v << '\n';
          }
        }
      }else{
        //TODO now we should decribe what the heuristic should do, would the solution be feasible already

        //First find the job that costs the more
        // In fact we should try to look for a serie of interesting moves
        config->cost(bestSolSoFar, rho);
        int improvement = 0;
        bool thereIsAnImprovement = false;
        int jobOfInterest = 0;
        int machineOfInterest = 0;

        for(int i = 0; i < config-> n; ++i){
          for(int j = 0; j < config-> m; ++j){
            if(config->c[bestSolSoFar.affectation[i]][i] - config->c[j][i] > improvement && ( bestSolSoFar.violationOfConstraint[j]  + config -> a[j][i] < 0  )){

              improvement = config->c[bestSolSoFar.affectation[i]][i] - config->c[j][i];
              jobOfInterest = i;
              machineOfInterest = j;
              thereIsAnImprovement = true;
            }
          }
        }
        //bestSolSoFar.print();
        std::cout << config -> cost(bestSolSoFar, rho) << '\n';
        std::cout << "Expected gain : " << improvement<<'\n';

        if(thereIsAnImprovement){
          bestSolSoFar.shift(jobOfInterest, machineOfInterest);
          tabuShiftList.push_back(pair<int,int>(jobOfInterest,machineOfInterest));
        }
        // END ELSE
      }

      std::cout<< config->cost(bestSolSoFar, rho) << endl;
      threshold = config->cost(bestSolSoFar, rho);
      if (rho < 10000000){
        rho = 2 * rho;}

        //std::cout << "Now rho is equal to : " << rho <<  std::endl;

      }

      /* The value of this int should never go up*/

      threshold = config->cost(bestSolSoFar, rho);

      //cout << "Best Solution is : "<< threshold << endl;


      cout << "Cost of best Solution found : "<< config->cost(bestSolSoFar, rho)<< endl;
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
