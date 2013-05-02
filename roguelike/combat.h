/********************************************
combat.h - combat actions header file

Author: Andy
*********************************************/
using namespace std;

#ifndef COMBAT_H
#define COMBAT_H
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Combat
{
private:
public:
    void playerMeleeAttack(Floor*& floor, Player& player1, Enemy enemyArray[50])
    {
        //assert(false); //test to see if game header is handling the attack input
        char buffer[50];
        //int randomChance = (rand() % 100);
        int atkUpX = player1.getCurrentX() - 1;
        int atkUpY = player1.getCurrentY();
        int atkLeftX = player1.getCurrentX();
        int atkLeftY = player1.getCurrentY() - 1;
        int atkRightX = player1.getCurrentX();
        int atkRightY = player1.getCurrentY() + 1;
        int atkDownX = player1.getCurrentX() + 1;
        int atkDownY = player1.getCurrentY();
        //if there is an enemy above the player
        if (floor -> tileArray[atkUpX][atkUpY].hasEnemy() == 1)
        {
            //take health from enemy above player
            for (int q = 0; q < 50; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkUpX) &&
                   (enemyArray[q].getCurrentY() == atkUpY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());

                    sprintf(buffer, "%i", enemyArray[q].getDamageTkn());
                    //printw("You did ");
                    //printw(buffer);
                    //printw(" damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        //printw("You killed the enemy! \n");
                        player1.gainExperience(enemyArray[q].getLevel());
                        sprintf(buffer, "%i", player1.getXPgained());
                        //printw("You gained ");
                        //printw(buffer);
                        //printw("XP! \n");
                        floor -> tileArray[atkUpX][atkUpY].setEnemy(0);
                    }
                    else
                    {
                        if (player1.evade() == false)
                        {
                            player1.takeMeleeDamage(enemyArray[q].getDamage());
                            sprintf(buffer, "%i", player1.getDamageTkn());
                            //printw("The enemy attacked you back for ");
                            //printw(buffer);
                            //printw(" damage! \n");
                        }
                        else
                        {
                            //printw("You evaded the enemy counter!");
                        }
                    }
                }
            }
        }
        // else if there is an enemy to the left of the player
        else if (floor -> tileArray[atkLeftX][atkLeftY].hasEnemy() == 1)
        {
            //take health from enemy to the left of player
            for (int q = 0; q < 50; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkLeftX) &&
                   (enemyArray[q].getCurrentY() == atkLeftY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    char buffer[50];
                    sprintf(buffer, "%i", enemyArray[q].getDamageTkn());
                    //printw("You did ");
                    //printw(buffer);
                    //printw(" damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        //printw("You killed the enemy! \n");
                        player1.gainExperience(enemyArray[q].getLevel());
                        sprintf(buffer, "%i", player1.getXPgained());
                        //printw("You gained ");
                       // printw(buffer);
                        //printw("XP! \n");
                        floor -> tileArray[atkLeftX][atkLeftY].setEnemy(0);
                    }
                    else
                    {
                        if (player1.evade() == false)
                        {
                            player1.takeMeleeDamage(enemyArray[q].getDamage());
                            sprintf(buffer, "%i", player1.getDamageTkn());
                            //printw("The enemy attacked you back for ");
                            //printw(buffer);
                            //printw(" damage! \n");
                        }
                        else
                        {
                            //printw("You evaded the enemy counter!");
                        }
                    }
                }
            }
        }
        // else if there is an enemy to the right of the player
        else if (floor -> tileArray[atkRightX][atkRightY].hasEnemy() == 1)
        {
            //take health from enemy to the right of the player
            for (int q = 0; q < 50; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkRightX) &&
                   (enemyArray[q].getCurrentY() == atkRightY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    char buffer[50];
                    sprintf(buffer, "%i", enemyArray[q].getDamageTkn());
                    //printw("You did ");
                    //printw(buffer);
                    //printw(" damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        //printw("You killed the enemy! \n");
                        player1.gainExperience(enemyArray[q].getLevel());
                        sprintf(buffer, "%i", player1.getXPgained());
                        //printw("You gained ");
                        //printw(buffer);
                        //printw("XP! \n");
                        floor -> tileArray[atkRightX][atkRightY].setEnemy(0);
                    }
                    else
                    {
                        if (player1.evade() == false)
                        {
                            player1.takeMeleeDamage(enemyArray[q].getDamage());
                            sprintf(buffer, "%i", player1.getDamageTkn());
                            //printw("The enemy attacked you back for ");
                            //printw(buffer);
                            //printw(" damage! \n");
                        }
                        else
                        {
                            //printw("You evaded the enemy counter!\n");
                        }
                    }
                }
            }
        }
        // else if there is an enemy under the player
        else if (floor -> tileArray[atkDownX][atkDownY].hasEnemy() == 1)
        {
            //take health from enemy under player
            for (int q = 0; q < 55; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkDownX) &&
                   (enemyArray[q].getCurrentY() == atkDownY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    char buffer[50];
                    sprintf(buffer, "%i", enemyArray[q].getDamageTkn());
                    //printw("You did ");
                    //printw(buffer);
                    //printw(" damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        //printw("You killed the enemy! \n");
                        player1.gainExperience(enemyArray[q].getLevel());
                        sprintf(buffer, "%i", player1.getXPgained());
                        //printw("You gained ");
                        //printw(buffer);
                        //printw("XP! \n");
                        floor -> tileArray[atkDownX][atkDownY].setEnemy(0);
                    }
                    else
                    {
                        if (player1.evade() == false)
                        {
                            player1.takeMeleeDamage(enemyArray[q].getDamage());
                            sprintf(buffer, "%i", player1.getDamageTkn());
                            //printw("The enemy attacked you back for ");
                           // printw(buffer);
                           // printw(" damage! \n");
                        }
                        else
                        {
                           // printw("You evaded the enemy counter!");
                        }
                    }
                }
            }
        }
    }
    void playerDirMagicAtk(Floor*& floor, Player& player1, Enemy enemyArray[50])
    {
        if (player1.getMagicAmount() >= 10)
        {
            //char buffer[50];
            //int randomChance = (rand() % 100);
            int atkUpX = player1.getCurrentX() - 1;
            int atkUpY = player1.getCurrentY();
            int atkLeftX = player1.getCurrentX();
            int atkLeftY = player1.getCurrentY() - 1;
            int atkRightX = player1.getCurrentX();
            int atkRightY = player1.getCurrentY() + 1;
            int atkDownX = player1.getCurrentX() + 1;
            int atkDownY = player1.getCurrentY();
            //if there is an enemy above the player
            for (int counter = 0; counter < 7; counter++)
            {
                if (floor -> tileArray[atkUpX][atkUpY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkUpX) &&
                        (enemyArray[q].getCurrentY() == atkUpY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(player1.getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkUpX][atkUpY].setEnemy(0);
                            }
                        }
                    }
                }
                atkUpX = atkUpX - 1;
            }
            for (int counter = 0; counter < 7; counter++)
            {
                if (floor -> tileArray[atkLeftX][atkLeftY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkLeftX) &&
                        (enemyArray[q].getCurrentY() == atkLeftY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(player1.getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkLeftX][atkLeftY].setEnemy(0);
                            }
                        }
                    }
                }
                atkLeftY = atkLeftY - 1;
            }
            for (int counter = 0; counter < 7; counter++)
            {
                if (floor -> tileArray[atkRightX][atkRightY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkRightX) &&
                        (enemyArray[q].getCurrentY() == atkRightY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(player1.getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkRightX][atkRightY].setEnemy(0);
                            }
                        }
                    }
                }
                atkRightY = atkRightY + 1;
            }
            for (int counter = 0; counter < 7; counter++)
            {
                if (floor -> tileArray[atkDownX][atkDownY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkDownX) &&
                        (enemyArray[q].getCurrentY() == atkDownY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(player1.getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkDownX][atkDownY].setEnemy(0);
                            }
                        }
                    }
                }
                atkDownX = atkDownX + 1;
            }
            player1.setMagicAmount(player1.getMagicAmount() - 10);
        }
        else
        {
            printw("You don't have enough MP!");
        }
    }
    void enemyMeleeAttack(int inDamage, Player& player1)
    {
        //test to see if it's getting inside this function
        //assert(false);
        player1.takeMeleeDamage(inDamage);
    }
};

#endif
