tabou: main.o configuration.o solution.o
	g++ main.o solution.o configuration.o -o tabou

main.o: code/main.cpp code/solution.cpp code/configuration.cpp code/solution.h code/configuration.h
	g++ -c code/main.cpp code/solution.cpp code/configuration.cpp -W -Wall -ansi -pedantic

configuration.o : code/solution.cpp code/configuration.cpp code/solution.h code/configuration.h
	g++  -c code/solution.cpp code/configuration.cpp -W -Wall -ansi -pedantic

solution.o : code/solution.cpp code/solution.h
	g++ -c code/solution.cpp -W -Wall -ansi -pedantic
