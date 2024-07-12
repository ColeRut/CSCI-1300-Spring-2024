#ifndef ENTITY_H
#define ENTITY_H
#include "UsefulFunctions.h"
#include "Structs.h"






class Entity
{

private:
    
    const static int _MAX_INVENTORY = 3;

    string _name;
    char _type;
    double _hp;
    double _stamina;
    double _defense;
    char _condition;
    bool _advantage;
    char _elemental_weakness;
    string _item_start_name[2];
    string _item_start[2];
    int _num_potion;
    int _num_item;
    string _ultimate;
    Potions _potions[3]; //3 slots
    Equipment _equipped[2]; //weapon and shield or 2 weapons
    Equipment _inventory[_MAX_INVENTORY];
    int _items[2]; //potions, equipment
    int _gold;
    float _calamity; //probability of encountering calamity
    char _win_lose;
    int _calamity_chance;
    int _num_treasure_found;
    bool _can_move;

public:
    Entity();
    Entity(string, char, double, double, double, char, bool, char, int, string[], int, int, string);
    string getName();
    char getType();
    double getHP();
    double getStamina();
    double getDefense();
    char getCondition();
    bool getAdvantage();
    char getElementalWeakness();
    string getItemStart0();
    string getItemStart1();
    int getNumPotion();
    int getNumItem();
    string getUltimate();
    Potions getPotions(int);
    Equipment getEquipped(int);
    Equipment getInventory(int);
    int getItems(int);
    int getGold();
    float getCalamity();
    char getWin_Lose();

    void setName(string); //string name
    void setType(char);
    void setHP(double); //double hp
    void setStamina(double); //double stamina
    void setDefense(double); //double defense
    void setCondition(char); //char condition
    void setAdvantage(bool); //bool advantage
    void setWin_Lose(char);

    void setElementalWeakness(char);
    void setItemStart(string[], Equipment[], Potions[]);
    void setNumPotion(int);
    void setNumItem(int);
    void setUltimate(string);

    void setPotions(Potions, int); //Potions potions[3]
    void setEquipped(Equipment, int); //Equipment equipped[2], W and S or W and W
    void setInventory(Equipment, int); //Equipment inventory[maxinventory]
    void setItems(int, int); //int items[], num potions and num invetory+equipped
    void setGold(int); //int gold
    void setCalamity(float); //float calamity

    void swap(int, int); //int userChoic, changes weapons or potions
    void dropPotions(int); //int index, drops potions from potions index
    void dropInventory(int);
    void dropEquipped(int);
    void usePotion(int, Equipment); //int userChoise, usespotions
    void updateEquipment(int, Equipment); //int equiopIndex, Eqipment weapon, uses weapon weapon to update weapon at index
    bool addPotion(Potions); //add potion to index
    bool addEquipment(Equipment); //adds equipment to end of inventory index, returns false if full

    void printStats();
    void displayInventory();
    void displayPotions();
    void displayEquipped();

    void itemShop(); //in StartGame.h

    int getCalamityChance();
    void setCalamityChance(int);
    int getNumTreasureFound();
    void setNumTreasureFound(int);
    bool getCanMove();
    void setCanMove(bool);

};


#endif