/*
HEADER COMMENT 
Full name: Tyler Wescott
NSHE: 5006959108
Goal of the program/output: 
Using adjacency lists and DFS, help Jill Valentine get away from nemesis by taking paths
that potentially lead to escape until a successful path is found. 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

bool escapeRPD(string jillsLocation, string roomNeedToReach, int jillsHealth, unordered_map<string, list<string>> rpdMap, vector<string> &predecessorVec, unordered_map<string, int> &healthInRoom, unordered_map<string, int> nemesisLocations)
{
    int roomDanger = nemesisLocations[jillsLocation];   //get the room health value
    jillsHealth -= roomDanger;    //set jill's health based on the room's +/- health value

    //if this room causes jill to lose all her health, this path is not viable
    if(jillsHealth <= 0)
        return false;
        
    //add current health to healthInRoom map
    healthInRoom[jillsLocation] = jillsHealth;

    //if she arrived in final room, she escaped. 
    if(jillsLocation == roomNeedToReach)
    {
        predecessorVec.push_back(jillsLocation);    //fill predecessor vector
        return true;
    }

    //for each neighbor of a room
    for (auto neighbor : rpdMap[jillsLocation])
    {
        if(escapeRPD(neighbor, roomNeedToReach, jillsHealth, rpdMap, predecessorVec, healthInRoom, nemesisLocations) == true)
        {
            predecessorVec.push_back(jillsLocation);    //fill predecessor vector
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    //an adjacency list, maps a room name to a list
    //of neighbor rooms (each neighbor represents an edge/door to another room)
    unordered_map< string, list<string> > rpdMap;

    //maps a room name to either Nemesis or a
    //healing item, so if the room name maps to a value of 0 (there’s no danger), a positive value represents
    //how much damage Nemesis can cause to Jill, and a negative value means an herb is found in the room,
    //so Jill can heal in this room
    unordered_map< string, int > nemesisLocations; 

    //predecessor vector which is used to construct a path that leads to the courtyard
    vector<string> predecessorVector;

    // map that stores the max health Jill had when she
    //entered the room (this is sort of the ”visited” array/map
    unordered_map< string, int > healthInRoom;

    /*
    You will be given a list of edges in a RPD.txt file (via a command line argument), each line of input will
    contain a directed edge (a pair of two rooms), so if a line contains
    WestStairway1F DarkRoom
    You insert this edge into your adjacency list in the following way
    rpdMap [ " WestStairway1F " ]. push_back ( " DarkRoom " );

    If you want to look at each neighbor room of WestStairway1F
    for ( auto neighbor : rpdMap [ " WestStairway1F " ])
    {
    cout << neighor << endl ;
    }

    Once you read the two input files and populate the rpdMap and nemesisLocation maps, you will write a
    DFS type traversal that finds a path from WestStairway1F to Courtyard. You would probably want to write
    the following recursive function
    bool escapeRPD ( string jillsLocation , string roomNeedToReach ,
    int jillsHealth , unordered_map < string , list < string > > rpdMap ,
    unordered_map < string , string > & predecessor ,
    unordered_map < string , int > & healthInRoom ,
    unordered_map < string , int > nemesisLocations )
    {

    }

    */  

    //read command line txt file 1

    string readFileStr, roomName, neighbor, roomLocations;
    int dangerValue, startingHealth = 20;

    ifstream reader(argv[1]);

    while (getline(reader, readFileStr))
    {
        stringstream ss(readFileStr);

        if (ss >> roomName >> neighbor)
            rpdMap[roomName].push_back(neighbor);       //populate rpdMap adjacency list
    }
    reader.close();

    //read command line txt file 2
    reader.open(argv[2]);

    while (getline(reader, readFileStr))
    {
        stringstream ss(readFileStr);

        if (ss >> roomLocations >> dangerValue) 
            nemesisLocations[roomLocations] = dangerValue;     //populate nemesis or healing map
    }
    reader.close();

    //recursive call
    if(escapeRPD("WestStairway1F", "Courtyard", startingHealth, rpdMap, predecessorVector, healthInRoom, nemesisLocations) == true)
    {
        //Path : WestStairway1F -> DarkRoom -> WestOffice -> MainHall1F -> Courtyard
        //Somehow ... I ’m still alive ..
        cout << "Path : " ;

        for (int i = predecessorVector.size()-1; i >= 0; i--)
        {
            auto x = predecessorVector[i];
            cout << x;
            if(i > 0)
                cout << " -> ";
        }
        cout << endl << "Somehow ... I'm still alive ..." << endl;
    }
    else
        cout << "STARS !!!" << endl;

    return 0;
}