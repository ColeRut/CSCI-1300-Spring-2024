#ifndef PLAYER_H
#define PLAYER_H

#include "MapDriver.cpp"
#include "Shop.h"


void loadPlayers(Entity heroes[], Equipment all_items[], Potions all_potions[])
{
    string start = R"(
                                                                                                                                                             ,---. 
,--.   ,--.       ,--.                                    ,--.               ,--.  ,--.                 ,-----.    ,--.                                      |   | 
|  |   |  | ,---. |  | ,---. ,---. ,--,--,--. ,---.     ,-'  '-. ,---.     ,-'  '-.|  ,---.  ,---.     '  .-.  ' ,-|  |,--. ,--.,---.  ,---.  ,---. ,--. ,--.|  .' 
|  |.'.|  || .-. :|  || .--'| .-. ||        || .-. :    '-.  .-'| .-. |    '-.  .-'|  .-.  || .-. :    |  | |  |' .-. | \  '  /(  .-' (  .-' | .-. : \  '  / |  |  
|   ,'.   |\   --.|  |\ `--.' '-' '|  |  |  |\   --.      |  |  ' '-' '      |  |  |  | |  |\   --.    '  '-'  '\ `-' |  \   ' .-'  `).-'  `)\   --.  \   '  `--'  
'--'   '--' `----'`--' `---' `---' `--`--`--' `----'      `--'   `---'       `--'  `--' `--' `----'     `-----'  `---' .-'  /  `----' `----'  `----'.-'  /   .--.  
                                                                                                                       `---'                        `---'    '--'  
)";







    cout << start << endl;


    string input;
    getline(cin, input);
    Entity characters[14];
    loadCharacters("entity.txt", characters, 14, all_items, all_potions);
    loadPlayerList(heroes, characters);

    for (int i = 0; i < 4; i++)
    {
        cout << heroes[i].getName() << " loaded!" << endl;
    }
    cout << endl;
}

// bool loadAllItems(Equipment all_items[])
// {

//     // all_item size = 16 in current case

//     ifstream file("items.txt"); // open file, check if open
//     if (!file.is_open())
//     {
//         return false;
//     }

//     ifstream test_file("items.txt"); // use test file to count lines (test_file = file)

//     string line;
//     string item_stats[6];

//     getline(file, line); // skips first line
//     for (int i = 0; i < 16; i++)
//     {
//         getline(file, line);

//         if (line != "") // if on a non-blank line
//         {
//             split(line, '|', item_stats, 6); // split and set to stat array, then set each stat to Entity character[]

//             all_items[i].name = item_stats[0];
//             all_items[i].type = item_stats[2][0];
//             all_items[i].element = item_stats[4][0];
//             all_items[i].price = stod(item_stats[5]);

//             if (all_items[i].type == 'D')
//             {
//                 all_items[i].damage = stod(item_stats[3]);
//                 all_items[i].defense = 0;
//             }

//             else if (all_items[i].type == 'S')
//             {
//                 all_items[i].defense = stod(item_stats[3]);
//                 all_items[i].damage = 0;
//             }
//         }

//         // make potion and item array
//     }

//     return true;
// }

// bool loadAllPotions(Potions all_potions[])
// {

//     // all_item size = 26 in current case

//     ifstream file("potions.txt"); // open file, check if open
//     if (!file.is_open())
//     {
//         return false;
//     }

//     ifstream test_file("potions.txt"); // use test file to count lines (test_file = file)

//     string line;
//     string potion_stats[6];

//     getline(file, line); // skips first line
//     for (int i = 0; i < 11; i++)
//     {
//         getline(file, line);

//         if (line != "") // if on a non-blank line
//         {
//             split(line, '|', potion_stats, 6); // split and set to stat array, then set each stat to Entity character[]

//             all_potions[i].name = potion_stats[0];
//             all_potions[i].type = potion_stats[2][0];
//             all_potions[i].effect_value = stod(potion_stats[3]);
//             all_potions[i].price = stod(potion_stats[5]);
//             all_potions[i].quantity = 1;
//         }

//         // make potion and item array
//     }

//     return true;
// }

Equipment nameToEquipment(string name, Equipment all_items[])
{
    for (int i = 0; i < 15; i++)
    {
        if (name == all_items[i].name)
        {
            return all_items[i];
        }
    }

    return Equipment();
}

Potions nameToPotion(string name, Potions all_potions[])
{
    for (int i = 0; i < 11; i++)
    {
        if (name == all_potions[i].name)
        {
            return all_potions[i];
        }
    }

    return Potions();
}

void selectCharacter(Entity heroes[], Entity players[], Equipment all_items[], Potions all_potions[])
{
    string input;

    // choosing player 1
    cout << "Player 1, which character would you like to choose? Enter a number:" << endl
         << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << "(" << i + 1 << ") " << heroes[i].getName() << " ";
    }
    cout << endl;

    int index_of_hero_1;
    bool valid_input = false;
    while (valid_input == false)
    {
        getline(cin, input);

        if (validateInt(input) && input != "" && (stoi(input) >= 1 && stoi(input) <= 4))
        {
            players[0] = heroes[stoi(input) - 1];
            index_of_hero_1 = stoi(input);
            valid_input = true;
        }
        else
        {
            cout << "Enter a valid input" << endl;
        }
        cout << endl;
        lineBreak();
    }

    // choosing player 2
    cout << "Player 2, which character would you like to choose? Enter a number:" << endl
         << endl;
    ;

    for (int i = 0; i < 3; i++)
    {
        if ((i + 1) < index_of_hero_1)
        {
            cout << "(" << i + 1 << ") " << heroes[i].getName() << " ";
        }
        else
        {
            cout << "(" << i + 1 << ") " << heroes[i + 1].getName() << " ";
        }
    }
    cout << endl;

    valid_input = false;
    while (valid_input == false)
    {
        getline(cin, input);

        if (validateInt(input) && input != "" && (stoi(input) >= 1 && stoi(input) <= 3))
        {
            if (stoi(input) < index_of_hero_1)
            {
                players[1] = heroes[stoi(input) - 1];
            }
            else
            {
                players[1] = heroes[stoi(input)];
            }
            valid_input = true;
        }
        else
        {
            cout << "Enter a valid input" << endl;
        }

        lineBreak();
    }

    // setting starting items to eqipped
    players[0].setEquipped(nameToEquipment(players[0].getItemStart1(), all_items), 0);
    players[1].setEquipped(nameToEquipment(players[1].getItemStart1(), all_items), 0);

    players[0].setEquipped(all_items[15], 1);
    players[1].setEquipped(all_items[15], 1);

    //set start potion
    players[0].setPotions(nameToPotion(players[0].getItemStart0(), all_potions), 0);
    players[1].setPotions(nameToPotion(players[1].getItemStart0(), all_potions), 0);

    //make other indices blank
    players[0].setPotions(Potions(), 1);
    players[0].setPotions(Potions(), 2);
    players[1].setPotions(Potions(), 1);
    players[1].setPotions(Potions(), 2);


}

int whichPlayerGoesFirst()
{
    int roll = diceRoll() % 2;

    cout << "Rolling die to see who goes first." << endl;
    string input;
    getline(cin, input);
    
    if (roll == 0)
    {
        cout << "Player 1 rolled higher! Player 1 will go first." << endl;
    }

    else
    {
        cout << "Player 2 rolled higher! Player 2 will go first." << endl;

    }

    return roll;
}

#endif