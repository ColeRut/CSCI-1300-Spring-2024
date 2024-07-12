#include <iostream>
#include "Entity.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//getters

    Entity::Entity()
    {
        _name = "";
        _type = 'P';
        _hp = 0;
        _stamina = 0;
        _defense = 0;
        _condition = 'H';
        _advantage = false;
        _elemental_weakness = 'W';
        _gold = 0;
        _item_start[0] = "";
        _item_start[1] = "";
        _num_potion = 0;
        _num_item = 0;
        _ultimate = "none";
        _calamity_chance = 30;
        _num_treasure_found = 0;
        _can_move = true;

    }
    
    Entity::Entity(string name, char type, double hp, double stamina, double defense, char condition, bool advantage, char elemental_weakness, int gold, string item_start[], int num_potion, int num_item, string ultimate)
    {
        _name = name;

        setType(type);
        
        if (hp > 0)
        {_hp = hp;}
        else
        {_hp = 0;}

        if (stamina > 0)
        {_stamina = stamina;}
        else
        {_stamina = 0;}

        if (defense > 0)
        {_defense = defense;}
        else
        {_defense = 0;}

        
        if (validateCondition(condition))
        {
            _condition = condition;
        }
        else
        {
            _condition = 'H';
        }
        
        _advantage = advantage;


        if (validateElementalWeakness(elemental_weakness))
        {
            _elemental_weakness = elemental_weakness;
        }
        else
        {
            _elemental_weakness = 'W';
        }

        if (gold > 0)
        {_gold = gold;}
        else
        {_gold = 0;}
        
        //////
        _item_start[0] = "";
        _item_start[1] = "";
        //////

        if (num_potion > 0)
        {
            _num_potion = num_potion;
        }
        else
        {_num_potion = 0;}

        if (num_item > 0)
        {
            _num_item = num_item;
        }
        else
        {_num_item = 0;}

        setUltimate(ultimate);

        _calamity_chance = 30;
        _num_treasure_found = 0;
        _can_move = true;
    }

    string Entity::getName()
    {
        return _name;
    }

    char Entity::getType()
    {
        return _type;
    }

    double Entity::getHP()
    {
        return _hp;
    }

    double Entity::getStamina()
    {
        return _stamina;
    }

    double Entity::getDefense()
    {
        return _defense;
    }

    char Entity::getCondition()
    {
        return _condition;
    }

    bool Entity::getAdvantage()
    {
        return _advantage;
    }

    char Entity::getElementalWeakness()
    {
        return _elemental_weakness;
    }

    string Entity::getItemStart0()
    {
        return _item_start[0];
    }

    string Entity::getItemStart1()
    {
        return _item_start[1];
    }

    int Entity::getNumPotion()
    {
        return _num_potion;
    }

    int Entity::getNumItem()
    {
        return _num_item;
    }

    string Entity::getUltimate()
    {
        return _ultimate;
    }

    Potions Entity::getPotions(int index)
    {
        return _potions[index]; //gets potions at index index
    }

    Equipment Entity::getEquipped(int index)
    {
        return _equipped[index]; //gets equipped at index index
    }

    Equipment Entity::getInventory(int index)
    {
        return _inventory[index]; //gets inventory at index index
    }

//////////
    int Entity::getItems(int index)
    {
        return _items[index]; //gets items at index index
    }

    int Entity::getGold()
    {
        return _gold;
    }

    float Entity::getCalamity()
    {
        return _calamity;
    }

    char Entity::getWin_Lose()
    {
        return _win_lose;
    }


///////////////////////////////////////////////////////////////////////////////////////////////
//setters
    void Entity::setName(string name)
    {
        _name = name;
    }

    void Entity::setType(char type)
    {
        if (validateType(type))
        {
            _type = type;
        }
        else
        {_type = 'P';}
    }

    void Entity::setHP(double hp)
    {
        if (hp > 0)
        {
            _hp = hp;
        }
        else
        {_hp = 0;}
    }

    void Entity::setStamina(double stamina)
    {
        if (stamina > 0)
        {
            _stamina = stamina;
        }
        else
        {_stamina = 0;}
    }

    void Entity::setDefense(double defense)
    {
        if (defense > 0)
        {_defense = defense;}
        else
        {_defense = 0;}
    }

    void Entity::setCondition(char condition)
    {
        if (validateCondition(condition))
        {
            _condition = condition;
        }
        else
        {
            _condition = 'H';
        }
    }

    void Entity::setAdvantage(bool advantage)
    {
        _advantage = advantage;
    }

    void Entity::setElementalWeakness(char elemental_weakness)
    {
        if (validateElementalWeakness(elemental_weakness))
        {
            _elemental_weakness = elemental_weakness;
        }
        else
        {
            _elemental_weakness = 'W';
        }
    }

    void Entity::setItemStart(string item_start_name[], Equipment all_items[], Potions all_potions[])
    {
        if (validatePotion(item_start_name[0]))
        {
            for (int i = 0; i < 11; i++)
            {
                if (item_start_name[0] == all_potions[i].name)
                {
                    _item_start[0] = all_potions[i].name;
                }
            }
        }
        else
        {
            _item_start[0] = "";
        }

        if (validateItem(item_start_name[1]))
        {
            for (int i = 0; i < 15; i++)
            {
                if (item_start_name[1] == all_items[i].name)
                {
                    _item_start[1] = all_items[i].name;
                }
            }
        }
        else
        {
            _item_start[1] = "";
        }
    }

    void Entity::setNumPotion(int num_potion)
    {
        if (num_potion > 0)
        {
            _num_potion = num_potion;
        }
        else
        {_num_potion = 0;}
    }

    void Entity::setNumItem(int num_item)
    {
        if (num_item > 0)
        {
            _num_item = num_item;
        }
        else
        {_num_item = 0;}
    }

    void Entity::setUltimate(string ultimate)
    {
        if (validateUltimate(ultimate))
        {
            _ultimate = ultimate;
        }
        else
        {
            _ultimate = "none";
        }
    }

    void Entity::setPotions(Potions potion, int index)
    {
        if (index >= 0 && index < 3)
        {
            _potions[index] = potion;
        }
    }

    void Entity::setEquipped(Equipment equipped, int index) //Equipment equipped[2], W and S or W and W
    {
        if (index >= 0 && index < 2)
        {
            _equipped[index] = equipped;
        }
    }

    void Entity::setInventory(Equipment inventory, int index) //Equipment inventory[maxinventory]
    {
        if (index >= 0 && index < _MAX_INVENTORY)
        {
            _inventory[index] = inventory;
        }
    }

    void Entity::setItems(int item, int index) //int items[], num potions and num invetory+equipped
    {
        if (index >= 0 && index < 2)
        {
            _items[index] = item;
        }
    }

    void Entity::setGold(int gold) //int gold
    {
        if (gold > 0)
        {
            _gold = gold;
        }
        else
        {_gold = 0;}
    }

    void Entity::setCalamity(float calamity) //float calamity
    {
        if (calamity > 0)
        {
            _calamity = calamity;
        }
        else
        {_calamity = 0;}
    }

    void Entity::setWin_Lose(char win_lose)
    {
        _win_lose = win_lose;
    }

//do set items, gold, calamity

///////////////////////////////////////////////////////////////////////////////////////////////
//other functions

    void Entity::swap(int equipped_index, int inventory_index) //swaps inventory and equipped item
    {
        //for equipped to inventory, ill make a take in the equipped index and inventory index to swap
        //then set a temp = equippeditem --> equippeditem = inventoryitem, inventoryitem = temp

        Equipment temp;

        temp = _inventory[inventory_index];
        _inventory[inventory_index] = _equipped[equipped_index];
        _equipped[equipped_index] = temp;

    }

    void Entity::dropPotions(int index) //int index, drops potion at index from _potions[]
    {
        //if holding multiple potions, reduce quantity by 1
        //else reset index to blank
        if (index >= 0 && index < 3)
        {
            if (_potions[index].quantity > 1)
            {
                _potions[index].quantity--;
            }
            else
            {
                _potions[index] = Potions();
            }
        }
    }

    void Entity::dropInventory(int index) 
    {
        if (index >= 0 && index < _MAX_INVENTORY)
        {
            _inventory[index] = Equipment();
        }
    }

    void Entity::dropEquipped(int index) //int iserChoise, drops weapon or potion
    {
        if (index >= 0 && index < 2)
        {
            _equipped[index] = Equipment();
        }
    }

    void Entity::usePotion(int index, Equipment weapon) //int userChoise, usespotions
    {

        //check each available potion
        //update player stats by the specified amount

        if (_potions[index].name == "Lesser Health Potion")
        {
            _hp += 10;
        }

        if (_potions[index].name == "Greater Health Potion")
        {
            _hp += 25;
        }

        if (_potions[index].name == "Lesser Stamina Potion")
        {
            _stamina += 10;
        }

        if (_potions[index].name == "Greater Stamina Potion")
        {
            _stamina += 25;
        }

        if (_potions[index].name == "Cleansing Potion")
        {
            _condition = 'H';
        }

        if (_potions[index].name == "Greater Rejuvenation Potion")
        {
            _hp += 25;
            _stamina += 25;
        }

        if (_potions[index].name == "Lesser Rejuvenation Potion")
        {
            _hp += 10;
            _stamina += 10;
        }

        if (_potions[index].name == "Minor Strength Potion")
        {
            weapon.damage += 2;
        }

        if (_potions[index].name == "Major Strength Potion")
        {
            weapon.damage += 5;
        }

        //drop potion after using it (reduces quantity by 1)
        dropPotions(index);


    }

    void Entity::updateEquipment(int equipIndex, Equipment weapon) //int equiopIndex, Eqipment weapon, uses weapon weapon to update weapon at index
    {
        //im not entirely sure what this one does, but im guessing it just replaces a weapon and drops the original
        //to do this, im gonna just use my drop equipped function then setEquipped at the same index
        //I don't even use this in the game
        dropEquipped(equipIndex);
        setEquipped(weapon, equipIndex);
    }

    bool Entity::addPotion(Potions potion)
    {
        //adds potions to empty potion slot or to existing potion (false if full)

        //increase quantity by 1 to existing potion in index
        for (int i = 0; i < 3; i++)
        {
            if (_potions[i].name == potion.name)
            {
                _potions[i].quantity++;
                return true;
            }
        }

        //if not existing already, add to new index
        for (int i = 0; i < 3; i++)
        {
            if (_potions[i].name == "")
            {
                _potions[i] = potion;
                _potions[i].quantity = 1;
                return true;
            }
        }

        //return false if potion index is full
        return false;
    }

    bool Entity::addEquipment(Equipment equipment)
{
    //adds equipment to empty inventory slot
    for (int i = 0; i < _MAX_INVENTORY; i++)
    {
        if (_inventory[i].name == "")
        {
            _inventory[i] = equipment;
            return true;
        }
    }

    return false;
}

void Entity::printStats()
{
    cout << "Name: " << _name << endl;
    cout << fixed << setprecision(2) << "HP: " << _hp << endl;
    cout << fixed << setprecision(2) << "Stamina: " << _stamina << endl;
    cout << fixed << setprecision(2) << "Defense: " << _defense << endl;
    cout << "Gold: " << _gold << endl;
    cout << "Condition: " << _condition << endl;
    cout << "Advantage: " << boolalpha << _advantage << endl;
    cout << "Elemental Weakness: " << _elemental_weakness << endl;

}

void Entity::displayInventory()
{
    cout << "{";
    for (int i = 0; i < 3; i++)
    {
        cout << i+1 << ". " << _inventory[i].name;
        if (i != 2)
        {
            cout << ", ";
        }
    }
    cout << "}" << endl;
}

void Entity::displayPotions()
{
    cout << "{";
    for (int i = 0; i < 3; i++)
    {
        cout << i+1 << ". " << _potions[i].name << " (" << _potions[i].quantity << ")";
        if (i != 2)
        {
            cout << "  |  ";
        }
    }
    cout << "}" << endl;
}

void Entity::displayEquipped()
{
    cout << "{";
    for (int i = 0; i < 2; i++)
    {
        cout << i+1 << ". " << _equipped[i].name;
        if (i != 1)
        {
            cout << ", ";
        }
    }
    cout << "}" << endl;
}


int Entity::getCalamityChance()
{
    return _calamity_chance;
}

void Entity::setCalamityChance(int calamity_chance)
{
    _calamity_chance = calamity_chance;
}

int Entity::getNumTreasureFound()
{
    return _num_treasure_found;
}

void Entity::setNumTreasureFound(int num_treasure_found)
{
    _num_treasure_found = num_treasure_found;
}

bool Entity::getCanMove()
{
    return _can_move;
}

void Entity::setCanMove(bool can_move)
{
    _can_move = can_move;
}

