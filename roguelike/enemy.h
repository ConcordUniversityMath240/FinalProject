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
        /*
            AI
        */
        int sighted = 0;
        int visualField = 5;
        int direction = 0;
        int destX = currentX;
        int destY = currentY;
        for (int i = 0; i < visualField; i++) {
            // up
            if (floor -> tileArray[currentX-i][currentY].hasPlayer()) {
                sighted = 1;
                direction = 1;
            }
            // down
            if (floor -> tileArray[currentX+i][currentY].hasPlayer()) {
                sighted = 1;
                direction = 2;
            }
            // right
            if (floor -> tileArray[currentX][currentY+i].hasPlayer()) {
                sighted = 1;
                direction = 3;
           }
            // left
            if (floor -> tileArray[currentX][currentY-i].hasPlayer()) {
                sighted = 1;
                direction = 4;
            }
            // down left
            if (floor -> tileArray[currentX+i][currentY-i].hasPlayer()) {
                sighted = 1;
                direction = 5;
            }
            // up left
            if (floor -> tileArray[currentX-i][currentY-i].hasPlayer()) {
                sighted = 1;
                direction = 6;
            }
            // up right
            if (floor -> tileArray[currentX-i][currentY+i].hasPlayer()) {
                sighted = 1;
                direction = 7;
            }
            // down right
            if (floor -> tileArray[currentX+i][currentY+i].hasPlayer()) {
                sighted = 1;
                direction = 8;
            }
            /*
                Special Cases
            */
            for (int j = 1; j < visualField; j++) {
                // up left skipping vertical // horizontal
                if (floor -> tileArray[currentX-i-j][currentY-i].hasPlayer() ||
                    floor -> tileArray[currentX-i][currentY-i-j].hasPlayer()
                    ) {
                    sighted = 1;
                    if (floor -> tileArray[currentX-i][currentY].hasFloor()) {
                        direction = 1;
                    }
                    else if (floor -> tileArray[currentX][currentY-i].hasFloor()) {
                        direction = 4;
                    }
                }
                // up right skipping vertical // horizontal
                if (floor -> tileArray[currentX-i-j][currentY+i].hasPlayer() ||
                    floor -> tileArray[currentX-i][currentY+i+j].hasPlayer()
                    ) {
                    sighted = 1;
                    if (floor -> tileArray[currentX-i][currentY].hasFloor()) {
                        direction = 1;
                    }
                    else if (floor -> tileArray[currentX][currentY+i].hasFloor()) {
                        direction = 3;
                    }
                }
                // down right skipping vertical // horizontal
                if (floor -> tileArray[currentX+i+j][currentY+i].hasPlayer() ||
                    floor -> tileArray[currentX+i][currentY+i+j].hasPlayer()
                    ) {
                    sighted = 1;
                    if (floor -> tileArray[currentX+i][currentY].hasFloor()) {
                        direction = 2;
                    }
                    else if (floor -> tileArray[currentX][currentY+i].hasFloor()) {
                        direction = 3;
                    }
                }
                // down left skipping vertical // horizontal
                if (floor -> tileArray[currentX+i+j][currentY-i].hasPlayer() ||
                    floor -> tileArray[currentX+i][currentY-i-j].hasPlayer()
                    ) {
                    sighted = 1;
                    if (floor -> tileArray[currentX+i][currentY].hasFloor()) {
                        direction = 2;
                    }
                    else if (floor -> tileArray[currentX][currentY-i].hasFloor()) {
                        direction = 4;
                    }
                }
            }
        }
        // move dumb
        if (sighted == 0) {
            int randomChance = (rand() % 100);
            //check to see if it's getting this far
            //assert(false);
            // determine direction!
            // 6% chance of moving up
            if (randomChance > 93)
            {
                destX = currentX - 1;
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
            }
        }
        //move smart ;)
        else {
            switch(direction) {
            //move up
            case 1:
                destX = currentX - 1;
                break;
            //move down
            case 2:
                destX = currentX + 1;
                break;
            //move right
            case 3:
                destY = currentY + 1;
                break;
            //move left
            case 4:
                destY = currentY - 1;
                break;
            //move down left
            case 5:
                destX = currentX + 1;
                destY = currentY - 1;
                break;
            //move up left
            case 6:
                destX = currentX - 1;
                destY = currentY - 1;
                break;
            //move up right
            case 7:
                destX = currentX - 1;
                destY = currentY + 1;
                break;
            //move down right
            case 8:
                destX = currentX + 1;
                destY = currentY + 1;
                break;
            }
        }

            //check to see if it's determining direction
            //assert(false);
            //proceed with move!
            //if enemy tries to move to an empty tile, move him there
            if (floor -> tileArray[destX][destY].hasFloor() == 1 &&
                health > 0 && floor -> tileArray[destX][destY].hasPlayer() != 1
                && floor -> tileArray[destX][destY].hasEnemy() != 1
                )
            {
                floor -> tileArray[currentX][currentY].setEnemy(0);
                floor -> tileArray[destX][destY].setEnemy(1);
                currentX = destX;
                currentY = destY;
            }
            if (floor -> tileArray[destX][destY].hasPlayer() == 1) {
            }
            //check to see if it's proceeding with the move
            //assert(false);

            //if enemy tries to move onto the player, damage the player
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
