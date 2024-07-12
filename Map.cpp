#include "Map.h"


Map::Map()
{}

Map::Map(int players_num, int size)
{
    map_array[players_num][size] = {};
}

// setter for position on map given the value and which player and then the index for their lane
void Map::setMapPos(string value, int playerID, int index)
{
    map_array[playerID][index] = value;
}

// getter for position on map given which player and then the index for their lane
string Map::getMapPos(int playerID, int index)
{
    return map_array[playerID][index];
}

void Map::initializeMap()
{

    // variables to hold random numbers
    int rand_num1, rand_num2;
    int num_red_1 = 0;
    int num_red_2 = 0;
    int num_green_1 = 0;
    int num_green_2 = 0;

    //start tiles white
    map_array[0][0] = WHITE;
    map_array[1][0] = WHITE;


//reinitializes if less than 4 red or less than 3 green
while (num_red_1 < 4 || num_red_2 < 4 || num_green_1 < 3 || num_green_2 < 3)
{

    for (int i = 1; i < 50; i++){
        /* generate random number between 1 and 100: */
        rand_num1 = rand() % 100 + 1;
        rand_num2 = rand() % 100 + 1;

        // 25% chance for red and green
        if (rand_num1 <= 25){
            map_array[0][i] = RED;
            num_red_1++;
            if (map_array[0][i-1] == RED)
            {
                map_array[0][i] = BLUE;
                num_red_1--;
            }
        }
        else if (rand_num1 <=50){
            map_array[0][i] = GREEN;
            num_green_1++;
            if (map_array[0][i-1] == GREEN)
            {
                map_array[0][i] = BLUE;
                num_green_1--;
            }
        }
        else{
            map_array[0][i] = BLUE;
        }



        // This part populates the other lane for the second player
        if (rand_num2 <= 25){
            map_array[1][i] = RED;
            num_red_2++;
            if (map_array[1][i-1] == RED)
            {
                map_array[1][i] = BLUE;
                num_red_2--;
            }
        }
        else if (rand_num2 <=50){

            map_array[1][i] = GREEN;
            num_green_2++;
            if (map_array[1][i-1] == GREEN)
            {
                map_array[1][i] = BLUE;
                num_green_2--;
            }
        }
        else{
            map_array[1][i] = BLUE;
        }
    }

    //end tile yellow
    map_array[0][50] = YELLOW;
    map_array[1][50] = YELLOW;

}
}

string Map::getTileColor(int player, int position)
{
    //player one, check tile color and set _tile_color to "color"
    if (player == 1)
    {
        if (map_array[0][position] == RED)
        {
            _tile_color = "Red";
        }

        else if (map_array[0][position] == GREEN)
        {
            _tile_color = "Green";
        }

        else if (map_array[0][position] == BLUE)
        {
            _tile_color = "Blue";
        }

        else if (map_array[0][position] == WHITE)
        {
            _tile_color = "White";
        }

        else if (map_array[0][position] == YELLOW)
        {
            _tile_color = "Yellow";
        }

        //if it's messed up then it returns blank
        else
        {
            _tile_color = "";
        }
    }

    //player 2
    else if (player == 2)
    {
        if (map_array[1][position] == RED)
        {
            _tile_color = "Red";
        }

        else if (map_array[1][position] == GREEN)
        {
            _tile_color = "Green";
        }

        else if (map_array[1][position] == BLUE)
        {
            _tile_color = "Blue";
        }

        else if (map_array[1][position] == WHITE)
        {
            _tile_color = "White";
        }

        else if (map_array[1][position] == YELLOW)
        {
            _tile_color = "Yellow";
        }

        //if it's messed up, return blank
        else
        {
            _tile_color = "";
        }
    }

    else
    {
        _tile_color = "";
    }

    return _tile_color;
}