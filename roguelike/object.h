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
        int level;
        int Experience;
        int Experience_Cap;
        float Cap_Increase;
        int damage;
        int defense;
        int evasion;
        int critical;

        int Experience_Count = 20;


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
        printw("\n\n\n");
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

        if (floor -> tileArray[destX][destY].hasEnemy() == 1)
            printw("%s", "An enemy blocks your path!! \n");

        else if (floor -> tileArray[destX][destY].hasFloor() == 1)
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
        damage = 5;
        defense = 5;
        evasion = 5;
        critical = 5;
        level = 1;
        Experience = 0;
        //amount of experience from monster.
        Experience_Cap = 20;
        Cap_Increase = 1.2;

    }
    void gainExperience()
    {
        //if player kills a monster, gain exp
        if((test == 1))
        {
        //When combat is done and a monster is killed
        Experience = Experience + Experience_Count;
        //Experience_Count is the amount of exp a monster will send
        //to that variable when it dies.
        }
    }
    void levelUp()
    {
        //if experience is equal to the cap
        if(Experience == Experience_Cap)
        {
            //set exp to zero, inc the cap, adjust attributes
            Experience = 0;
            Experience_Cap = Experience_Cap * Cap_Increase;
            damage++;
            defense++;
            evasion++;
            critical++;
            level++;
        }
        //if experience is greater than the cap
        else if(Experience > Experience_Cap)
        {
            //experience set to rollover exp, cap increase, attributes adjusted
            Experience = Experience - Experience_Cap;
            Experience_Cap = Experience_Cap * Cap_Increase;
            damage++;
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

    void useStairs(Floor*& currentFloor)
    {
        if (currentFloor -> tileArray[currentX][currentY].hasDownStairs() == 1)
        {
            currentFloor = currentFloor -> next;
            printw("%s\n\n\n", "You moved down a floor.");
        }
        else if (currentFloor -> tileArray[currentX][currentY].hasUpStairs() == 1)
        {
            currentFloor = currentFloor -> prev;
            printw("%s\n\n\n", "You moved up a floor.");
        }
        else
          printw("%s\n\n\n", "You are not currently on any stairs...");
    }

    void attack(Floor*& floor)
    {
        //assert(false); //test to see if game header is handling the attack input

        printw("%s\n", "ATTACK!");
        int atkUpX = currentX - 1;
        int atkUpY = currentY - 1;
        int atkLeftX = currentX;
        int atkLeftY = currentY - 1;
        int atkRightX = currentX;
        int atkRightY = currentY + 1;
        int atkDownX = currentX + 1;
        int atkDownY = currentY + 1;

        //if there is an enemy adjacent to the player
        if ((floor -> tileArray[atkUpX][atkUpY].hasEnemy() == 1) ||
            (floor -> tileArray[atkLeftX][atkLeftY].hasEnemy() == 1) ||
            (floor -> tileArray[atkRightX][atkRightY].hasEnemy() == 1) ||
            (floor -> tileArray[atkDownX][atkDownY].hasEnemy() == 1))
        {
            //take health from the adjacent enemy
        }
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
