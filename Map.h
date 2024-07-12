#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h>
#include "Game.cpp"

#define RED "\033[41m"     /* Red */
#define GREEN "\033[42m"   /* Green */
#define BLUE "\033[44m"    /* Blue */
#define MAGENTA "\033[45m" /* Magenta */
#define CYAN "\033[46m"    /* Cyan */
#define YELLOW "\033[0;103m"
#define WHITE "\033[47m"
#define BLACK "\033[0;30m"
#define RESET "\033[0m"


using namespace std;

class Map
{
    public:

    // Constructor
    Map();
    
    // Parametrized Constructor
    Map(int players_num, int size);

    //Setter-Getter pair for position on map
    void setMapPos(string value, int playerID, int index);
    string getMapPos(int playerID, int index);

    void initializeMap();
    string getTileColor(int, int);

    private:
    //2 players, 51 total tiles
    //1 tiles for start, 1 for finish
    //terminal can only handle 51 tiles
    string map_array[2][51] = {};
    string _tile_color;
};




// void setMap(Map map)
// {
//     /* initialize random seed: */
//     srand (time(NULL));

//     map = Map();
//     // initialize tiles
//     map.initializeMap();
// }

#endif