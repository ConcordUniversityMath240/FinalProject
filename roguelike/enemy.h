using namespace std;

#ifndef ENEMY_H
#define ENEMY_H
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/************************************************
Enemy.h

Class for all enemy attributes and actions.

    Enemy()                                                     sets up enemy stats
    void setHealth(int inHealth)                                set health
    int getLevel()                                              gets level
    int getDamage()                                             gets damage they can do
    int getDamageTkn()                                          get damage they have taken
    void takeMeleeDamage(int inPlayerDamage, bool inCritical)   function for hurting enemy (melee)
    void takeMagicDam(int inPlayerMagDam)                       function for hurting enemy (magic)
    void takeArrowDam(int inPlayerArrowDam)                     function for hurting enemy (arrows)
    void move(Floor*& floor)                                    moving enemies
    int getCurrentFloorLevel()                                  get the current floor an enemy is on
    void setCurrentFloorLevel(int inLevel)                      set the floor level
    void setAtkStatus(bool inStatus)                            set whether they are attacking
    bool getAtkStatus()                                         get the status of attacking or not

*************************************************/
class Enemy: public Character
{
protected:
    int currentFloorLevel;
    bool isBoss;
    bool attackPlayerNow;
public:

    Enemy()
    {
        level = 1;
        health = (level * 1.2) + 95;
        magicAmount = (level * 1.2) + 95;
        damage = level + 4;
        magicPower = level + 4;
        defense = level + 4;
        magicDefense = level + 4;
        evasion = level + 4;
        critical = level + 4;

        currentFloorLevel = 0;
        isBoss = 0;
        attackPlayerNow = false;
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

    void takeMeleeDamage(int inPlayerDamage, bool inCritical)
    {
        if (inCritical == true)
        {
            printw("Critical Hit! \n");
            damageTkn = (((inPlayerDamage * 20) - (defense * 10)) * 2);
            if (damageTkn < 0)
            {
                damageTkn = ((rand() % (7 - 4 + 1)) + 4) * 2;
            }
            health = health - damageTkn;
        }
        else
        {
            damageTkn = ((inPlayerDamage * 20) - (defense * 10));
            if (damageTkn < 0)
            {
                damageTkn = (rand() % (7 - 4 + 1)) + 4;
            }
            health = health - damageTkn;
        }
    }

    void takeMagicDam(int inPlayerMagDam)
    {
        damageTkn = ((inPlayerMagDam * 20) - (magicDefense * 7));
        if (damageTkn < 0)
        {
            damageTkn = (rand() % (7 - 4 + 1)) + 4;
        }
        health = health - damageTkn;
    }

    void takeArrowDam(int inPlayerArrowDam)
    {
        damageTkn = ((inPlayerArrowDam * 15) - (defense * 8));
        if (damageTkn < 0)
        {
            damageTkn = (rand() % (7 - 4 + 1)) + 4;
        }
        health = health - damageTkn;
    }

    void move(Floor*& floor)
    {
        /*
            AI
        */
        int sighted = 0;
        int visualField = 6;
        int direction = 0;
        int destX = currentX;
        int destY = currentY;
        /*
            For each one of the 8 possible directions loop through the visual field;
            check for player; and then set the enemy in the respective direction
        */
        for (int i = 0; i < visualField; i++) {
            // up
            if (floor -> tileArray[currentX-i][currentY].hasFloor()) {
                if (floor -> tileArray[currentX-i][currentY].hasPlayer()) {
                    sighted = 1;
                    direction = 1;
                }
            }
            // down
            if (floor -> tileArray[currentX+i][currentY].hasFloor()) {
                if (floor -> tileArray[currentX+i][currentY].hasPlayer()) {
                    sighted = 1;
                    direction = 2;
                }
            }
            // right
            if (floor -> tileArray[currentX][currentY+i].hasFloor()) {
                if (floor -> tileArray[currentX][currentY+i].hasPlayer()) {
                    sighted = 1;
                    direction = 3;
                }
            }
            // left
            if (floor -> tileArray[currentX][currentY-i].hasFloor()) {
                if (floor -> tileArray[currentX][currentY-i].hasPlayer()) {
                    sighted = 1;
                    direction = 4;
                }
            }
            // down left
            if (floor -> tileArray[currentX+i][currentY-i].hasFloor()) {
                if (floor -> tileArray[currentX+i][currentY-i].hasPlayer()) {
                    sighted = 1;
                    direction = 5;
                }
            }
            // up left
            if (floor -> tileArray[currentX-i][currentY-i].hasFloor()) {
                if (floor -> tileArray[currentX-i][currentY-i].hasPlayer()) {
                    sighted = 1;
                    direction = 6;
                }
            }
            // up right
            if (floor -> tileArray[currentX-i][currentY+i].hasFloor()) {
                if (floor -> tileArray[currentX-i][currentY+i].hasPlayer()) {
                    sighted = 1;
                    direction = 7;
                }
            }
            // down right
            if (floor -> tileArray[currentX+i][currentY+i].hasFloor()) {
                if (floor -> tileArray[currentX+i][currentY+i].hasPlayer()) {
                    sighted = 1;
                    direction = 8;
                }
            }
            /*
                Special Cases
            */
            for (int j = 1; j < visualField; j++) {
                if (i+j <= visualField) {
                    // up left skipping vertical // horizontal
                    if (floor -> tileArray[currentX-i-j][currentY-i].hasFloor() ||
                        floor -> tileArray[currentX-i][currentY-i-j].hasFloor()
                        ) {
                        if (floor -> tileArray[currentX-i-j][currentY-i].hasPlayer() ||
                            floor -> tileArray[currentX-i][currentY-i-j].hasPlayer()
                            ) {
                            sighted = 1;
                            direction = 6;
                        }
                    }
                    // up right skipping vertical // horizontal
                    if (floor -> tileArray[currentX-i-j][currentY+i].hasFloor() ||
                        floor -> tileArray[currentX-i][currentY+i+j].hasFloor()
                        ) {
                        if (floor -> tileArray[currentX-i-j][currentY+i].hasPlayer() ||
                            floor -> tileArray[currentX-i][currentY+i+j].hasPlayer()
                            ) {
                            sighted = 1;
                            direction = 7;
                        }
                    }
                    // down right skipping vertical // horizontal
                    if (floor -> tileArray[currentX+i+j][currentY+i].hasFloor() ||
                        floor -> tileArray[currentX+i][currentY+i+j].hasFloor()
                        ) {
                        if (floor -> tileArray[currentX+i+j][currentY+i].hasPlayer() ||
                            floor -> tileArray[currentX+i][currentY+i+j].hasPlayer()
                            ) {
                            sighted = 1;
                            direction = 8;
                        }
                    }
                    // down left skipping vertical // horizontal
                    if (floor -> tileArray[currentX+i+j][currentY-i].hasFloor() ||
                        floor -> tileArray[currentX+i][currentY-i-j].hasFloor()
                        ) {
                        if (floor -> tileArray[currentX+i+j][currentY-i].hasPlayer() ||
                            floor -> tileArray[currentX+i][currentY-i-j].hasPlayer()
                            ) {
                            sighted = 1;
                            direction = 5;
                        }
                    }
                }
            }
        }
        // if the player has not been sighted move randomly
        if (sighted == 0) {
            // added a flag to account for the times that we don't hit any probabilities
            int moved = 0;
            int randomChance = 0;
            while (moved != 1) {
                randomChance = rand() % 100;
                //check to see if it's getting this far
                //assert(false);
                // determine direction!

                // 6% chance of moving up
                if (randomChance > 93)
                {
                    destX = currentX - 1;
                    moved = 1;
                }
                // 6% chance of moving left
                else if (randomChance > 87 && randomChance < 94)
                {
                    destY = currentY - 1;
                    moved = 1;
                }
                // 6% chance of moving right
                else if (randomChance > 81 && randomChance < 88)
                {
                    destY = currentY + 1;
                    moved = 1;
                }
                // 6% chance of moving down
                else if (randomChance > 75 && randomChance < 82)
                {
                    destX = currentX + 1;
                    moved = 1;
                }
                // 6% chance of moving down right
                else if (randomChance > 69 && randomChance < 75)
                {
                    destX = currentX + 1;
                    destY = currentY + 1;
                    moved = 1;
                }
                // 6% chance of moving down left
                else if (randomChance > 63 && randomChance < 69)
                {
                    destX = currentX + 1;
                    destY = currentY - 1;
                    moved = 1;
                }
                // 6% chance of moving up left
                else if (randomChance > 57 && randomChance < 63)
                {
                    destX = currentX - 1;
                    destY = currentY - 1;
                    moved = 1;
                }
                // 6% chance of moving up right
                else if (randomChance > 51 && randomChance < 57)
                {
                    destX = currentX - 1;
                    destY = currentY + 1;
                    moved = 1;
                }
            }
        }
        //move smart ;)
        else {
            /*
                checks original direction, and tries to go around obstacles
            */
            switch(direction) {
            //move up
            case 1:
                if (floor->tileArray[currentX-1][currentY].hasWall()) {
                    if (floor->tileArray[currentX][currentY+1].hasWall()) {
                        destY = currentY - 1;
                    }
                    else {
                        destX = currentX + 1;
                    }
                }
                else {
                    destX = currentX - 1;
                }
                break;
            //move down
            case 2:
                if (floor->tileArray[currentX+1][currentY].hasWall()) {
                    if (floor->tileArray[currentX][currentY+1].hasWall()) {
                        destY = currentY - 1;
                    }
                    else {
                        destX = currentX + 1;
                    }
                }
                else {
                    destX = currentX + 1;
                }
                break;
            //move right
            case 3:
                if (floor->tileArray[currentX][currentY+1].hasWall()) {
                    if (floor->tileArray[currentX+1][currentY].hasWall()) {
                        destX = currentX - 1;
                        destY = currentY + 1;
                    }
                    else {
                        destX = currentX + 1;
                        destY = currentY + 1;
                    }
                }
                else {
                    destY = currentY + 1;
                }
                break;
            //move left
            case 4:
                if (floor->tileArray[currentX][currentY-1].hasWall()) {
                    if (floor->tileArray[currentX+1][currentY].hasWall()) {
                        destX = currentX - 1;
                        destY = currentY - 1;
                    }
                    else {
                        destX = currentX + 1;
                        destY = currentY - 1;
                    }
                }
                else {
                    destY = currentY - 1;
                }
                break;
            //move down left
            case 5:
                if (floor->tileArray[currentX+1][currentY-1].hasWall()) {
                    if (floor->tileArray[currentX+1][currentY].hasWall()) {
                        destY = currentY-1;
                    }
                    else {
                        destX = currentX+1;
                    }
                }
                else {
                    destX = currentX + 1;
                    destY = currentY - 1;
                }
                break;
            //move up left
            case 6:
                if (floor->tileArray[currentX-1][currentY-1].hasWall()) {
                    if (floor->tileArray[currentX-1][currentY].hasWall()) {
                        destY = currentY-1;
                    }
                    else {
                        destX = currentX-1;
                    }
                }
                else {
                    destX = currentX - 1;
                    destY = currentY - 1;
                }
                break;
            //move up right
            case 7:
                if (floor->tileArray[currentX-1][currentY+1].hasWall()) {
                    if (floor->tileArray[currentX-1][currentY].hasWall()) {
                        destY = currentY+1;
                    }
                    else {
                        destX = currentX-1;
                    }
                }
                else {
                    destX = currentX - 1;
                    destY = currentY + 1;
                }
                break;
            //move down right
            case 8:
                if (floor->tileArray[currentX+1][currentY+1].hasWall()) {
                    if (floor->tileArray[currentX+1][currentY].hasWall()) {
                        destY = currentY+1;
                    }
                    else {
                        destX = currentX+1;
                    }
                }
                else {
                    destX = currentX + 1;
                    destY = currentY + 1;
                }
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
            if (floor -> tileArray[destX][destY].hasPlayer() == 1)
            {
                attackPlayerNow = true;
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

    void setAtkStatus(bool inStatus)
    {
        attackPlayerNow = inStatus;
    }

    bool getAtkStatus()
    {
        return attackPlayerNow;
    }
};

#endif
