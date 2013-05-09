#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;

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
        magicAmount = 80;
        magicAmount_Cap = 80;
        health_cap = 100;
        damage = 5;
        magicPower = 5;
        arrows = 50;
        defense = 5;
        magicDefense = 5;
        evasion = 5;
        critical = 5;
        Experience = 0;
        //player reaches lvl 2 with 100 experience
        Experience_Cap = 100;
    }
    void gainExperience(int inEnemyLevel)
    {
        XPgained = inEnemyLevel * 10;
        Experience = Experience + XPgained;
        if (Experience >= Experience_Cap)
        {
            levelUp();
        }
    }
    int getXPgained()
    {
        return XPgained;
    }
    void levelUp()
    {
        //printw("LEVEL UP!! \n");
        //randomchance is variable for randomization
        int randomChance = (rand() % 100);
        //chance to increase health cap
        if (randomChance > 29)
        {
            health_cap = (health_cap/5) + health_cap;
            //printw("Max Health Increased! \n");
        }
        //give full health
        health = health_cap;

        //chance to increase magic amount cap
        randomChance = (rand() % 100);
        if (randomChance > 29)
        {
            magicAmount_Cap = (magicAmount_Cap/5) + magicAmount_Cap;
            //printw("Max MP increased! \n);
        }
        //give full MP
        magicAmount = magicAmount_Cap;

        //chance to increase damage
        randomChance = (rand() % 100);
        if (randomChance > 29)
        {
            damage++;
            //printw("Damage Increased!\n");
        }
        //chance to increase magic damage
        randomChance = (rand() % 100);
        if (randomChance > 29)
        {
            magicPower++;
            //printw("Magic Damage Increased!\n");
        }
        //chance to increase defense
        randomChance = (rand() % 100);
        if (randomChance > 29)
        {
            defense++;
            //printw("Defense Increased! \n");
        }
        //chance to increase magic defense
        randomChance = (rand() % 100);
        if (randomChance > 49)
        {
            magicDefense++;
            //printw("Magic Defense Increased! \n");
        }
        //chance to increase evasion
        randomChance = (rand() % 100);
        if (randomChance > 79)
        {
            evasion++;
            //printw("Evasion Increased! \n");
        }
        randomChance = (rand() % 100);
        //chance to increase critical
        if (randomChance > 79)
        {
            critical++;
            //printw("Critical Increased! \n");
        }
        Experience_Cap = Experience_Cap * 1.2;
        Experience = 0;
        level++;
        if (level == 3)
        {
            printw("You can now use Directional magic attack! \n");
        }
        if (level == 4)
        {
            printw("You can now use Heal magic! \n");
        }
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
            //printw("%s\n\n\n", "You moved down a floor.");
        }
        else if (currentFloor -> tileArray[currentX][currentY].hasUpStairs() == 1)
        {
            currentFloor = currentFloor -> prev;
            //printw("%s\n\n\n", "You moved up a floor.");
        }
        //else
          //printw("%s\n\n\n", "You are not currently on any stairs...");
    }
    void move(char input, Floor*& floor, Enemy enemyArray[50])
    {
        printw("\n\n\n");
        // Destination X,Y
        int destX = currentX;
        int destY = currentY;

        // Up
        if (input == 3)
            destX = currentX-1;

        // Left
        else if (input == 4)
            destY = currentY-1;

        // Right
        else if (input == 5)
            destY = currentY+1;

        // Down
        else if (input == 2)
            destX = currentX+1;

        //if you move into a tile with an enemy
        if (floor -> tileArray[destX][destY].hasEnemy() == 1)
        {
            for (int q = 0; q < 50; q++)
            {
            //enemy damages player
                if ((enemyArray[q].getCurrentX() == destX) &&
                    (enemyArray[q].getCurrentY() == destY))
                {
                    takeMeleeDamage(enemyArray[q].getDamage(), evade());
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
            //printw("%s", "You walked into a wall, dumbass! \n");
        }
    }
    void healMagic()
    {
        if (health == health_cap)
        {
            printw("You already have full HP!");
        }
        else if (magicAmount >= 7)
        {
            magicAmount = magicAmount - 7;
            health = health + 20;
            if (health > health_cap)
            {
                health = health_cap;
            }
        }
        else
        {
            printw("You don't have enough MP!");
        }
    }
    void takeMeleeDamage(int inEnemyDamage, bool inEvade)
    {
        if (inEvade == true)
        {
            printw("You dodged the enemy attack!");
        }
        else
        {
            damageTkn = ((inEnemyDamage * 11) - (defense * 10));
            if (damageTkn < 0)
            {
                damageTkn = 0;
            }
            health = health - damageTkn;
            char bell = 7;
            cout<<bell; //game beeps when you take damage!
        }
    }
    int getDamageTkn()
    {
        return damageTkn;
    }
    void setArrowAmount(int inAmount)
    {
        arrows = inAmount;
    }
    int getArrowAmount()
    {
        return arrows;
    }
};


#endif
