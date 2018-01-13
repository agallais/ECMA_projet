//We probably don't need to use IBM CPLEX on this one, we will implement a first Tabu search from scratch

#include <iostream>
#include <fstream>

#include "configuration.h"

using namespace std;
//First a bunch of utilitarian functions :

typedef basic_ifstream<char> ifstream;



Configuration* readDataFile(char* nom_de_fichier){

  char un_char;
  char deuxieme_char;
  //int nb_lu;
  int n;
  int m ;


  ifstream fichier(nom_de_fichier);
  fichier >> un_char>> deuxieme_char >> n >> un_char;

  if(fichier){
    //Lecture de n
    fichier >> un_char>> deuxieme_char >> m >> un_char;
}


Configuration* config = new Configuration(n,m);

return config;
}

// HERE BEGINS THE MAIN


int main(int argv, char** args){

char fileName[] = "GAP-a05100.dat";



Configuration* config  = readDataFile(fileName);

config->print();

  return 0;
}
