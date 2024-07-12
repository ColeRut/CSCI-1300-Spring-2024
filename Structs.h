#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>
using namespace std;

struct Potions
{
    string name;
    char type;//H healing, C cleanse, S stamina, U ultimate
    double effect_value;
    double price;
    int quantity;
};



struct Equipment
{
    string name;
    char type; //D damage, S shield
    char element; //W water, A air, F fire, E earth
    double damage;
    double defense;
    double price;

};

struct Riddle
{
    string question;
    string answer;
};

#endif