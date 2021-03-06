/************************************************
object.h    - Entity related classes header file.
            - Game Object (base class)
            - Character (base class)

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
    getMagicAmount()        Return the Mana amount of the player.
    setMagicAmount()        Set the player's mana amount.
    getMagicPower()         Return the strength of player's magic attacks.
    getMagicDefense()       Return the defense of the player against magic attacks.
*************************************************/
class Character : public Object
{
protected:
    int health;
    //max amount of health a player can hold
    int health_cap;
    int magicAmount;
    int magicAmount_Cap;
    int level;
    int Experience;
    int Experience_Cap;
    int XPgained;
    int damage;
    int magicPower;
    int arrows; //amount of arrows in player inventory
    int defense;
    int magicDefense;
    int evasion;
    bool successfulEvade;
    int critical;
    bool successfulCrit;
    int damageTkn; //Amount of damage dealt
    int Arrow_Count;


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
    int getMagicAmount()
    {
        return magicAmount;
    }
    void setMagicAmount(int inAmount)
    {
        magicAmount = inAmount;
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
    int getMagicPower()
    {
        return magicPower;
    }
    int getDefense()
    {
        return defense;
    }
    int getMagicDefense()
    {
        return magicDefense;
    }
    int getEvasion()
    {
        return evasion;
    }
    int getCritical()
    {
        return critical;
    }
    void setHealth(int input)
    {
        health = input;
    }
    void setLevel(int inLevel)
    {
        level = inLevel;
    }
};

#endif
