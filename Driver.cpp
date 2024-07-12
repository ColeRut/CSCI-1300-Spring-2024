#include "GameFlow.h"



int main()
{
    //loading and selecting eveything
    Entity heroes[4];
    Entity players[2];
    Equipment all_items[16];
    Potions all_potions[11];
    loadAllItems(all_items);
    loadAllPotions(all_potions);
    loadPlayers(heroes, all_items, all_potions);
    selectCharacter(heroes, players, all_items, all_potions);
    Game game(players, 2);

    //loading enemies
    Entity characters[14];
    loadCharacters("entity.txt", characters, 14, all_items, all_potions);
    Entity island_enemies[7];
    Entity epic_enemies[3];

    loadEpicEnemyList(epic_enemies, characters);
    loadIslandEnemyList(island_enemies, characters);

// map cout
    game.setPlayer1Position(players[0], 0);
    game.setPlayer2Position(players[1], 0);
    srand (time(NULL));

    Map map = Map();
    // initialize tiles
    map.initializeMap();
    displayMap(map, game.getPlayer1Position(), game.getPlayer2Position());
    lineBreak();


    int first_player = whichPlayerGoesFirst();

    gameFlow(players, first_player, game, map, all_items, all_potions, island_enemies, epic_enemies);
    cout << endl;

    game.endGame(players);
    return 0;
}
