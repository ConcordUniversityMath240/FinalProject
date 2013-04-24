/************************************************
object.h    - Entity related classes header file.
            - Game Object (base class)
            - Character
            - Item

Author: MATH 240 Team

Purpose: These are the base classes for the more
         advanced Player and Enemy classes.
*************************************************/

#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;

/************************************************
Object class

Member functions:
    getCurrentX()      Returns the object's X coordinate.
    getCurrentY()      Returns the object's Y coordinate.
    setCurrentX()      Sets the object's X coordinate.
    setCurrentY()      Sets the object's Y coordinate.
*************************************************/
class Object
{
protected:
    int currentX;
    int currentY;

public:
    int getCurrentX()
    {
        return currentX;
    }

    int getCurrentY()
    {
        return currentY;
    }

    void setCurrentX(int input)
    {
        currentX = input;
    }

    void setCurrentY(int input)
    {
       currentY = input;
    }
};

/************************************************
Character class

    getLevel()              Returns the character's level.
    getHealthCap()          Returns the character's maximum health.
    getHealth()             Returns the character's current health.
    getExperience()         Returns the character's current XP.
    getExperience_Cap()     Returns the amount of XP needed to level
    getDamage()             Returns the character's damage attribute.
    getDefense()            Returns the character's defense attribute.
    getEvasion()            Returns the character's evasion attribute.
    getCritical()           Returns the character's critical attribute.
    setHealth()             Sets the player's health
    setLevel()              Sets the player's level.
*************************************************/
class Character : public Object
{
    protected:
        int health;
        //max amount of health a player can hold
        int health_cap;
        int level;
        int Experience;
        int Experience_Cap;
        int XPgained;
        int damage;
        int defense;
        int evasion;
        bool successfulEvade = false;
        int critical;
        bool successfulCrit = false;
        int damageTkn; //Amount of damage dealt


    public:
    int getLevel()
    {
        return level;
    }
    int getHealthCap()
    {
        return health_cap;
    }
    int getHealth()
    {
        return health;
    }
    int getExperience()
    {
        return Experience;
    }
    int getExperience_Cap()
    {
        return Experience_Cap;
    }
    int getDamage()
    {
        return damage;
    }
    int getDefense()
    {
        return defense;
    }
    int getEvasion()
    {
        return evasion;
    }
    int getCritical()
    {
        return critical;
    }
    int setHealth(int input)
    {
        health = input;
    }

    void setLevel(int inLevel)
    {
        level = inLevel;
    }
};

/************************************************
Item class

*************************************************/
class Item : public Object
{
public:

};

#endif
