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
        health = 100;
    }

    void setHealth(int inHealth)
    {
        health = inHealth;
    }

    void takeDamage(int inDamage)
    {
        health = health - inDamage;
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
        {
            printw("%s", "An enemy blocks your path!! \n");
            takeDamage(10); //this amount can definitely change later
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

        int randomChance = (rand() % 10);
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
                    enemyArray[q].takeDamage(50);
                    printw("You did 50 damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        floor -> tileArray[atkUpX][atkUpY].setEnemy(0);
                    }
                    else
                    {
                        if (randomChance > 5)
                        {
                            takeDamage(10);
                            printw("The enemy attacked you back for 10 damage! \n");
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
                    enemyArray[q].takeDamage(50);
                    printw("You did 50 damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        floor -> tileArray[atkLeftX][atkLeftY].setEnemy(0);
                    }
                    else
                    {
                        if (randomChance > 5)
                        {
                            takeDamage(10);
                            printw("The enemy attacked you back for 10 damage! \n");
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
                    enemyArray[q].takeDamage(50);
                    printw("You did 50 damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        floor -> tileArray[atkRightX][atkRightY].setEnemy(0);
                    }
                    else
                    {
                        if (randomChance > 5)
                        {
                            takeDamage(10);
                            printw("The enemy attacked you back for 10 damage! \n");
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
                    enemyArray[q].takeDamage(50);
                    printw("You did 50 damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        floor -> tileArray[atkDownX][atkDownY].setEnemy(0);
                    }
                    else
                    {
                        if (randomChance > 5)
                        {
                            takeDamage(10);
                            printw("The enemy attacked you back for 10 damage! \n");
                        }
                    }
                }
            }
        }
    }

    void takeDamage(int inDamage)
    {
        char bell = 7;
        health = health - inDamage;
        cout<<bell;
    }
};


#endif
