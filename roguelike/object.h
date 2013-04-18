/************************************************
object.h    - Entity related classes header file.
            - Object (base class)
            - Player
            - Enemy
            - Star
            - Starbase

Author: Derek Royse & Andy Pritt

Purpose: These classes store and print locational data.
*************************************************/
#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <ctime>
#include <cstdlib>
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

    getHealth()
    setHealth()
    move()
*************************************************/
class Character : public Object
{
    protected:
        int health;
        int attack;
        int defense;
        int evasion;
        int critical;
        int Experience_Count = 20;
        int level;
        int Experience;
        int Experience_Cap;
        float Cap_Increase;

    public:

    int getHealth()
    {
        return health;
    }

    int setHealth(int input)
    {
        health = input;
    }
    void move(char input, Floor*& floor)
    {
        // Destination X,Y
        int destX = currentX;
        int destY = currentY;

        // Up
        if (input == 3)
        {
            destX = currentX-1;
            destY = currentY-1;
        }
        // Left
        else if (input == 4)
            destY = currentY-1;

        // Right
        else if (input == 5)
            destY = currentY+1;

        // Down
        else if (input == 2)
        {
            destX = currentX+1;
            destY = currentY+1;
        }


        if (floor -> tileArray[destX][destY].hasFloor() == 1)
        {
            floor -> tileArray[currentX][currentY].setPlayer(0);
            floor -> tileArray[destX][destY].setPlayer(1);
            currentX = destX;
            currentY = destY;
        }
        else
            printw("%s", "You walked into a wall, dumbass! \n");
    }
};

/************************************************
Player class

    Player()

*************************************************/
class Player : public Character
{
public:
    int test = 1;
    // Create a player with default attributes.
    Player()
    {
        health = 100;
        attack = 5;
        defense = 5;
        evasion = 5;
        critical = 5;
        int level = 1;
        int Experience = 0;
        int Experience_Cap = 20;
        float Cap_Increase = 1.2;

    }
    void gainExperience()
    {
        if((test = 1))
        {
        //When combat is done and a monster is killed
        Experience = Experience + Experience_Count;
        }
    }
    void levelUp()
    {
        if(Experience == Experience_Cap)
        {
            Experience = 0;
            Experience_Cap = Experience_Cap * Cap_Increase;
            attack++;
            defense++;
            evasion++;
            critical++;
            level++;
        }
        else if(Experience > Experience_Cap)
        {
            Experience = Experience - Experience_Cap;
            Experience_Cap = Experience_Cap * Cap_Increase;
            attack++;
            defense++;
            evasion++;
            critical++;
            level++;
        }
    }
    int Return_Level()
    {
        return level;
    }
};

/************************************************
Enemy class

    Enemy()             Creates an enemy with 100 health.

*************************************************/
class Enemy: public Character
{
private:

public:

    Enemy()
    {
        health = 100;
    }
};

#endif
