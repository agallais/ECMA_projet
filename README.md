# ECMA_projet

## Presentation of the project
This project is part of the grade in one of my courses. It is about finding a heuristic to eficiently solve the General Assignment Problem.

This is a well known problem in Operation Research, and as you may know the problem quickly becomes impossible to solve by the classical branch-and-bound method, requiring a **heuristic approach**.

I will upload the OPL model of the problem as soon as I have time. The main point is that it works great on the data file a... still ok on data files b-smth but does not give a solution after 12h for a c-smth. At this point the heuristic approach or the column generation becomes necessary. 

## What I tried to do

I wil first try to solve the problem via a **tabu search** heuristic, then I will try a **lagrangian relaxation** / **column generation** if time.

Don't hesitate to e-mail me about the project or the way I write the code : aymeri.gallais@gmail.com

## Bibliography

To do this I read :
A Tabu search heuristic for the generalized assignment problem, by Juan A. Dõaz , Elena Fernandez, [European Journal of Operational Research 132 (2001) 22±38]
Even if old, I think it is still quite actual. If you have any suggestion of a more modern paper, please feel free to e-mail me and I will try to implement the approach.


For more on the Tabu search I think that the main ressource is Glover 86 : Future Paths for integer programming and links to artificial intelligence, by Fred Glover in 1986

## How to build the project ?
 To Build the project I used :
```
g++ main.cpp solution.cpp configuration.cpp -o tabuSearch.exe
```
