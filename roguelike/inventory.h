/************************************************
inventory.h - Inventory related classes header file.
            - Item
            - Inventory

Author: MATH 240 Team

Purpose: These classes create items and control the player's inventory.
*************************************************/

#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <vector>
using namespace std;

/************************************************
Item class
    Item()                      Create a default Item with 0 bonuses.
    getName                     Return the Item's name.
    getItemType                 Return the Item's type (Armor, weapon, etc)
    getHealthBonus()            Return the health bonus the item provides.
    getMagicAmount_CapBonus()   Return the magic bonus the item provides.
    getDamageBonus()            Return the damage bonus the item provides.
    getMagicDamageBonus()       Return the magic damage bonus the item provides.
    getDefenseBonus()           Return the defense bonus the item provides.
    getMagicDefenseBonus()      Return the magic defense bonus the item provides.
    getEvasionBonus()           Return the evasion bonus the item provides.
    getCriticalBonus()          Return the critical hit bonus the item provides.
    setCurrentFloorLevel()      Return the floor level the item is on.
    setName()                   Set the item's name.
    randomize()                 Randomly assign the Item's bonus stats depending on
                                floor level it is found on.
*************************************************/
class Item : public Object
{
    private:
        string name;
        int currentFloorLevel;
        int itemType;
        int healthBonus;
        int magicAmount_CapBonus;
        int damageBonus;
        int magicDamageBonus;
        int defenseBonus;
        int magicDefenseBonus;
        int evasionBonus;
        int criticalBonus;

    public:
        Item()
        {
            name = "";
            itemType = 0;
            healthBonus = 0;
            magicAmount_CapBonus = 0;
            damageBonus = 0;
            magicDamageBonus = 0;
            defenseBonus = 0;
            magicDefenseBonus = 0;
            evasionBonus = 0;
            criticalBonus = 0;
        }
        string getName()
        {
            return name;
        }
        int getItemType()
        {
           return itemType;
        }
        int getHealthBonus()
        {
            return healthBonus;
        }
        int getMagicAmount_CapBonus()
        {
            return magicAmount_CapBonus;
        }
        int getDamageBonus()
        {
            return damageBonus;
        }
        int getMagicDamageBonus()
        {
            return defenseBonus;
        }
        int getDefenseBonus()
        {
            return defenseBonus;
        }
        int getMagicDefenseBonus()
        {
            return magicDefenseBonus;
        }
        int getEvasionBonus()
        {
            return evasionBonus;
        }
        int getCriticalBonus()
        {
            return criticalBonus;
        }
        void setCurrentFloorLevel(int input)
        {
            currentFloorLevel = input;
        }
        void setName(string input)
        {
            name = input;
        }
        void randomize()
        {
            itemType = rand() % 2;

            // Armor
            if (itemType == 0)
            {
                name = "Shield";
                healthBonus = rand() % 10 + currentFloorLevel;
                defenseBonus = rand() % 1 + currentFloorLevel;
                magicDefenseBonus = rand() % 5 + currentFloorLevel;
                evasionBonus = rand() % 1 + currentFloorLevel;
            }

            // Weapon
            else if (itemType == 1)
            {
                name = "Sword";
                damageBonus = rand() % 5 + currentFloorLevel;
                magicDamageBonus = rand() % 5 + currentFloorLevel;
                criticalBonus = rand() % 1 + currentFloorLevel;
            }

        }
};

/***********************************************
Inventory class
    print()         Displays inventory and allows player to equip items.
***********************************************/
class Inventory
{
    public:
        vector <Item> storage;
        Item nullItem;

        // Displays inventory and allows player to equip items.
        int print()
        {
            int counter = 0;
            int input;

            if (storage.size() == 0)
            {
                move(44, 0);
                printw("No items!");
                getch();
                return 99;
            }

            for (int i = 15; i < 45 ; i += 10)
                for (int j = 5; j < 77; j += 18)
                {
                    // Print the box
                    move(i-1, j-1);
                    printw("--------------------");
                    move(i, j-1);
                    printw("-                  -");
                    move(i+1, j-1);
                    printw("-                  -");
                    move(i+2, j-1);
                    printw("-                  -");
                    move(i+3, j-1);
                    printw("-                  -");
                    move(i+4, j-1);
                    printw("-                  -");
                    move(i+5, j-1);
                    printw("-                  -");
                    move(i+6, j-1);
                    printw("-                  -");
                    move(i+7, j-1);
                    printw("--------------------");

                    // Print the object's name and relevant stats.
                    move(i,j);
                    printw(" %i. ", counter);
                    const char *itemName = storage[counter].getName().c_str();
                    printw(itemName);
                    // Armor
                    if (storage[counter].getItemType() == 0)
                    {
                        move(i+1,j);
                        printw(" Defense: +%i", storage[counter].getDefenseBonus());
                        move(i+2,j);
                        printw(" Health: +%i", storage[counter].getHealthBonus());
                        move(i+3,j);
                        printw(" M.Defense: +%i", storage[counter].getMagicDefenseBonus());
                        move(i+4,j);
                        printw(" Evasion: +%i", storage[counter].getEvasionBonus());
                    }

                    // Weapon
                    else if (storage[counter].getItemType() == 1)
                    {
                        move(i+1,j);
                        printw(" Damage: +%i", storage[counter].getDamageBonus());
                        move(i+2,j);
                        printw(" Magic Damage: +%i", storage[counter].getMagicDamageBonus());
                        move(i+3,j);
                        printw(" Critical: +%i", storage[counter].getCriticalBonus());
                    }
                    counter++;


                    // Equip functionality.
                    if (counter >= storage.size())
                    {
                        move(44, 0);
                        printw("Press 'E' to equip an item or any other key to exit.");
                        input = getch();

                        // options to equip go here.
                        if(input == 'e' || input == 'E')
                        {
                           move(46, 0);
                           printw("Enter the number of the item to equip:");
                           input = getch() - '0';
                           return input;
                        }
                        // If no item is to be equipped, return dummy value.
                        return 99;
                    }
                }

            getch();
        }
};


#endif
