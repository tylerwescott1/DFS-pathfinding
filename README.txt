Creates a level layout using rpd.txt which starts with a room(room name on left)
then shows all its neighbors (room name on the right).
Uses this text file to fill a map and essentially maps out the level.

Picture will be included that gives visual of level.

Similar method for assigning the danger level of each room using the different
nemesis0#.txt files (where # is 1-4 inclusive).
Nemesis is the enemy that out main character Jill has to face throughout the level.


compile using c++11 and higher

when running, use rpd.txt as first command line arg, then one of the 4 
nemesis0#.txt files. 

Terminal output will provide a path that keeps our main character (Jill) alive.
If there is no path that Jill can use to escape, she will say her famous
catchphrase "STARS!!!"

DFS goes to every possible pathway until there is a path found that does not result
in Jill's health going below 0. She starts with 20 health. 

MAC(VSCode):
g++ -std=c++11 main.cpp
./a.out rpdtxt nemesis0#.txt
