#include "Map.cpp"


void displayMap(Map starterMap, int player1_position, int player2_position)
{

    
    // demonstrate tiles = these numbers will show up to
    // this top lane corresponds to player 1
    for(int i = 0; i < 51; i++){

            if (player1_position == i)
            {
                cout << starterMap.getMapPos(0,i) << "P1" << RESET;
            }
            else
            {
            cout << starterMap.getMapPos(0,i) << " |" << RESET;
            }
        
    }

    cout << endl;

    // this bottom lane corresponds to player 2
    for(int i = 0; i < 51; i++)
    {
            if (player2_position == i)
            {
                cout << starterMap.getMapPos(1,i) << "P2" << RESET;
            }
            else
            {
            cout << starterMap.getMapPos(1,i) << " |" << RESET;
            }
        
    }

    // // Use RESET to revert back to the default terminal text color when done
    cout << RESET << endl;
}
