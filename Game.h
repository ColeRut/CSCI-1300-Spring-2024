#ifndef GAME_H
#define GAME_H
#include "Entity.h"
#include "Map.h"



class Game
{

private:
    const static int _MAX_POTIONS = 3;
    const static int _MAX_EQUIPMENT = 2;

    Entity _players[2];
    Entity _enemies[2];
    int _num_players;
    int _num_enemies;
    int _position_player1;
    int _position_player2;
    Potions _allPotions[_MAX_POTIONS]; //add num_potions
    Equipment _allEqipment[_MAX_EQUIPMENT]; //add num_equipment
    bool _end_game;

    //possibly add num_gold_spent, num_damage_dealt

public:
    Game();
    Game(Entity[], int);
    int getNumPlayers();
    int getNumEnemies();
    void setPlayersList(Entity[], int);
    void setEnemiesList(Entity[], int);
    bool setPlayer(int, Entity);
    Entity getPlayer(string);
    bool setEnemy(int, Entity);
    Entity getEnemy(string);
    int findPlayer(string);
    int findEnemy(string);
    int getPlayer1Position();
    void setPlayer1Position(Entity, int); //entity player, current position
    int getPlayer2Position();
    void setPlayer2Position(Entity, int); //entity player, current position
    void updatePlayerPosition(int, int);
    bool getEndGame();
    void setEndGame(bool);




    
    int epicCombat(Entity, Entity, Entity); //player1, player2, enemy
    void shop(Potions, Equipment); //all_potions[], all_equipment[}, randomizes somehow
    void loadEntity(); //loads player and enemies
    void playGame(); //controls gameflow, combat, turn taking, etc
    void endGame(Entity[]);
    bool playerMenu(Entity&, int);

    void calamity(Entity& player, int player_num);
    void endTurn(Entity& player, int player_num);
    void combatMenu(Entity& player, Entity& enemy, string);

};



#endif