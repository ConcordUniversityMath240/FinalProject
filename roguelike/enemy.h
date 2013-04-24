using namespace std;

#ifndef ENEMY_H
#define ENEMY_H
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/************************************************
Enemy class

    Enemy()             Creates an enemy with 100 health.

*************************************************/
class Enemy: public Character
{
protected:
    int currentFloorLevel;
public:

    Enemy()
    {
        level = 1;
        health = (level * 15) + 80;
        damage = level + 4;
        defense = level + 4;
        evasion = level + 4;
        critical = level + 4;

        currentFloorLevel = 0;
    }

    void setHealth(int inHealth)
    {
        health = inHealth;
    }

    int getLevel()
    {
        return level;
    }

    int getDamage()
    {
        return damage;
    }

    int getDamageTkn()
    {
        return damageTkn;
    }

    void takeDamage(int inPlayerDamage, bool inCritical)
    {
        if (inCritical == true)
        {
            printw("Critical Hit! \n");
            damageTkn = (((inPlayerDamage * 20) - (defense * 10)) * 2);
            health = health - damageTkn;
        }
        else
        {
            damageTkn = ((inPlayerDamage * 20) - (defense * 10));
            health = health - damageTkn;
        }

    }

    void move(Floor*& floor)
    {
        int randomChance = (rand() % 100);
        int destX = currentX;
        int destY = currentY;

        //check to see if it's getting this far
        //assert(false);
        // determine direction!
        // 6% chance of moving up
        if (randomChance > 93)
        {
            destX = currentX - 1;
            destY = currentY - 1;
        }
        // 6% chance of moving left
        else if (randomChance > 87 && randomChance < 94)
        {
            destY = currentY - 1;
        }
        // 6% chance of moving right
        else if (randomChance > 81 && randomChance < 88)
        {
            destY = currentY + 1;
        }
        // 6% chance of moving down
        else if (randomChance > 75 && randomChance < 82)
        {
            destX = currentX + 1;
            destY = currentY + 1;
        }

        //check to see if it's determining direction
        //assert(false);
        //proceed with move!
        //if enemy tries to move to an empty tile, move him there
        if (floor -> tileArray[destX][destY].hasFloor() == 1 &&
            health > 0)
        {
            floor -> tileArray[currentX][currentY].setEnemy(0);
            floor -> tileArray[destX][destY].setEnemy(1);
            currentX = destX;
            currentY = destY;

        }
        //check to see if it's proceeding with the move
        //assert(false);

        //if enemy tries to move onto the player, damage the player
        else if (floor -> tileArray[destX][destY].hasPlayer() == 1)
        {
            destX = currentX;
            destY = currentY;
        }
        else if (floor -> tileArray[destX][destY].hasEnemy() == 1)
        {
            destX = currentX;
            destY = currentY;
        }
    }

    int getCurrentFloorLevel()
    {
        return currentFloorLevel;
    }

    void setCurrentFloorLevel(int inLevel)
    {
        currentFloorLevel = inLevel;
    }
};

#endif
