#ifndef GAMEFLOW_H
#define GAMEFLOW_H
#include "Combat.h"

// player menu
// quit (ends game)
// use potion (ends turn)
// drop/swap weapon (ends turn)
// move (roll die, update position)
// check tile color
// combat
// noncombat
// ithaca


void Game::endTurn(Entity& player, int player_num)
{
    // do calamity at every turn
    calamity(player, player_num);

    cout << endl
         << "Turn ended" << endl;
}

bool Game::playerMenu(Entity& player, int player_num)
{
    string input;
    int choice1;
    int potion_index;
    int weapon_index;
    int drop_index;
    int inventory_index;
    int equipped_index;
    bool empty_potions;
    bool turn_ended = false;
    bool move = false;

    while (turn_ended == false)
    {
        cout << endl
             << "Player " << player_num + 1 << "'s turn!" << endl
             << endl;

        cout << "1. Move" << endl;
        cout << "2. Display Player Stats" << endl;
        cout << "3. Display Equipment" << endl;
        cout << "4. Display Inventory" << endl;
        cout << "5. Display Potions" << endl;
        cout << "6. Use Potion" << endl;
        cout << "7. Drop Inventory Item" << endl;
        cout << "8. Swap Inventory and Equipment Item" << endl;
        cout << "9. Quit Game" << endl;

        getline(cin, input);
        cout << endl;
        choice1 = -1;
        lineBreak();

        if (validateInt(input) && input != "")
        {
            choice1 = stoi(input);

            if (choice1 > 9 || choice1 < 1)
            {
                cout << "Enter a valid input" << endl;
                lineBreak();
            }
        }

        else if (!validateInt(input) || input == "")
        {
            cout << "Enter a valid input" << endl;
            lineBreak();
        }

        // move
        if (choice1 == 1)
        {

            if (player.getCanMove())
            {
                int roll = diceRoll();

            updatePlayerPosition(player_num + 1, roll);
            cout << "You rolled a " << roll << "!" << endl;

            move = true;
            return move;
            }

            //implementing not being able to move from a calamity striking (siren's song)
            else 
            {
                cout << "You cannot move this turn." << endl;
                player.setCanMove(true); //reset to can move so you can move next turn
                return move;
            }

        }

        // display player stats
        if (choice1 == 2)
        {
            cout << "Player stats" << endl
                 << endl;
            player.printStats();
            lineBreak();
        }

        // display equipment
        if (choice1 == 3)
        {

            cout << "Equipped: " << endl;
            player.displayEquipped();
            lineBreak();
        }

        // display inventory
        if (choice1 == 4)
        {
            cout << "Inventory: " << endl;
            player.displayInventory();
            lineBreak();
        }

        // display potions
        if (choice1 == 5)
        {
            cout << "Potions:" << endl;
            player.displayPotions();
            lineBreak();
        }

        // use potion
        if (choice1 == 6)
        {
            empty_potions = true;
            for (int i = 0; i < 3; i++)
            {
                if (player.getPotions(i).name != "")
                {
                    empty_potions = false;
                }
            }

            // if no potions
            if (empty_potions == true)
            {
                cout << "You are out of Potions!" << endl;
            }

            else
            {
                player.displayPotions();
                potion_index = -1;

                while (potion_index > 3 || potion_index < 1)
                {
                    cout << "Which potion do you want to use?" << endl;
                    getline(cin, input);
                    cout << endl;

                    if (validateInt(input) && input != "")
                    {
                        potion_index = stoi(input);

                        if (potion_index > 3 || potion_index < 1)
                        {
                            cout << "Enter a valid input" << endl;
                            lineBreak();
                        }

                        else if (player.getPotions(potion_index - 1).name == "")
                        {
                            cout << "Select a valid potion" << endl;
                            lineBreak();
                            potion_index = -1;
                        }
                    }

                    else if (!validateInt(input) || input == "")
                    {
                        cout << "Enter a valid input" << endl;
                        lineBreak();
                    }
                }

                player.displayEquipped();
                weapon_index = -1;

                while (weapon_index > 2 || weapon_index < 1)
                {
                    // need to have a weapon for strength potion
                    // a weapon should always be equipped anyway
                    cout << "Select a weapon to use (for strength potions)" << endl;
                    getline(cin, input);
                    cout << endl;

                    // if out of bounds input
                    if (validateInt(input) && input != "")
                    {
                        weapon_index = stoi(input);

                        if (weapon_index > 2 || weapon_index < 1)
                        {
                            cout << "Enter a valid input" << endl;
                            lineBreak();
                        }

                        // if eqipped choice isn't a weapon
                        else if (player.getEquipped(weapon_index - 1).name == "" || player.getEquipped(weapon_index - 1).type != 'D')
                        {
                            cout << "Select a valid weapon" << endl;
                            lineBreak();
                            weapon_index = -1;
                        }

                        // finally, use potion
                        else
                        {

                            cout << player.getPotions(potion_index - 1).name << " successfully used!" << endl;
                            player.usePotion(potion_index - 1, player.getEquipped(weapon_index));
                        }
                    }

                    // if first choice is out of bounds
                    else if (!validateInt(input) || input == "")
                    {
                        cout << "Enter a valid input" << endl;
                        lineBreak();
                    }
                }
            }

            endTurn(player, player_num);
            return move;
        }

        // drop inventory
        if (choice1 == 7)
        {
            drop_index = -1;
            while (drop_index < 1 || drop_index > 3)
            {
                cout << "Which inventory item do you want to drop? Enter the index (1-3)" << endl;
                getline(cin, input);
                cout << endl;
                if (validateInt(input) && input != "")
                {
                    drop_index = stoi(input);

                    if (drop_index >= 1 && drop_index <= 3)
                    {
                        player.dropInventory(drop_index - 1);
                        cout << "Successfully dropped item from index " << drop_index << endl;
                        lineBreak();
                    }

                    else
                    {
                        cout << "Enter valid input" << endl;
                        lineBreak();
                    }
                }
            }

            endTurn(player, player_num);
            return move;
        }

        // swap
        if (choice1 == 8)
        {

            inventory_index = -1;
            while (inventory_index < 1 || inventory_index > 3)
            {
                cout << "Which inventory item do you want to equip? Enter the index (1-3)" << endl;
                getline(cin, input);
                cout << endl;
                if (validateInt(input) && input != "")
                {
                    inventory_index = stoi(input);

                    if (inventory_index >= 1 && inventory_index <= 3)
                    {

                        equipped_index = -1;
                        while (equipped_index < 1 || equipped_index > 2)
                        {
                            cout << "Which equipped item do you want to move to inventory? Enter the index (1-2)" << endl;
                            getline(cin, input);
                            cout << endl;
                            if (validateInt(input) && input != "")
                            {
                                equipped_index = stoi(input);

                                if (equipped_index >= 1 && equipped_index <= 2)
                                {
                                    player.swap(equipped_index - 1, inventory_index - 1);
                                    cout << "Successfully swapped " << player.getEquipped(equipped_index-1).name << " for " << player.getInventory(inventory_index-1).name << endl;
                                    lineBreak();
                                }

                                else
                                {
                                    cout << "Enter valid input" << endl;
                                    lineBreak();
                                }
                            }
                        }
                    }

                    else
                    {
                        cout << "Enter valid input" << endl;
                        lineBreak();
                    }
                }
            }

            endTurn(player, player_num);
            return move;
        }

        // quit game
        if (choice1 == 9)
        {
            input = "";

            // double check that they really want to end game
            while (input != "n")
            {
                cout << "Are you sure you want to quit? (y/n)" << endl;
                getline(cin, input);
                cout << endl;

                if (input == "y")
                {
                    cout << "Ending game" << endl;
                    setEndGame(true);
                    return move;
                }

                else if (input != "y" && input != "n")
                {
                    cout << "Enter a valid input" << endl;
                }
            }
        }
    }
    return move;
}

void gameFlow(Entity players[], int first_player, Game game, Map map, Equipment all_items[], Potions all_potions[], Entity island_enemies[], Entity epic_enemies[])
{
    string input;
    bool move;

    // see who is first and second
    int second_player;
    if (first_player == 0)
    {
        second_player = 1;
    }
    else
    {
        second_player = 0;
    }

    getline(cin, input); // press a key to continue
    // start by visiting shop
    lineBreak();
    cout << "Player " << first_player + 1 << endl;
    players[first_player].itemShop();
    lineBreak();
    cout << "Player " << second_player + 1 << endl;
    players[second_player].itemShop();

    // keep looping the player menu for each player
    // if they choose to quit or reach the end, end game

    while (game.getPlayer1Position() < 50 && game.getPlayer2Position() < 50)
    {
        // menu for first player
        move = game.playerMenu(players[first_player], first_player);

        // chexk if player 1 has quit or won
        if (map.getTileColor(1, game.getPlayer1Position()) == "Yellow")
        {
            cout << endl
                 << "Congratulations Player 1! You beat the Odyssey!" << endl;
            displayMap(map, game.getPlayer1Position(), game.getPlayer2Position());

            game.setEndGame(true);
        }

        if (game.getEndGame())
        {
            cout << "The game is over :(" << endl;
            return;
        }

        // check if player 2 has quit or won
        if (map.getTileColor(2, game.getPlayer2Position()) == "Yellow")
        {
            cout << endl
                 << "Congratulations Player 2! You beat the Odyssey!" << endl;
            displayMap(map, game.getPlayer1Position(), game.getPlayer2Position());

            game.setEndGame(true);
        }

        if (game.getEndGame())
        {
            cout << "The game is over :(" << endl;
            return;
        }
        // display map after first players turn
        displayMap(map, game.getPlayer1Position(), game.getPlayer2Position());

        if (move == true)
        {
            combat(players[first_player], first_player + 1, island_enemies, epic_enemies, map, game);
        }

        if (game.getEndGame())
        {
            cout << "Player " << first_player + 1 << " died in combat." << endl << endl;
            cout << "The game is over :(" << endl;
            game.endGame(players);
            return;
        }

        // second players turn
        move = game.playerMenu(players[second_player], second_player);

        // check if player 1 has quit or won
        if (map.getTileColor(1, game.getPlayer1Position()) == "Yellow")
        {
            cout << "Congratulations Player 1! You beat the Odyssey!" << endl;
            players[0].setWin_Lose('W');
            players[1].setWin_Lose('L');
            displayMap(map, game.getPlayer1Position(), game.getPlayer2Position());

            game.setEndGame(true);
        }

        if (game.getEndGame())
        {
            cout << "The game is over :(" << endl;
            game.endGame(players);
            return;
        }

        // check if player 2 has quit or won
        if (map.getTileColor(2, game.getPlayer2Position()) == "Yellow")
        {
            cout << "Congratulations Player 2! You beat the Odyssey!" << endl;
            players[0].setWin_Lose('L');
            players[1].setWin_Lose('W');
            displayMap(map, game.getPlayer1Position(), game.getPlayer2Position());

            game.setEndGame(true);
        }

        if (game.getEndGame())
        {
            cout << "The game is over :(" << endl;
            game.endGame(players);
            return;
        }

        // display map after second players turn
        displayMap(map, game.getPlayer1Position(), game.getPlayer2Position());

        if (move == true)
        {
            combat(players[second_player], second_player + 1, island_enemies, epic_enemies, map, game);
        }

        if (game.getEndGame())
        {

            cout << "Player " << second_player + 1 << " died in combat." << endl << endl;
            cout << "The game is over :(" << endl;
            game.endGame(players);
            return;
        }
    }
}

#endif