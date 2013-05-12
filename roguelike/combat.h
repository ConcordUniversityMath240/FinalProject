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
        int atkUpX = player1.getCurrentX() - 1;
        int atkUpY = player1.getCurrentY();
        int atkLeftX = player1.getCurrentX();
        int atkLeftY = player1.getCurrentY() - 1;
        int atkRightX = player1.getCurrentX();
        int atkRightY = player1.getCurrentY() + 1;
        int atkDownX = player1.getCurrentX() + 1;
        int atkDownY = player1.getCurrentY();
        //if there is an enemy above the player
        for (int q = 0; q < 50; q++)
        {
            if (floor -> tileArray[atkUpX][atkUpY].hasEnemy() == 1)
            //take health from enemy above player
            {
                if ((enemyArray[q].getCurrentX() == atkUpX) &&
                   (enemyArray[q].getCurrentY() == atkUpY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    if (enemyArray[q].getHealth() < 1)
                    {
                        player1.gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkUpX][atkUpY].setEnemy(0);
                    }
                    else
                    {
                        /*if (player1.evade() == false)
                        {
                            player1.takeMeleeDamage(enemyArray[q].getDamage());
                        }
                        else
                        {
                            //printw("You evaded the enemy counter!");
                        }*/
                    }
                }
            }

        // else if there is an enemy to the left of the player

            //take health from enemy to the left of player
            else if (floor -> tileArray[atkLeftX][atkLeftY].hasEnemy() == 1)
            {
                if ((enemyArray[q].getCurrentX() == atkLeftX) &&
                   (enemyArray[q].getCurrentY() == atkLeftY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    if (enemyArray[q].getHealth() < 1)
                    {
                        player1.gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkLeftX][atkLeftY].setEnemy(0);
                    }
                    else
                    {
                        /*if (player1.evade() == false)
                        {
                            player1.takeMeleeDamage(enemyArray[q].getDamage());
                        }
                        else
                        {

                        }*/
                    }
                }
            }
        // else if there is an enemy to the right of the player
            //take health from enemy to the right of the player
            else if (floor -> tileArray[atkRightX][atkRightY].hasEnemy() == 1)
            {
                if ((enemyArray[q].getCurrentX() == atkRightX) &&
                   (enemyArray[q].getCurrentY() == atkRightY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    if (enemyArray[q].getHealth() < 1)
                    {
                        player1.gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkRightX][atkRightY].setEnemy(0);
                    }
                    else
                    {
                        /*if (player1.evade() == false)
                        {
                            player1.takeMeleeDamage(enemyArray[q].getDamage());
                        }
                        else
                        {

                        }*/
                    }
                }
            }
        // else if there is an enemy under the player
            else if (floor -> tileArray[atkDownX][atkDownY].hasEnemy() == 1)
            {
                if ((enemyArray[q].getCurrentX() == atkDownX) &&
                   (enemyArray[q].getCurrentY() == atkDownY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    if (enemyArray[q].getHealth() < 1)
                    {
                        player1.gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkDownX][atkDownY].setEnemy(0);
                    }
                    else
                    {
                        /*if (player1.evade() == false)
                        {
                            player1.takeMeleeDamage(enemyArray[q].getDamage());
                        }
                        else
                        {

                        }*/
                    }
                }
            }
        }
    }
    void playerDirMagicAtk(Floor*& floor, Player& player1, Enemy enemyArray[50])
    {
        if (player1.getMagicAmount() >= 10)
        {
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

    void playerArrowAtk(Floor*& floor, Player& player1, Enemy enemyArray[50])
    {
        if (player1.getArrowAmount() >= 10)
        {
            int randomChance = (rand() % 100);
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
                            enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
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
                            enemyArray[q].takeMeleeDamage(player1.getDamage(),  player1.CritHit());
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
                            enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
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
                            enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
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
            player1.setArrowAmount(player1.getArrowAmount() - 1);
        }
        else
        {
            printw("You're out of arrows!!");
        }
    }
    void enemyMeleeAttack(int inDamage, Player& player1)
    {
        //test to see if it's getting inside this function
        //assert(false);
        player1.takeMeleeDamage(inDamage, player1.evade());
    }

    void playerArrowAtk(Floor*& floor, Player& player1, Enemy enemyArray[50])
    {
        if (player1.getArrowAmount() >= 10)
        {
            int randomChance = (rand() % 100);
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
                            enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
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
                            enemyArray[q].takeMeleeDamage(player1.getDamage(),  player1.CritHit());
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
                            enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
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
                            enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
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
            player1.setArrowAmount(player1.getArrowAmount() - 1);
        }
        else
        {
            printw("You're out of arrows!!");
        }
    }
};

#endif
