//We probably don't need to use IBM CPLEX on this one, we will implement a first Tabu search from scratch

#include <iostream>
#include <fstream>

#include <vector>

#include "configuration.h"
#include "solution.h"

using namespace std;
//First a bunch of utilitarian functions :

typedef basic_ifstream<char> ifstream;



Configuration* readDataFile(char* nom_de_fichier){

  char un_char;
  char deuxieme_char;
  //int nb_lu;
  int n;
  int m ;
  vector< vector<int> > c;
  vector< vector<int> > a;
  vector<int>  b;


  // Remember n is jobs, m is machines
  ifstream fichier(nom_de_fichier);


  if(fichier){
    //Lecture de n
    fichier >> un_char>> deuxieme_char >> n >> un_char;
    fichier >> un_char>> deuxieme_char >> m >> un_char;

    //Now reading c b and a

    fichier >> un_char >> un_char >> un_char;

    // C preambule should be read at this point
    // For each machine there is a line so :

    c = vector<vector<int> > (m);
    for (int j = 0; j < m; j++){
      vector<int> tab(n);
      fichier >> un_char;
      for ( int i = 0; i < n ; i ++)
      {
        int u;

        fichier >>u;
        tab[i] = u;
      }
      fichier >> un_char >> un_char;
      c[j] = tab;
    }
    fichier >> un_char   ;

    //Now reading a
    fichier >> un_char >> un_char >> un_char;
    a = vector<vector<int> > (m);
    for (int j = 0; j < m; j++){
      vector<int> tab(n);
      fichier >> un_char;
      for ( int i = 0; i < n ; i ++)
      {
        int u;

        fichier >>u;
        tab[i] = u;
      }
      fichier >> un_char >> un_char;
      a[j] = tab;
    }
    fichier >> un_char  >> un_char ;



  }


  fichier >> un_char >> un_char;
  b = vector<int> (m);



  for (int j = 0; j < m ; ++j){
    int u ;
    fichier >> u;
    b[j] = u;
  }


  Configuration* config = new Configuration(n,m ,c, a , b);

  return config;
}

// HERE BEGINS THE MAIN ///


int main(int argv, char** args){

  bool DEBUG = false;

  char fileName[] = "data/GAP-a05100.dat";

  Configuration* config  = readDataFile(fileName);

  if(DEBUG){
    config->print();
   }
  // Now starts the tabu search

  //First find an admissible solution
  Solution sol = config -> generateSol();


  //Now we store a number of solutions already explored
  vector<Solution> tabuList = vector<Solution>();

  tabuList.push_back(sol);
  
  int threshold = config -> cost(sol);
  
  Solution bestSolSoFar = sol;
  //Second find a way to improve it
  
 
 for( int loop = 0; loop < 10; ++loop){

  sol = bestSolSoFar;

  for(int i = 0; i < config -> n; i++){
    for(int j = 0; j < config -> n; j++){
      if( i != j){
        Solution candidat = sol.swap(i,j);
        if(config -> cost(candidat) < threshold){
          threshold = config -> cost(candidat);
          //cout << "Better candidate found : "<<threshold<<  endl;
          bestSolSoFar = candidat;
        }
      }
    }
  }

 }



  /* The value of this int should never go up*/

  
  
cout << threshold << endl;

bestSolSoFar.print();
  //
  
  return 0;
}
