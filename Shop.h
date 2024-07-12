#ifndef SHOP_H
#define SHOP_H
#include "Entity.h"

bool loadAllItems(Equipment all_items[])
{

    // all_item size = 16 in current case

    ifstream file("items.txt"); // open file, check if open
    if (!file.is_open())
    {
        return false;
    }

    ifstream test_file("items.txt"); // use test file to count lines (test_file = file)

    string line;
    string item_stats[6];

    getline(file, line); // skips first line
    for (int i = 0; i < 16; i++)
    {
        getline(file, line);

        if (line != "") // if on a non-blank line
        {
            split(line, '|', item_stats, 6); // split and set to stat array, then set each stat to Entity character[]

            all_items[i].name = item_stats[0];
            all_items[i].type = item_stats[2][0];
            all_items[i].element = item_stats[4][0];
            all_items[i].price = stod(item_stats[5]);

            if (all_items[i].type == 'D')
            {
                all_items[i].damage = stod(item_stats[3]);
                all_items[i].defense = 0;
            }

            else if (all_items[i].type == 'S')
            {
                all_items[i].defense = stod(item_stats[3]);
                all_items[i].damage = 0;
            }
        }

        // make potion and item array
    }

    return true;
}

bool loadAllPotions(Potions all_potions[])
{

    // all_item size = 26 in current case

    ifstream file("potions.txt"); // open file, check if open
    if (!file.is_open())
    {
        return false;
    }

    ifstream test_file("potions.txt"); // use test file to count lines (test_file = file)

    string line;
    string potion_stats[6];

    getline(file, line); // skips first line
    for (int i = 0; i < 11; i++)
    {
        getline(file, line);

        if (line != "") // if on a non-blank line
        {
            split(line, '|', potion_stats, 6); // split and set to stat array, then set each stat to Entity character[]

            all_potions[i].name = potion_stats[0];
            all_potions[i].type = potion_stats[2][0];
            all_potions[i].effect_value = stod(potion_stats[3]);
            all_potions[i].price = stod(potion_stats[5]);
            all_potions[i].quantity = 1;
        }

        // make potion and item array
    }

    return true;
}


void Entity::itemShop()
{
    //load items
    Equipment all_items[16];
    Potions all_potions[11];
    loadAllItems(all_items);
    loadAllPotions(all_potions);


    // take out epic weapons
    Equipment items_without_epic[12];
    int j = 0;
    for (int i = 0; i < 15; i++)
    {
        if (all_items[i].price != 0)
        {
            items_without_epic[j] = all_items[i];
            j++;
        }
    }

    // get random index
    srand(time(0));
    int rand_item1 = rand() % 12;
    int rand_item2 = rand() % 12;
    int rand_item3 = rand() % 12;

    // while any indices are equal, step up 1
    // make sure that rand_item cant be out of bounds (only 0-11)
    while (rand_item2 == rand_item1)
    {
        rand_item2++;
        if (rand_item2 >= 12)
        {
            rand_item2 = 0;
        }
    }
    // rand3 cant be equal to 1 or 2 and must be in bounds
    while (rand_item3 == rand_item1 || rand_item3 == rand_item2)
    {
        rand_item3++;
        if (rand_item3 >= 12)
        {
            rand_item3 = 0;
        }
    }

    // same thing for potion but with (0-10)
    int rand_potion1 = rand() % 11;
    int rand_potion2 = rand() % 11;
    int rand_potion3 = rand() % 11;

    while (rand_potion2 == rand_potion1)
    {
        rand_potion2++;
        if (rand_potion2 >= 11)
        {
            rand_potion2 = 0;
        }
    }
    while (rand_potion3 == rand_potion1 || rand_potion3 == rand_potion2)
    {
        rand_potion3++;
        if (rand_potion3 >= 11)
        {
            rand_potion3 = 0;
        }
    }

    // things for sale array
    Equipment items_for_sale[3] = {items_without_epic[rand_item1], items_without_epic[rand_item2], items_without_epic[rand_item3]};
    Potions potions_for_sale[3] = {all_potions[rand_potion1], all_potions[rand_potion2], all_potions[rand_potion3]};

    string input;
    int choice1 = -1;
    int choice2 = -1;
    int choice3 = -1;
    int drop_index = -1;
    bool purchased_weapon = false;
    bool purchased_potion = false;
    bool full_inventory = true;
    bool dropped_item = false;
    bool dropped_potion = false;
    int inventory_index;

    cout << "Welcome to the Item Shop!!" << endl;

    // menu loop
    while (choice1 != 3)
    {
        lineBreak();
        cout << "1. Buy Weapon" << endl;
        cout << "2. Buy Potion" << endl;
        cout << "3. Leave Shop" << endl;
        lineBreak();

        choice1 = -1;
        choice2 = -1;
        choice3 = -1;
        drop_index = -1;
        // take in choice, make sure its valid
        getline(cin, input);
        cout << endl;
        if (validateInt(input) && input != "")
        {
            choice1 = stoi(input);
        }

        switch (choice1)
        {
        case 1:
            // to buy weapon
            if (purchased_weapon == false)
            {
                while (choice2 != 4)
                {
                    lineBreak();
                    // cout items for sale andprice
                    cout << "You have " << _gold << " gold." << endl
                         << endl;
                    cout << "Weapons for sale:" << endl;
                    cout << "1. " << items_for_sale[0].name << " | " << items_for_sale[0].price << " gold" << endl;
                    cout << "2. " << items_for_sale[1].name << " | " << items_for_sale[1].price << " gold" << endl;
                    cout << "3. " << items_for_sale[2].name << " | " << items_for_sale[2].price << " gold" << endl;
                    cout << "4. Exit" << endl;

                    // chooseitem to buy
                    getline(cin, input);
                    if (validateInt(input) && input != "")
                    {
                        choice2 = stoi(input);
                    }
                    cout << endl;

                    switch (choice2)
                    {
                        ////////////////////////////////////////////////////////////////////////////////////////////////
                        // item 1
                    case 1:
                        // check you have enough gold
                        if (_gold < items_for_sale[0].price && purchased_weapon == false)
                        {
                            cout << "You do not have enough gold for this item." << endl;
                        }

                        else
                        {
                            // check inventory isn't full
                            full_inventory = true;
                            for (int i = 0; i < 3; i++)
                            {
                                if (_inventory[i].name == "")
                                {
                                    full_inventory = false;
                                }
                            }

                            if (full_inventory == true) // if full inventory, have option to drop items
                            {
                                while (input != "n")
                                {
                                    if (dropped_item == false) // if you havent dropped an item yet and choose no (so it doesnt keep displaying even after dropping)
                                    {
                                        cout << "Your inventory is full! Do you want to drop an item? (y/n)" << endl;
                                        getline(cin, input);
                                        cout << endl;
                                    }
                                    else // set input to n if inventory isnt full to keep the loop from saying it is full
                                    {
                                        input = "n";
                                    }

                                    if (input == "y")
                                    {
                                        choice3 = -1;
                                        while (choice3 != 3)
                                        {
                                            // options
                                            cout << "1. Display inventory" << endl;
                                            cout << "2. Drop Inventory" << endl;
                                            cout << "3. Exit" << endl;

                                            getline(cin, input);
                                            if (validateInt(input) && input != "")
                                            {
                                                choice3 = stoi(input);
                                            }

                                            switch (choice3)
                                            {
                                            // display inventory
                                            case 1:
                                                cout << endl;
                                                displayInventory();
                                                cout << endl;
                                                break;

                                            // drop item
                                            case 2:
                                                drop_index = -1;
                                                while (drop_index < 1 || drop_index > 3)
                                                {
                                                    cout << "Which inventory item do you want to drop? Enter the index (1-3)" << endl;
                                                    getline(cin, input); // take in index to drop, do validations
                                                    cout << endl;
                                                    if (validateInt(input) && input != "")
                                                    {
                                                        drop_index = stoi(input);

                                                        if (drop_index >= 1 && drop_index <= 3)
                                                        {
                                                            dropInventory(drop_index - 1);
                                                            cout << "Successfully dropped item from index " << drop_index << endl;
                                                            dropped_item = true;
                                                        }

                                                        else
                                                        {
                                                            cout << endl
                                                                 << "Enter valid input" << endl
                                                                 << endl; // if invalid for drop
                                                        }
                                                    }

                                                    else
                                                    {
                                                        cout << "Enter valid input" << endl; // if invalid for full menu option
                                                        lineBreak();
                                                    }
                                                }

                                                break;

                                            case 3:
                                                cout << endl; // exit
                                                break;

                                            default:
                                                cout << "Enter a valid choice" << endl;
                                            }
                                        }
                                    }

                                    else if (input == "n")
                                    {
                                        lineBreak();
                                    }

                                    else
                                    {
                                        cout << "Enter a valid choice" << endl;
                                    }
                                }
                                full_inventory = true;
                                for (int i = 0; i < 3; i++)
                                {
                                    if (_inventory[i].name == "")
                                    {
                                        full_inventory = false; // if a blank name then inventory isnt full
                                    }
                                }
                            }

                            if (full_inventory == false && _gold >= items_for_sale[0].price) // if not full and can afford
                            {
                                setGold(_gold - items_for_sale[0].price); // update gold amount
                                for (int i = 0; i < 3; i++)
                                {
                                    if (_inventory[i].name == "")
                                    {
                                        inventory_index = i;
                                        setInventory(items_for_sale[0], inventory_index); // set purchased item to first empty index
                                        break;
                                    }
                                }

                                cout << "Congratulations! " << items_for_sale[0].name << " was added to your inventory at index " << inventory_index + 1 << endl;
                                cout << "You now have " << _gold << " gold" << endl;
                                lineBreak();

                                choice2 = 4;
                                purchased_weapon = true;
                            }
                        }

                        break;

                        ////////////////////////////////////////////////////////////////////////////////////////////////
                        // item 2
                        // same notes as item 1
                    case 2:
                        if (_gold < items_for_sale[1].price && purchased_weapon == false)
                        {
                            cout << "You do not have enough gold for this item." << endl;
                        }

                        else
                        {
                            full_inventory = true;
                            for (int i = 0; i < 3; i++)
                            {
                                if (_inventory[i].name == "")
                                {
                                    full_inventory = false;
                                }
                            }

                            if (full_inventory == true)
                            {
                                while (input != "n")
                                {
                                    if (dropped_item == false)
                                    {
                                        cout << "Your inventory is full! Do you want to drop an item? (y/n)" << endl;
                                        getline(cin, input);
                                        cout << endl;
                                    }
                                    else
                                    {
                                        input = "n";
                                    }

                                    if (input == "y")
                                    {
                                        choice3 = -1;
                                        while (choice3 != 3)
                                        {
                                            cout << "1. Display inventory" << endl;
                                            cout << "2. Drop Inventory" << endl;
                                            cout << "3. Exit" << endl;

                                            getline(cin, input);
                                            if (validateInt(input) && input != "")
                                            {
                                                choice3 = stoi(input);
                                            }

                                            switch (choice3)
                                            {
                                            case 1:
                                                cout << endl;
                                                displayInventory();
                                                cout << endl;
                                                break;

                                            case 2:
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
                                                            dropInventory(drop_index - 1);
                                                            cout << "Successfully dropped item from index " << drop_index << endl;
                                                            dropped_item = true;
                                                        }

                                                        else
                                                        {
                                                            cout << endl
                                                                 << "Enter valid input" << endl
                                                                 << endl;
                                                        }
                                                    }

                                                    else
                                                    {
                                                        cout << "Enter valid input" << endl;
                                                        lineBreak();
                                                    }
                                                }

                                                break;

                                            case 3:
                                                cout << endl;
                                                break;

                                            default:
                                                cout << "Enter a valid choice" << endl;
                                            }
                                        }
                                    }

                                    else if (input == "n")
                                    {
                                        lineBreak();
                                    }

                                    else
                                    {
                                        cout << "Enter a valid choice" << endl;
                                    }
                                }
                                full_inventory = true;
                                for (int i = 0; i < 3; i++)
                                {
                                    if (_inventory[i].name == "")
                                    {
                                        full_inventory = false;
                                    }
                                }
                            }

                            if (full_inventory == false && _gold >= items_for_sale[1].price)
                            {
                                setGold(_gold - items_for_sale[1].price);
                                for (int i = 0; i < 3; i++)
                                {
                                    if (_inventory[i].name == "")
                                    {
                                        inventory_index = i;
                                        setInventory(items_for_sale[1], inventory_index);
                                        break;
                                    }
                                }

                                cout << "Congratulations! " << items_for_sale[1].name << " was added to your inventory at index " << inventory_index + 1 << endl;
                                cout << "You now have " << _gold << " gold" << endl;
                                lineBreak();

                                choice2 = 4;
                                purchased_weapon = true;
                            }
                        }

                        break;

                        ////////////////////////////////////////////////////////////////////////////////////////////////
                        // item 3
                        // same notes as item 1
                    case 3:
                        if (_gold < items_for_sale[2].price && purchased_weapon == false)
                        {
                            cout << "You do not have enough gold for this item." << endl;
                        }

                        else
                        {
                            full_inventory = true;
                            for (int i = 0; i < 3; i++)
                            {
                                if (_inventory[i].name == "")
                                {
                                    full_inventory = false;
                                }
                            }

                            if (full_inventory == true)
                            {
                                while (input != "n")
                                {
                                    if (dropped_item == false)
                                    {
                                        cout << "Your inventory is full! Do you want to drop an item? (y/n)" << endl;
                                        getline(cin, input);
                                        cout << endl;
                                    }
                                    else
                                    {
                                        input = "n";
                                    }

                                    if (input == "y")
                                    {
                                        choice3 = -1;
                                        while (choice3 != 3)
                                        {
                                            cout << "1. Display inventory" << endl;
                                            cout << "2. Drop Inventory" << endl;
                                            cout << "3. Exit" << endl;

                                            getline(cin, input);
                                            if (validateInt(input) && input != "")
                                            {
                                                choice3 = stoi(input);
                                            }

                                            switch (choice3)
                                            {
                                            case 1:
                                                cout << endl;
                                                displayInventory();
                                                cout << endl;
                                                break;

                                            case 2:
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
                                                            dropInventory(drop_index - 1);
                                                            cout << "Successfully dropped item from index " << drop_index << endl;
                                                            dropped_item = true;
                                                        }

                                                        else
                                                        {
                                                            cout << endl
                                                                 << "Enter valid input" << endl
                                                                 << endl;
                                                        }
                                                    }

                                                    else
                                                    {
                                                        cout << "Enter valid input" << endl;
                                                        lineBreak();
                                                    }
                                                }

                                                break;

                                            case 3:
                                                cout << endl;
                                                break;

                                            default:
                                                cout << "Enter a valid choice" << endl;
                                            }
                                        }
                                    }

                                    else if (input == "n")
                                    {
                                        lineBreak();
                                    }

                                    else
                                    {
                                        cout << "Enter a valid choice" << endl;
                                    }
                                }
                                full_inventory = true;
                                for (int i = 0; i < 3; i++)
                                {
                                    if (_inventory[i].name == "")
                                    {
                                        full_inventory = false;
                                    }
                                }
                            }

                            if (full_inventory == false && _gold >= items_for_sale[2].price)
                            {
                                setGold(_gold - items_for_sale[2].price);
                                for (int i = 0; i < 3; i++)
                                {
                                    if (_inventory[i].name == "")
                                    {
                                        inventory_index = i;
                                        setInventory(items_for_sale[2], inventory_index);
                                        break;
                                    }
                                }

                                cout << "Congratulations! " << items_for_sale[2].name << " was added to your inventory at index " << inventory_index + 1 << endl;
                                cout << "You now have " << _gold << " gold" << endl;
                                lineBreak();

                                choice2 = 4;
                                purchased_weapon = true;
                            }
                        }

                        break;

                    case 4:
                        break;

                    default:
                        cout << "Enter a valid choice" << endl;
                    }
                }
            }

            else
            {
                cout << endl
                     << "Only 1 weapon can be purchased per visit!" << endl;
            }

            break;

        // to buy potion
        case 2:
            // to buy potion
            if (purchased_potion == false)
            {
                while (choice2 != 4)
                {

                    lineBreak();
                    // cout items for sale andprice
                    cout << "You have " << _gold << " gold." << endl
                         << endl;
                    cout << "Potions for sale:" << endl;
                    cout << "1. " << potions_for_sale[0].name << " | " << potions_for_sale[0].price << " gold" << endl;
                    cout << "2. " << potions_for_sale[1].name << " | " << potions_for_sale[1].price << " gold" << endl;
                    cout << "3. " << potions_for_sale[2].name << " | " << potions_for_sale[2].price << " gold" << endl;
                    cout << "4. Exit" << endl;

                    // choose potion to buy
                    getline(cin, input);
                    if (validateInt(input) && input != "")
                    {
                        choice2 = stoi(input);
                    }
                    cout << endl;

                    switch (choice2)
                    {
                        ////////////////////////////////////////////////////////////////////////////////////////////////
                        // potion 1
                    case 1:
                        // check you have enough gold
                        if (_gold < potions_for_sale[0].price && purchased_potion == false)
                        {
                            cout << "You do not have enough gold for this potion." << endl;
                        }

                        else
                        {
                            if (addPotion(potions_for_sale[0]))
                            {
                                cout << potions_for_sale[0].name << " successfully added to the Potion Inventory" << endl;
                                setGold(_gold - potions_for_sale[0].price);
                                cout << "You now have " << _gold << " gold" << endl;
                                lineBreak();
                                purchased_potion = true;
                                choice2 = 4;
                            }
                            else
                            {
                                input = "";
                                while (input != "n")
                                {
                                    if (dropped_potion == false) // if you havent dropped a potion yet and choose no (so it doesnt keep displaying even after dropping)
                                    {
                                        cout << "Your Potion Inventory is full! Do you want to drop a potion? (y/n)" << endl;
                                        getline(cin, input);
                                        cout << endl;
                                    }
                                    else // set input to n if inventory isnt full to keep the loop from saying it is full
                                    {
                                        input = "n";
                                    }

                                    if (input == "y")
                                    {
                                        choice3 = -1;
                                        while (choice3 != 3)
                                        {
                                            // options
                                            cout << "1. Display Potions" << endl;
                                            cout << "2. Drop Potion" << endl;
                                            cout << "3. Exit" << endl;

                                            getline(cin, input);
                                            cout << endl;
                                            if (validateInt(input) && input != "")
                                            {
                                                choice3 = stoi(input);
                                            }

                                            switch (choice3)
                                            {
                                            // display potions
                                            case 1:
                                                cout << endl;
                                                displayPotions();
                                                cout << endl;
                                                break;

                                            // drop potion
                                            case 2:
                                                drop_index = -1;
                                                while (drop_index < 1 || drop_index > 3)
                                                {
                                                    cout << "Which potion do you want to drop? Enter the index (1-3)" << endl;
                                                    getline(cin, input); // take in index to drop, do validations
                                                    cout << endl;
                                                    if (validateInt(input) && input != "")
                                                    {

                                                        drop_index = stoi(input);

                                                        if (drop_index >= 1 && drop_index <= 3)
                                                        {
                                                            dropPotions(drop_index - 1);
                                                            cout << "Successfully dropped potion from index " << drop_index << endl;
                                                            dropped_potion = true;
                                                        }

                                                        else
                                                        {
                                                            cout << endl
                                                                 << "Enter valid input" << endl
                                                                 << endl; // if invalid for drop
                                                        }
                                                    }

                                                    else
                                                    {
                                                        cout << "Enter valid input" << endl; // if invalid for full menu option
                                                        lineBreak();
                                                    }
                                                }

                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                    case 2:

                    if (_gold < potions_for_sale[1].price  && purchased_potion == false)
                        {
                            cout << "You do not have enough gold for this potion." << endl;
                        }

                        else
                        {
                            if (addPotion(potions_for_sale[1]))
                            {
                                cout << potions_for_sale[1].name << " successfully added to the Potion Inventory" << endl;
                                setGold(_gold - potions_for_sale[1].price);
                                cout << "You now have " << _gold << " gold" << endl;
                                lineBreak();
                                purchased_potion = true;
                                choice2 = 4;
                            }
                            else
                            {
                                input = "";
                                while (input != "n")
                                {
                                    if (dropped_potion == false) // if you havent dropped a potion yet and choose no (so it doesnt keep displaying even after dropping)
                                    {
                                        cout << "Your Potion Inventory is full! Do you want to drop a potion? (y/n)" << endl;
                                        getline(cin, input);
                                        cout << endl;
                                    }
                                    else // set input to n if inventory isnt full to keep the loop from saying it is full
                                    {
                                        input = "n";
                                    }

                                    if (input == "y")
                                    {
                                        choice3 = -1;
                                        while (choice3 != 3)
                                        {
                                            // options
                                            cout << "1. Display Potions" << endl;
                                            cout << "2. Drop Potion" << endl;
                                            cout << "3. Exit" << endl;

                                            getline(cin, input);
                                            cout << endl;
                                            if (validateInt(input) && input != "")
                                            {
                                                choice3 = stoi(input);
                                            }

                                            switch (choice3)
                                            {
                                            // display potions
                                            case 1:
                                                cout << endl;
                                                displayPotions();
                                                cout << endl;
                                                break;

                                            // drop potion
                                            case 2:
                                                drop_index = -1;
                                                while (drop_index < 1 || drop_index > 3)
                                                {
                                                    cout << "Which potion do you want to drop? Enter the index (1-3)" << endl;
                                                    getline(cin, input); // take in index to drop, do validations
                                                    cout << endl;
                                                    if (validateInt(input) && input != "")
                                                    {

                                                        drop_index = stoi(input);

                                                        if (drop_index >= 1 && drop_index <= 3)
                                                        {
                                                            dropPotions(drop_index - 1);
                                                            cout << "Successfully dropped potion from index " << drop_index << endl;
                                                            dropped_potion = true;
                                                        }

                                                        else
                                                        {
                                                            cout << endl
                                                                 << "Enter valid input" << endl
                                                                 << endl; // if invalid for drop
                                                        }
                                                    }

                                                    else
                                                    {
                                                        cout << "Enter valid input" << endl; // if invalid for full menu option
                                                        lineBreak();
                                                    }
                                                }

                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        break;

                    case 3:

                    if (_gold < potions_for_sale[2].price && purchased_potion == false)
                        {
                            cout << "You do not have enough gold for this potion." << endl;
                        }

                        else
                        {
                            if (addPotion(potions_for_sale[2]))
                            {
                                cout << potions_for_sale[2].name << " successfully added to the Potion Inventory" << endl;
                                setGold(_gold - potions_for_sale[2].price);
                                cout << "You now have " << _gold << " gold" << endl;
                                lineBreak();
                                purchased_potion = true;
                                choice2 = 4;
                            }
                            else
                            {
                                input = "";
                                while (input != "n")
                                {
                                    if (dropped_potion == false) // if you havent dropped a potion yet and choose no (so it doesnt keep displaying even after dropping)
                                    {
                                        cout << "Your Potion Inventory is full! Do you want to drop a potion? (y/n)" << endl;
                                        getline(cin, input);
                                        cout << endl;
                                    }
                                    else // set input to n if inventory isnt full to keep the loop from saying it is full
                                    {
                                        input = "n";
                                    }

                                    if (input == "y")
                                    {
                                        choice3 = -1;
                                        while (choice3 != 3)
                                        {
                                            // options
                                            cout << "1. Display Potions" << endl;
                                            cout << "2. Drop Potion" << endl;
                                            cout << "3. Exit" << endl;

                                            getline(cin, input);
                                            cout << endl;
                                            if (validateInt(input) && input != "")
                                            {
                                                choice3 = stoi(input);
                                            }

                                            switch (choice3)
                                            {
                                            // display potions
                                            case 1:
                                                cout << endl;
                                                displayPotions();
                                                cout << endl;
                                                break;

                                            // drop potion
                                            case 2:
                                                drop_index = -1;
                                                while (drop_index < 1 || drop_index > 3)
                                                {
                                                    cout << "Which potion do you want to drop? Enter the index (1-3)" << endl;
                                                    getline(cin, input); // take in index to drop, do validations
                                                    cout << endl;
                                                    if (validateInt(input) && input != "")
                                                    {

                                                        drop_index = stoi(input);

                                                        if (drop_index >= 1 && drop_index <= 3)
                                                        {
                                                            dropPotions(drop_index - 1);
                                                            cout << "Successfully dropped potion from index " << drop_index << endl;
                                                            dropped_potion = true;
                                                        }

                                                        else
                                                        {
                                                            cout << endl
                                                                 << "Enter valid input" << endl
                                                                 << endl; // if invalid for drop
                                                        }
                                                    }

                                                    else
                                                    {
                                                        cout << "Enter valid input" << endl; // if invalid for full menu option
                                                        lineBreak();
                                                    }
                                                }

                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        break;

                    case 4:
                        break;

                    default:
                        cout << "Enter a valid choice" << endl;
                    }
                }

                break;

            case 3:
                cout << "Thanks for visiting!" << endl << endl;
                break;

            default:
                cout << "Enter a valid choice" << endl
                     << endl;
            }
            else
            {
                cout << endl
                     << "Only 1 potion can be purchased per visit!" << endl;
            }
        }
    }
}



#endif