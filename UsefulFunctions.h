#ifndef USEFULFUNCTIONS_H
#define USEFULFUNCTIONS_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h>
using namespace std;

bool validateInt(string input)
{
    int length = input.length();\
    bool validity = true;

    for (int i = 0; i < length; i++)
    {
        if (input[i] < 48 || input[i] > 57)
        {
            validity = false;
            i = length + 1;
        }

    }

    return validity;
}

bool validateDouble(string input)
{
    int length = input.length();
    bool validity = true;
    int period_counter = 0;
    int digit_counter = 0;

    for (int i = 0; i < length; i++)
    {
        if (input[i] == ',')
        {
            period_counter++;
        }
    }

    for (int i = 0; i < length; i++)
    {
        if (isdigit(input[i]))
        {
            digit_counter++;
        }
    }

    if (period_counter > 1 || digit_counter == 0)
    {
        validity = false;
    }

    else if (input[0] == '-')
    {
        for (int i = 1; i < length; i++)
        {
            if (!(isdigit(input[i])) && input[i] != '.')
            {
                validity = false;
            }
        }
    }

    else
    {
        for (int i = 1; i < length; i++)
        {
            if (!(isdigit(input[i])) && input[i] != '.')
            {
                validity = false;
            }
        }
    }

    return validity;
}

int split(string input_string, char separator, string arr[], const int ARR_SIZE)
{
    input_string += separator;
    int input_string_length = input_string.length();
    int num_separator = 0;
    string substring = "";


    if (input_string == "")
    {
        return 0;
    }

    else
    {
        for (int i = 0; i < input_string_length; i++)
        {  
            
            if (input_string[i] != separator)
            {
                substring += input_string[i];
            }

            else
            {
                arr[num_separator] = substring;
                num_separator++;
                substring = "";
            }

            if (num_separator == ARR_SIZE && (i+1) < input_string_length)
            {
                return -1;
            }
            else if (num_separator == ARR_SIZE)
            {
                break;
            }
        }
        return num_separator;
    }
}

//make function for valid ultimate, valid item, valid condition, valid weakness

bool validateElementalWeakness(char elementalWeakness)
{
    if (elementalWeakness == 'E' || elementalWeakness == 'A' || elementalWeakness == 'F' || elementalWeakness == 'W')
    {
        return true;
    }

    else
    {return false;}
}

bool validateCondition(char condition)
{
    if (condition == 'H' || condition == 'D' || condition == 'P')
    {
        return true;
    }

    else
    {return false;}

}

bool validateType(char type)
{
    if (type == 'I' || type == 'E' || type == 'P')
    {
        return true;
    }
    else
    {return false;}
}

bool validateItem(string item)
{
    ifstream item_file("items.txt");
    
    string line;
    string item_stats[6];
    int k = 0;
    
    while(!item_file.eof())
    {
        getline(item_file, line);
        split(line, '|', item_stats, 6);

        if (item == item_stats[0] || item == "Health Potion")
        {
            k++;
        }
    }

    item_file.close();

    if (k == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool validatePotion(string potion_name)
{
    ifstream potion_file("potions.txt");
    
    string line;
    string potion_stats[6];
    int k = 0;
    
    while(!potion_file.eof())
    {
        getline(potion_file, line);
        split(line, '|', potion_stats, 6);

        if (potion_name == potion_stats[0])
        {
            k++;
        }
    }

    potion_file.close();

    if (k == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool validateUltimate(string ultimate)
{
    if (ultimate == "none")
    {
        return true;
    }
    return false;
}

int diceRoll()
{
    srand(time(0));
    int roll = rand() % 6 +1;
    return roll;
}

void lineBreak()
{
    cout << "--------------------------------------------------------------------------" << endl;
}

#endif