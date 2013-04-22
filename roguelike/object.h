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

    getHealth()
    setHealth()
    move()
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
        int damage;
        int defense;
        int evasion;
        bool successfulEvade = false;
        bool successfulCrit = false;
        int critical;


    public:

    int getHealth()
    {
        return health;
    }

    void setHealth(int inHealth)
    {
        health = inHealth;
    }

    int getLevel()
    {
        return level;
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
        level = 1;
        health = (level * 15) + 100;
        damage = level + 4;
        defense = level + 4;
        evasion = level + 4;
        critical = level + 4;
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

    void takeDamage(int inPlayerDamage, bool inCritical)
    {
        if (inCritical == true)
        {
            printw("Critical Hit!");
            health = health - (((inPlayerDamage * 20) - (defense * 10)) * 2);
        }
        else
        {
            health = health - ((inPlayerDamage * 20) - (defense * 10));
        }
    }

    void move(Floor*& floor/*, Player player1*/)
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
        if (floor -> tileArray[destX][destY].hasFloor() == 1)
        {
            floor -> tileArray[currentX][currentY].setEnemy(0);
            floor -> tileArray[destX][destY].setEnemy(1);
            currentX = destX;
            currentY = destY;

        }
        //check to see if it's proceeding with the move
        //assert(false);

        //if enemy tries to move onto the player, damage the player
        /*else if (floor -> tileArray[destX][destY].hasPlayer() == 1)
        {
            player1.takeDamage(10);
        }
*/

    }

};


/************************************************
Player class

    Player()

*************************************************/
class Player : public Character
{
public:
    // Create a player with default attributes.
    Player()
    {
        level = 1;
        health = 100;
        health_cap = 100;
        damage = 5;
        defense = 5;
        evasion = 5;
        critical = 5;
        Experience = 0;
        //player reaches lvl 2 with 100 experience
        Experience_Cap = 100;

    }
    void gainExperience(int inEnemyLevel)
    {
        Experience = (inEnemyLevel * 10) + Experience;
        if (Experience >= Experience_Cap)
        {
            levelUp();
        }
    }
    void levelUp()
    {
        printw("LEVEL UP!! \n");
        //randomchance is variable for randomization
        int randomChance = (rand() % 100);
        //chance to increase health cap
        if (randomChance > 29)
        {
            health_cap = (health_cap/5) + health_cap;
            printw("Max Health Increased! \n");
        }
        //give full health
        health = health_cap;
        //chance to increase damage
        randomChance = (rand() % 100);
        if (randomChance > 29)
        {
            damage++;
            printw("Damage Increased!\n");
        }
        //chance to increase defense
        randomChance = (rand() % 100);
        if (randomChance > 29)
        {
            defense++;
            printw("Defense Increased! \n");
        }
        //chance to increase evasion
        randomChance = (rand() % 100);
        if (randomChance > 79)
        {
            evasion++;
            printw("Evasion Increased! \n");
        }
        randomChance = (rand() % 100);
        //chance to increase critical
        if (randomChance > 79)
        {
            critical++;
            printw("Critical Increased! \n");
        }
        Experience_Cap = Experience_Cap * 1.2;
        Experience = 0;
    }

    //method to determine if player will get a critical hit
    bool CritHit()
    {
        int randomChance = (rand() % 100);
        if (randomChance < critical)
        {
            successfulCrit = true;
            return successfulCrit;
        }
        else
        {
            successfulCrit = false;
            return successfulCrit;
        }
    }
    //method to determine if player will evade an enemy attack
    bool evade()
    {
        int randomChance = (rand() % 100);
        if (randomChance < evasion)
        {
            successfulEvade = true;
            return successfulEvade;
        }
        else
        {
            successfulEvade = false;
            return successfulEvade;
        }
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

    void move(char input, Floor*& floor, Enemy enemyArray[50])
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

        //if you move into a tile with an enemy
        if (floor -> tileArray[destX][destY].hasEnemy() == 1)
        {
            for (int q = 1; q < 51; q++)
            {
            //enemy damages player
                if ((enemyArray[q].getCurrentX() == destX) &&
                    (enemyArray[q].getCurrentY() == destY))
                {
                    takeDamage(enemyArray[q].getDamage());
                }
            }

        }

        else if (floor -> tileArray[destX][destY].hasFloor() == 1)
        {
            floor -> tileArray[currentX][currentY].setPlayer(0);
            floor -> tileArray[destX][destY].setPlayer(1);
            currentX = destX;
            currentY = destY;
        }
        else
        {
            printw("%s", "You walked into a wall, dumbass! \n");
        }
    }


    void attack(Floor*& floor, Enemy enemyArray[50])
    {
        //assert(false); //test to see if game header is handling the attack input
        int randomChance = (rand() % 100);
        int atkUpX = currentX - 1;
        int atkUpY = currentY - 1;
        int atkLeftX = currentX;
        int atkLeftY = currentY - 1;
        int atkRightX = currentX;
        int atkRightY = currentY + 1;
        int atkDownX = currentX + 1;
        int atkDownY = currentY + 1;

        //if there is an enemy above the player
        if (floor -> tileArray[atkUpX][atkUpY].hasEnemy() == 1)
        {
            //take health from enemy above player
            for (int q = 1; q < 51; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkUpX) &&
                   (enemyArray[q].getCurrentY() == atkUpY))
                {
                    enemyArray[q].takeDamage(damage, CritHit());
                    printw("You did damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkUpX][atkUpY].setEnemy(0);
                    }
                    else
                    {
                        if (successfulEvade == false)
                        {
                            takeDamage(enemyArray[q].getDamage());
                            printw("The enemy attacked you back! \n");
                        }
                        else
                        {
                            printw("You evaded the enemy counter!");
                        }
                    }
                }
            }
        }
        // else if there is an enemy to the left of the player
        else if (floor -> tileArray[atkLeftX][atkLeftY].hasEnemy() == 1)
        {
            //take health from enemy to the left of player
            for (int q = 1; q < 51; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkLeftX) &&
                   (enemyArray[q].getCurrentY() == atkLeftY))
                {
                    enemyArray[q].takeDamage(damage, CritHit());
                    printw("You did damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkLeftX][atkLeftY].setEnemy(0);
                    }
                    else
                    {
                        if (successfulEvade == false)
                        {
                            takeDamage(enemyArray[q].getDamage());
                            printw("The enemy attacked you back! \n");
                        }
                        else
                        {
                            printw("You evaded the enemy counter!");
                        }
                    }
                }
            }
        }
        // else if there is an enemy to the right of the player
        else if (floor -> tileArray[atkRightX][atkRightY].hasEnemy() == 1)
        {
            //take health from enemy to the right of the player
            for (int q = 1; q < 51; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkRightX) &&
                   (enemyArray[q].getCurrentY() == atkRightY))
                {
                    enemyArray[q].takeDamage(damage, CritHit());
                    printw("You did damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkRightX][atkRightY].setEnemy(0);
                    }
                    else
                    {
                        if (successfulEvade == false)
                        {
                            takeDamage(enemyArray[q].getDamage());
                            printw("The enemy attacked you back! \n");
                        }
                        else
                        {
                            printw("You evaded the enemy counter!\n");
                        }
                    }
                }
            }
        }
        // else if there is an enemy under the player
        else if (floor -> tileArray[atkDownX][atkDownY].hasEnemy() == 1)
        {
            //take health from enemy under player
            for (int q = 1; q < 51; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkDownX) &&
                   (enemyArray[q].getCurrentY() == atkDownY))
                {
                    enemyArray[q].takeDamage(damage, CritHit());
                    printw("You did damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkDownX][atkDownY].setEnemy(0);
                    }
                    else
                    {
                        if (successfulEvade == false)
                        {
                            takeDamage(enemyArray[q].getDamage());
                            printw("The enemy attacked you back!");
                        }
                        else
                        {
                            printw("You evaded the enemy counter!");
                        }
                    }
                }
            }
        }
    }

    void takeDamage(int inEnemyDamage)
    {
        char bell = 7;
        health = health - ((inEnemyDamage * 12) - (defense * 10));
        cout<<bell;

    }
};


#endif
