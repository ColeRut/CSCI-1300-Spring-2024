#ifndef COMBAT_H
#define COMBAT_H
#include "StartGame.h"

void Game::calamity(Entity& player, int player_num)
{
    //calamity can happen if you dont move or land on a blue tile
    string input;

    // random number 1-100
    srand(time(0));
    int random_num = rand() % 100 + 1;

    // if <= 30 (30% chance), do calamity
    //check for calamity chance
    if (random_num <= player.getCalamityChance())
    {
        cout << "A Calamity has struck!" << endl;
        getline(cin, input);

        // random num again for calamity type
        random_num = rand() % 100 + 1;

        // Stormy Seas (45% chance)
        if (random_num >= 45)
        {
            cout << "With each passing moment, the storm grows fiercer, testing your courage and resolve as you struggle to keep your ship afloat amidst the wrath of Poseidon." << endl;
            cout << "You cannot move for 1 turn" << endl;
            player.setCanMove(false);
        }

        // Plague Outbreak (35% chance)
        else if (random_num >= 45 + 35)
        {
            cout << "The spread of the plague seems unstoppable, defying your best efforts to contain it and leaving you to confront the harsh reality of your own mortality." << endl;
            cout << "Condition set to 'D" << endl;
            player.setCondition('D'); // when I cout the condition before and after doing this, it updates, but when i print player stats it doesnt update ???
        }

        // Poisonous Rats (20% chance)
        else
        {
            cout << "Much to your dismay, it seems you are not the only one on your ship." << endl;
            cout << "Condition set to 'P'" << endl;
            player.setCondition('P'); // when I cout the condition before and after doing this, it updates, but when i print player stats it doesnt update ???
                                      // i also tried this with losing stamina every time you move but it had the same issue

                                      //nevermind, this work snow that i learned to use references
                                      //i was struggling with passing a non-array entity before using references
        }
    }
}

void hiddenTreasure(Entity& player)
{

    //import riddles and answers
    //splitline and turn into an array
    //cout riddle, random index 
    //getline input
    //if input == answer[index], then cout you got it right and run the code below
    // if !=, cout you got it wrong and lose your turn

    //do a random percent integer
    //for stamina refill, do setstamina(get stamina + 20), if getstamina > 100 set stamina 100 (stamina isnt implemented in making moves unfortunately)
    //for gold, do random int 2-4, them setgold(getgold + randomint*10)
    //for weapon buff, do check inventory [i] fro 0-1, if weapon.type == d then weapon.damange += random num from 5-10
        //if no weapon type d, do nothing

    ifstream file("riddles.txt");
    string input;
    string line;
    //15 riddles, question + answer
    Riddle riddles[15];
    string temp[2];
    int riddle_index = 0;
    bool found_treasure;

    while (!file.eof())
    {
        getline(file, line);
        split(line, '|', temp, 2);

        //setting temp to riddles array
        //i make a struct for riddle to hold the questions and answers
        riddles[riddle_index].question = temp[0];
        riddles[riddle_index].answer = temp[1];
        riddle_index++;
    }

    //get random index 0-14
    riddle_index = rand() % 15;

    cout << endl << "Answer the following riddle to claim your reward." << endl;
    lineBreak();
    cout << riddles[riddle_index].question << endl;
    getline(cin, input);
    cout << endl;
    string answer = riddles[riddle_index].answer;

    if (input == answer)
    {
        //return true if you get it right
        cout << "Congratulations! You answerred the riddle correctly. You have found a Hidden Treasure!" << endl;
        found_treasure = true;
    }

    else
    {
        cout << "Sorry, that is incorrect. The correct answer was " << riddles[riddle_index].answer << endl;
        cout << "You cannot move on your next turn." << endl;

        //return false because input was wrong
        player.setCanMove(false);
        found_treasure = false;
    }


    //if you found the treasure
    int rand_1_100 = rand() % 100 + 1;
    int circes_brew;
    int stamina_refill;
    int gold_refill;
    double damage_buff;
    bool no_weapon = true;
    Equipment temp_weapon;
    if (found_treasure == true)
    {
        //stamina refill, 10-30
        if (rand_1_100 <= 15)
        {  
            stamina_refill = (rand() % 20 + 20);
            cout << "You found a special potion that increases your stamina. Your stamina has increased by " << stamina_refill << endl;
            player.setStamina(player.getStamina() + stamina_refill);

            //capping stamina at 100
            if (player.getStamina() > 100)
            {
                player.setStamina(100);
            }
        }

        //gold refill
        else if (rand_1_100 <= 45)
        {
            gold_refill = (rand() % 20 + 20);
            cout << "Gold starts raining from the sky! You gain " << gold_refill << " gold." << endl;
            player.setGold(player.getGold() + gold_refill);
        }

        //damage buff
        else if (rand_1_100 <= 75)
        {
            damage_buff = rand() % 6 + 5; //5-10
            for (int i = 0; i < 2; i++)
            {
                if (player.getEquipped(i).type == 'D') //check for weapon
                {
                    cout << "A soft light falls upon your weapon. " << player.getEquipped(i).name << " receives a damage buff of " << damage_buff << endl;
                    
                    temp_weapon = player.getEquipped(i); //using temp to update the equipped weapon
                    temp_weapon.damage += damage_buff; //add damage to weapon
                    player.setEquipped(temp_weapon, i);

                    no_weapon = false;
                    break;
                }
            }

            //if you don't have a weapon attached, do noting
            if (no_weapon == true)
            {
                cout << "A soft light falls upon you, but you have no weapons equipped. Nothing happens." << endl;
            }


        }

        //circe's brew
        else
        {
            cout << "You found Circe's brew." << endl;
            getline(cin, input);
            circes_brew = rand() % 100 + 1;

            //30% snake
            //set condition to healthy
            if (circes_brew <= 30)
            {
                cout << "You've become an elusive serpent. You are now immune to poison. Your condition is set to 'H'" << endl;
                player.setCondition('H');
            }

            //70% chance Lion
            //buff equipped weapons by 10
            else if (circes_brew <= 70)
            {
                cout << "You've become a ferocious lion. Your equipped weapons gain 10 damage." << endl;

                //adding damage to weapon
                for (int i = 0; i < 2; i++)
                {
                    if (player.getEquipped(i).type == 'D') //check for weapon
                    {
                        temp_weapon = player.getEquipped(i); //using temp to update the equipped weapon
                        temp_weapon.damage += 10; //add damage to weapon
                        player.setEquipped(temp_weapon, i);
                    }
                }

            }

            //30% chance wolf
            //give player advantage
            else
            {
                cout << "You've become an agile wolf. You now have an advantage in combat." << endl;
                player.setAdvantage(true);
            }


        }
    }

    

}

bool whoGoesFirst(Entity player, Entity enemy)
{
//return true when player goes first
    bool player_advantage = player.getAdvantage();
    bool enemy_advantage = enemy.getAdvantage();
    int dice_roll;
//if enemy and player have advantage
//roll die
    if (player_advantage == enemy_advantage)
    {

            //roll dice and % 2 so it is even or odd
            //(kept getting errors with rolling for both because rolling at the same time lags it out)
            //50% chance for who has advantage
            dice_roll = diceRoll() % 2;

            //if odd, return true
            if (dice_roll == 1)
            {
                return true;
            }

            //if even, return false
            else if (dice_roll == 0)
            {
                return false;
            }

        
    }

    //if player has advantage and enemy doesnt
    else if (player_advantage == true && enemy_advantage == false)
    {
        return true;
    }

    //if enemy has advantage andplayer doesnt
    else if(player_advantage == false && enemy_advantage == true)
    {
        return false;
    }

cout << "If you see this the function is messed up" << endl;
return true;
}

void playerAttack(Entity& player, Entity& enemy)
{
    string input;
    double roll1;
    double roll2;
    double damage;

    cout << endl << "Rolling for player damage" << endl;
    getline(cin, input);
    roll1 = diceRoll();
    cout << fixed << setprecision(0) << "You rolled a " << roll1 << endl;
    getline(cin, input);
    cout << "Rolling for damage multiplier" << endl;
    getline(cin, input);
    roll2 = diceRoll();
    cout << fixed << setprecision(0) << "You rolled a " << roll2 << endl;
    getline(cin, input);
    damage = roll1*roll2 - enemy.getDefense();
    

    if (damage < 0)
    {
        damage = 0;
    }

    cout << fixed << setprecision(0) << "Enemy has " << enemy.getDefense() << " defense. You will do (" << roll1 << "*" << roll2 << ") - " << enemy.getDefense() << " = " <<  damage << " damage." << endl;
    getline(cin, input);

    for (int i = 0; i < 2; i++)
    {
        if (player.getEquipped(i).type == 'D')
        {
            damage += player.getEquipped(i).damage;
            cout << "Your equipped weapon " << player.getEquipped(i).name << " adds " << player.getEquipped(i).damage << " damage!" << endl;
        }
    }

    enemy.setHP(enemy.getHP() - damage);
    if (enemy.getHP() < 0)
    {
        enemy.setHP(0);
    }

    cout << "Enemy took " << damage << " damage. They now have " << enemy.getHP() << " HP." << endl;

}

void enemyAttack(Entity& player, Entity& enemy)
{
    string input;
    double roll1;
    double roll2;
    double damage;

    cout << endl << endl << "Rolling for enemy damage" << endl;
    getline(cin, input);
    roll1 = diceRoll();
    cout << fixed << setprecision(0) << "They rolled a " << roll1 << endl;
    getline(cin, input);
    cout << "Rolling for damage multiplier" << endl;
    getline(cin, input);
    roll2 = diceRoll();
    cout << fixed << setprecision(0) << "They rolled a " << roll2 << endl;
    getline(cin, input);
    damage = roll1*roll2 - player.getDefense();
    

    if (damage < 0)
    {
        damage = 0;
    }

    cout << fixed << setprecision(0) << "You have " << player.getDefense() << " defense. Enemy will do (" << roll1 << "*" << roll2 << ") - " << player.getDefense() << " = " <<  damage << " damage." << endl;
    getline(cin, input);

    for (int i = 0; i < 2; i++)
    {
        if (player.getEquipped(i).type == 'S')
        {
            damage -= player.getEquipped(i).defense;
            cout << "Your equipped shield " << player.getEquipped(i).name << " subtracts " << player.getEquipped(i).defense << " damage!" << endl;
        }
    }

    if (damage < 0)
    {
        damage = 0;
    }

    player.setHP(player.getHP() - damage);
    if (player.getHP() < 0)
    {
        player.setHP(0);
    }

    cout << "You took " << damage << " damage. You now have " << player.getHP() << " HP." << endl;

}

void Game::combatMenu(Entity& player, Entity& enemy, string first_move)
{

    string input = "";
    string filler;
    int potion_index;
    int weapon_index;
    bool empty_potions;
    bool someone_died = false;


while (someone_died == false && input != "4")
{
    getline(cin, input);
    cout << endl;
    cout << "Player stats:" << endl;
    player.printStats();
    cout << endl;
    cout << "Enemy Stats:" << endl;
    enemy.printStats();


//so enemy can go first if they rolled to go first
            //only haoppens once
            if (first_move == "enemy")
            {
                enemyAttack(player, enemy);
                first_move = "";
            }

        cout << endl << "Choose an action:" << endl;
        cout << "1: Attack" << endl;
        cout << "2: Use potion" << endl;
        cout << "3: Swap equipment and inventory" << endl;
        cout << "4: Run" << endl;

        getline(cin, input);

        //attacking
        if (input == "1")
        {


            playerAttack(player, enemy);
            enemyAttack(player, enemy);

            //if enemy is dead
            if (enemy.getHP() <= 0)
            {
                cout << "Congratulations! You defeated " << enemy.getName() << ". You picked up all their gold." << endl;
                player.setGold(player.getGold() + enemy.getGold());

                cout << enemy.getName() << " dropped " << enemy.getGold() << " gold. You now have " << player.getGold() << " gold." << endl;
                break;
            }


            if (player.getHP() <= 0)
            {
                cout << endl << "HP: 0" << endl;
                setEndGame(true);
                someone_died = true;
                break;
            }

        }

        //use potions
        else if (input == "2")
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
                    cout << endl << "You are out of Potions!" << endl << endl;
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
        }

        //to run
        else if (input == "4")
        {
            cout << endl << "You ran away successfully, but you dropped your all gold while escaping." << endl << endl;
            player.setGold(0);
        }
        
        else
        {
            cout << endl << "Enter a valid input" << endl << endl;
        }
}

//visit item shop after combat
        if (someone_died == false)
        {
            player.itemShop();
        }

}

void combat(Entity& player, int player_number, Entity island_enemies[], Entity epic_enemies[], Map& map, Game& game)
{ //called combat but really its whenever you move and land on a tile

    //references saved my life
    //thank you TA Mohhamad

    string tile_color;
    string input;
    
    if (player_number == 1) 
    {
        tile_color = map.getTileColor(1, game.getPlayer1Position());
    }
    else
    {
        tile_color = map.getTileColor(2, game.getPlayer2Position());
    }

    cout << endl << "Player " << player_number << " has landed on a " << tile_color << " tile." << endl << endl;
    //player.printStats();


    //special tile
    int rand_num_1_100 = rand() % 100 + 1;
    int rand_50_50 = rand() % 2 + 1;
    if (tile_color == "Red")
    {
        
        //50% chance for treasure
        //count up the number of treasures found
        //when it hits 3, stop finding treasure

        //50% chance of doing a treasure
        if (rand_50_50 == 1 && player.getNumTreasureFound() < 3)
        {
            //hidden treasure!
            //do hidden treasure function
            //update how many the player has found, that way it only finds 3 max

            cout << "You have encountered a Hidden Treasure!" << endl;
            player.setNumTreasureFound(player.getNumTreasureFound() + 1);
            hiddenTreasure(player);
            //if you answer the riddle right
           
            
            
        }


        //regular special tile things (not treasure)
        else
        {
            //nymph
            if (rand_num_1_100 <= 25)
            {
                cout << "You encountered the Nymph's Spring." << endl;
                cout << "In the embrace of the Nymph's Spring, you feel the embrace of nature itself. Your stamina is replenished." << endl;
                player.setStamina(100);
            }

            //siren
            else if (rand_num_1_100 <= 50)
            {
                cout << "You encountered the Sirens' Song." << endl;
                cout << "As the Siren's Song echoes through the air, you sense its magical pull, an otherworldly force that toys with the hearts of those who dare to listen. ";
                cout << "You stop in your tracks. You cannot move your next turn." << endl;
                player.setCanMove(false);

            }

            //shortcut
            else if (rand_num_1_100 <= 75)
            {
                cout << "You have found a shortcut!" << endl;
                cout << "Move up 3 tiles." << endl;
                game.updatePlayerPosition(player_number, 3);
                displayMap(map, game.getPlayer1Position(), game.getPlayer2Position());
            }

            //helios
            else if (rand_num_1_100 <= 100)
            {
                cout << "You enecountered Helios' Beacon." << endl;
                player.setCalamityChance(player.getCalamityChance() - 5);
                cout << "Your chance of Calamity has reduced by 5. You now have a " << player.getCalamityChance() << "% chance of a Calamity." << endl;
            }
        }

    }

    //normal (safe) tile
    else if (tile_color == "Blue")
    {
        //30% chance of calamity
        game.calamity(player, player_number);
    }

    //island enemy
    else if (tile_color == "Green")
    {
        //random island enemy from array
        int island_enemy_index = rand() % 7;
        Entity enemy = island_enemies[island_enemy_index];

        cout << "You landed on an island and encountered " << enemy.getName() << endl;
        cout << "Entering combat." << endl << endl;
        getline(cin, input);
        cout << "Rolling to see who does first." << endl;
        
        //see who goes first
        if (whoGoesFirst(player, enemy))
        {
            cout << "You rolled higher. Player goes first." << endl;
            game.combatMenu(player, enemy, "player");
        }
        else
        {
            cout << "Enemy rolled higher. They go first." << endl << endl;
            
            //take this out
            game.combatMenu(player, enemy, "enemy");
        }




    }

}


#endif