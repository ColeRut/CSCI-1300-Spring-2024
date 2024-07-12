
#include <iostream>
#include "Entity.cpp"
#include "Game.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//public functions

Game::Game()
    {
    _players[0] = {};
    _enemies[0] = {};
    _num_players = 0;
    _num_enemies = 0;
    _end_game = false;
    }

Game::Game(Entity players[], int num_players)
{
    if (num_players > 2)
    {
        _num_players = 2;
    }
    else
    {
        _num_players = num_players;
    }


    for (int i = 0; i < _num_players; i++)
    {
        _players[i] = players[i];
    }

    _end_game = false;

}

int Game::getNumPlayers()
{
    return _num_players;
}

int Game::getNumEnemies()
{
    return _num_enemies;
}

void Game::setPlayersList(Entity players[], int num_players)
{
    switch(num_players)
    {
        case 0: 
            _num_players = num_players;
        break;
        case 1:
            _players[0] = players[0];
            _num_players = num_players;
        break;
        case 2:
            _players[0] = players[0];
            _players[1] = players[1];
            _num_players = num_players;
        break;
        default:
            if (num_players > 2)
            {
                _players[0] = players[0];
                _players[1] = players[1];
                _num_players = 2;
            }
    }
}

void Game::setEnemiesList(Entity enemies[], int num_enemies)
{
    switch(num_enemies)
    {
        case 0: 
            _num_enemies = num_enemies;
        break;
        case 1:
            _enemies[0] = enemies[0];
            _num_enemies = num_enemies;
        break;
        case 2:
            _enemies[0] = enemies[0];
            _enemies[1] = enemies[1];
            _num_enemies = num_enemies;
        break;
        default:
            if (num_enemies > 2)
            {
                _enemies[0] = enemies[0];
                _enemies[1] = enemies[1];
                _num_enemies = 2;
            }
    }
}

bool Game::setPlayer(int index, Entity new_player)
{
    if (index >= _num_players || index < 0)
    {return false;}

    else
    {
        _players[index] = new_player;
        return true;
    }
}

Entity Game::getPlayer(string name)
{
    for (int i = 0; i < _num_players; i++)
    {
        if (_players[i].getName() == name)
        {
            return _players[i];
        }
    }

    return Entity();
}

bool Game::setEnemy(int index, Entity new_enemy)
{
    if (index >= _num_enemies || index < 0)
    {
        return false;
    }

    else
    {
        _enemies[index] = new_enemy;
        return true;
    }
}

Entity Game::getEnemy(string name)
{
    for (int i = 0; i < _num_enemies; i++)
    {
        if (_enemies[i].getName() == name)
        {
            return _enemies[i];
        }
    }

    return Entity();
}

int Game::findPlayer(string name)
{
    int index  = -1;

    for (int i = 0; i < _num_players; i++)
    {
        if (_players[i].getName() == name)
        {
            index = i;
        }
    }

    return index;
}

int Game::findEnemy(string name)
{
    int index  = -1;

    for (int i = 0; i < _num_enemies; i++)
    {
        if (_enemies[i].getName() == name)
        {
            index = i;
        }
    }

    return index;
}

int Game::getPlayer1Position()
{
    return _position_player1;
}

int Game::getPlayer2Position()
{
    return _position_player2;
}

void Game::setPlayer1Position(Entity player1, int position_player1)
{
    if (position_player1 > 0)
    {
        _position_player1 = position_player1;
    }
    else
    {
        _position_player1 = 0;
    }
}

void Game::setPlayer2Position(Entity player2, int position_player2)
{
    if (position_player2 > 0)
    {
        _position_player2 = position_player2;
    }
    else
    {
        _position_player2 = 0;
    }
}

bool Game::getEndGame()
{
    return _end_game;
}

void Game::setEndGame(bool end_game)
{
    _end_game = end_game;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//other functions

bool loadCharacters(string filename, Entity characters[], const int CHARACTERS_SIZE, Equipment all_items[], Potions all_potions[])
{    
    //character size = 14 in current case

    ifstream file(filename); //open file, check if open
    if (!file.is_open())
    {
        return false;
    }

    ifstream test_file(filename); //use test file to count lines (test_file = file)

    string line;
    string character_stats[13];
    string item_start_split[2];

    int num_characters = CHARACTERS_SIZE;
    int num_lines_in_file = 0;

    while (!test_file.eof()) //read test_file and count lines
    {
        getline(test_file,line);
        num_lines_in_file += 1;
    }

    if (CHARACTERS_SIZE >= num_lines_in_file) //compare character size to num_lines (issues if char >= lines)
    {
        num_characters = num_lines_in_file - 1; //if more characters than line, set num_characters to num_lines
    }


    getline(file, line); //skips first line
    for (int i = 0; i < num_characters; i++)
    {
            getline(file, line);
            
            if (file.eof() && num_characters < CHARACTERS_SIZE && i == CHARACTERS_SIZE - 1) //if past last line, set stats to default constructor
            {
                characters[i] = Entity();
            }

            
            
            else if(line != "") //if on a non-blank line
            {
                split(line, '|',  character_stats, 13); //split and set to stat array, then set each stat to Entity character[]

                characters[i].setName(character_stats[0]);
                characters[i].setType(character_stats[1][0]);
                characters[i].setHP(stod(character_stats[2]));
                characters[i].setStamina(stod(character_stats[3]));
                characters[i].setDefense(stod(character_stats[4]));
                characters[i].setCondition(character_stats[5][0]);

                if (character_stats[6] == "True")
                {characters[i].setAdvantage(true);}
                else{characters[i].setAdvantage(false);}
                
                characters[i].setElementalWeakness(character_stats[7][0]);
                characters[i].setGold(stoi(character_stats[8]));

                split(character_stats[9], ',',  item_start_split, 2);
                characters[i].setItemStart(item_start_split, all_items, all_potions);

                characters[i].setNumPotion(stoi(character_stats[10]));
                characters[i].setNumItem(stoi(character_stats[11]));
                characters[i].setUltimate(character_stats[12]);

    //6 is a bool, double check
            }

    }

return true;
    
}

void loadPlayerList(Entity players[], Entity characters[])
{
    //4 players
    int k = 0;
    char temp;
    for (int i = 0; i < 14; i++)
    {
        temp = characters[i].getType();
        if (temp == 'P')
        {
            players[k] = characters[i];
            k++;
        }
    }
}

void loadIslandEnemyList(Entity island_enemies[], Entity characters[])
{
    int k = 0;
    char temp;
    for (int i = 0; i < 14; i++)
    {
        temp = characters[i].getType();
        if (temp == 'I')
        {
            island_enemies[k] = characters[i];
            k++;
        }
    }
}

void loadEpicEnemyList(Entity epic_enemies[], Entity characters[])
{
    int k = 0;
    char temp;
    for (int i = 0; i < 14; i++)
    {
        temp = characters[i].getType();
        if (temp == 'E')
        {
            epic_enemies[k] = characters[i];
            k++;
        }
    }
}

void Game::updatePlayerPosition(int player_number, int dice_roll)
{
    int current_position;

    if (player_number == 1)
    {
        current_position = _position_player1;
        current_position += dice_roll;

        //cant go past 50 (ithaca tile is at index 50)
            if (current_position > 50)
            {
                current_position = 50;
            }

        _position_player1 = current_position;
    }

    if (player_number == 2)
    {
        current_position = _position_player2;
        current_position += dice_roll;

            if (current_position > 50)
            {
                current_position = 50;
            }

        _position_player2 = current_position;
    }
    
}

void Game::endGame(Entity players[2])
{
    _players[0] = players[0];
    _players[1] = players[1];

    _end_game = true;
    if (_players[0].getWin_Lose() != 'W' && _players[0].getWin_Lose() != 'L')
    {
        _players[0].setWin_Lose('D');
        _players[1].setWin_Lose('D');
    }

    ofstream file("EndGameStats.txt");

    file << "Player number|Character name|win/lose|gold left|HP left|stamina left|Equipped1|Equipped2|Inventory 1-3 (| seperated)| Potions, num potions 1-3" << endl;
    
    //writing player 1 stats
    file << "1" << "|" << _players[0].getName() << "|" << _players[0].getWin_Lose() << "|" << _players[0].getGold() << "|" << _players[0].getHP() << "|" << _players[0].getCondition() << "|" << _players[0].getStamina() << "|";
    file << _players[0].getCalamityChance() << "|" << players[0].getEquipped(0).name << "|" << _players[0].getEquipped(1).name << "|";
    for (int i = 0; i < 3; i++)
    {file << _players[0].getInventory(i).name << "|";}
    for (int i = 0; i < 3; i++)
    {file << _players[0].getPotions(i).name << "," << _players[0].getPotions(i).quantity; if (i != 2) {file << "|";}}
    file << endl;


    //writing player 2 stats
    file << "2" << "|" << _players[1].getName() << "|" << _players[1].getWin_Lose() << "|" << _players[1].getGold() << "|" << _players[1].getHP() << "|"  << _players[1].getCondition() << "|" << _players[1].getStamina() << "|";
    file << _players[1].getCalamityChance() << "|" << _players[1].getEquipped(0).name << "|" << _players[1].getEquipped(1).name << "|";
    for (int i = 0; i < 3; i++)
    {file << _players[1].getInventory(i).name << "|";}
    for (int i = 0; i < 3; i++)
    {file << _players[1].getPotions(i).name << "," << _players[1].getPotions(i).quantity; if (i != 2) {file << "|";}}
    
    file.close(); //make sure the file closes

    //aftersome testing it thankfully works
}

void menu(); //menu function, possibly different menu functionsfor different actions