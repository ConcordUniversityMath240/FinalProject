/********************************************
combat.h - Combat actions header file.

Author: Andy

Purpose: These classes allow for combat between enemies and the player.
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
    // Player presses (F) to attack an enemy.
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
        int atkUpDLeftX = player1.getCurrentX() - 1;
        int atkUpDLeftY = player1.getCurrentY() - 1;
        int atkUpDRightX = player1.getCurrentX() - 1;
        int atkUpDRightY = player1.getCurrentY() + 1;
        int atkDownDLeftX = player1.getCurrentX() + 1;
        int atkDownDLeftY = player1.getCurrentY() - 1;
        int atkDownDRightX = player1.getCurrentX() + 1;
        int atkDownDRightY = player1.getCurrentY() + 1;

        // Loop through all enemies.
        for (int q = 0; q < 50; q++)
        {
            // If there is an enemy above the player take health from enemy above player.
            if (floor -> tileArray[atkUpX][atkUpY].hasEnemy() == 1)

            {
                if ((enemyArray[q].getCurrentX() == atkUpX) &&
                   (enemyArray[q].getCurrentY() == atkUpY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    // If enemy dies, give the player experience and remove the enemy.
                    if (enemyArray[q].getHealth() < 1)
                    {
                        player1.gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkUpX][atkUpY].setEnemy(0);
                    }
                }
            }
            // If there is an enemy to the left of the player take health from enemy above player.
            else if (floor -> tileArray[atkLeftX][atkLeftY].hasEnemy() == 1)
            {
                if ((enemyArray[q].getCurrentX() == atkLeftX) &&
                   (enemyArray[q].getCurrentY() == atkLeftY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    // If enemy dies, give the player experience and remove the enemy.
                    if (enemyArray[q].getHealth() < 1)
                    {
                        player1.gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkLeftX][atkLeftY].setEnemy(0);
                    }
                }
            }
            // Right
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
                }
            }

            // Below
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
                }
            }
            // Up-Left
            else if (floor -> tileArray[atkUpDLeftX][atkUpDLeftY].hasEnemy() == 1)
            {
                if ((enemyArray[q].getCurrentX() == atkUpDLeftX) &&
                   (enemyArray[q].getCurrentY() == atkUpDLeftY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    if (enemyArray[q].getHealth() < 1)
                    {
                        player1.gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkUpDLeftX][atkUpDLeftY].setEnemy(0);
                    }
                }
            }
            // Up-Right
            else if (floor -> tileArray[atkUpDRightX][atkUpDRightY].hasEnemy() == 1)
            {
                if ((enemyArray[q].getCurrentX() == atkUpDRightX) &&
                   (enemyArray[q].getCurrentY() == atkUpDRightY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    if (enemyArray[q].getHealth() < 1)
                    {
                        player1.gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkUpDRightX][atkUpDRightY].setEnemy(0);
                    }
                }
            }
            // Down-Left
            else if (floor -> tileArray[atkDownDLeftX][atkDownDLeftY].hasEnemy() == 1)
            {
                if ((enemyArray[q].getCurrentX() == atkDownDLeftX) &&
                   (enemyArray[q].getCurrentY() == atkDownDLeftY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    if (enemyArray[q].getHealth() < 1)
                    {
                        player1.gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkDownDLeftX][atkDownDLeftY].setEnemy(0);
                    }
                }
            }
            // Down-Right
            else if (floor -> tileArray[atkDownDRightX][atkDownDRightY].hasEnemy() == 1)
            {
                if ((enemyArray[q].getCurrentX() == atkDownDRightX) &&
                   (enemyArray[q].getCurrentY() == atkDownDRightY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                    if (enemyArray[q].getHealth() < 1)
                    {
                        player1.gainExperience(enemyArray[q].getLevel());
                        floor -> tileArray[atkDownDRightX][atkDownDRightY].setEnemy(0);
                    }
                }
            }
        }
    }

    // Directional magic attack.
     void playerDirMagicAtk(Floor*& floor, Player& player1, Enemy enemyArray[50])
    {
        if (player1.getMagicAmount() >= 10)
        {
            /*char buffer[50];
            int randomChance = (rand() % 100);*/
            int atkUpX = player1.getCurrentX() - 1;
            int atkUpY = player1.getCurrentY();
            int atkLeftX = player1.getCurrentX();
            int atkLeftY = player1.getCurrentY() - 1;
            int atkRightX = player1.getCurrentX();
            int atkRightY = player1.getCurrentY() + 1;
            int atkDownX = player1.getCurrentX() + 1;
            int atkDownY = player1.getCurrentY();
            int atkUpDLeftX = player1.getCurrentX() - 1;
            int atkUpDLeftY = player1.getCurrentY() - 1;
            int atkUpDRightX = player1.getCurrentX() - 1;
            int atkUpDRightY = player1.getCurrentY() + 1;
            int atkDownDLeftX = player1.getCurrentX() + 1;
            int atkDownDLeftY = player1.getCurrentY() - 1;
            int atkDownDRightX = player1.getCurrentX() + 1;
            int atkDownDRightY = player1.getCurrentY() + 1;

            // If there is an enemy above the player, damage them.
            // If enemy dies, player gains XP and loses mana.
            for (int counter = 0; counter < 4; counter++)
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
            // Left
            for (int counter = 0; counter < 4; counter++)
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
            // Right
            for (int counter = 0; counter < 4; counter++)
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
            // Below
            for (int counter = 0; counter < 4; counter++)
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
            // Up-Left
            for (int counter = 0; counter < 4; counter++)
            {
                if (floor -> tileArray[atkUpDLeftX][atkUpDLeftY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {

                        if ((enemyArray[q].getCurrentX() == atkUpDLeftX) &&
                        (enemyArray[q].getCurrentY() == atkUpDLeftY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(player1.getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkUpDLeftX][atkUpDLeftY].setEnemy(0);
                            }
                        }
                    }
                    atkUpDLeftX = atkUpDLeftX - 1;
                        atkUpDLeftY = atkUpDLeftY - 1;
                }
            }
            // Up-Right
            for (int counter = 0; counter < 4; counter++)
            {

               if (floor -> tileArray[atkUpDRightX][atkUpDRightY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {

                        if ((enemyArray[q].getCurrentX() == atkUpDRightX) &&
                        (enemyArray[q].getCurrentY() == atkUpDRightY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(player1.getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkUpDRightX][atkUpDRightY].setEnemy(0);
                            }
                        }
                    }
                    atkUpDRightX = atkUpDRightX + 1;
                    atkUpDRightY = atkUpDRightY - 1;
                }
            }
            // Down-Left
            for (int counter = 0; counter < 4; counter++)
            {
               if (floor -> tileArray[atkDownDLeftX][atkDownDLeftY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {

                        if ((enemyArray[q].getCurrentX() == atkDownDLeftX) &&
                        (enemyArray[q].getCurrentY() == atkDownDLeftY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(player1.getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkDownDLeftX][atkDownDLeftY].setEnemy(0);
                            }
                        }
                    }
                    atkDownDLeftX = atkDownDLeftX - 1;
                    atkDownDLeftY = atkDownDLeftY + 1;
                }
            }
            // Down-Right
            for (int counter = 0; counter < 4; counter++)
            {
                if (floor -> tileArray[atkDownDRightX][atkDownDRightY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {

                        if ((enemyArray[q].getCurrentX() == atkDownDRightX) &&
                        (enemyArray[q].getCurrentY() == atkDownDRightY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(player1.getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkDownDRightX][atkDownDRightY].setEnemy(0);
                            }
                        }

                    }
                    atkDownDRightX = atkDownDRightX + 1;
                    atkDownDRightY = atkDownDRightY + 1;
                }
            }
        player1.setMagicAmount(player1.getMagicAmount() - 10);
        }
        else
        {
            move(45, 0);
            printw("You don't have enough MP!");
        }
    }

    // Shoot an arrow in front of the player.
    void playerArrowAtk(Floor*& floor, Player& player1, Enemy enemyArray[50])
    {
        if (player1.getArrowAmount() >= 10)
        {
            int atkUpX = player1.getCurrentX() - 1;
            int atkUpY = player1.getCurrentY();
            int atkLeftX = player1.getCurrentX();
            int atkLeftY = player1.getCurrentY() - 1;
            int atkRightX = player1.getCurrentX();
            int atkRightY = player1.getCurrentY() + 1;
            int atkDownX = player1.getCurrentX() + 1;
            int atkDownY = player1.getCurrentY();
            int atkUpDLeftX = player1.getCurrentX() - 1;
            int atkUpDLeftY = player1.getCurrentY() - 1;
            int atkUpDRightX = player1.getCurrentX() - 1;
            int atkUpDRightY = player1.getCurrentY() + 1;
            int atkDownDLeftX = player1.getCurrentX() + 1;
            int atkDownDLeftY = player1.getCurrentY() - 1;
            int atkDownDRightX = player1.getCurrentX() + 1;
            int atkDownDRightY = player1.getCurrentY() + 1;

            // If there is an enemy above the player within range, shoot
            // an arrow at it and deal damage. If enemy dies, player gains
            // experience and enemy is removed from game.
            for (int counter = 0; counter < 4; counter++)
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
            // Left
            for (int counter = 0; counter < 4; counter++)
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
            // Right
            for (int counter = 0; counter < 4; counter++)
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
            // Down
            for (int counter = 0; counter < 4; counter++)
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
            // Up-Left
            for (int counter = 0; counter < 4; counter++)
            {
                if (floor -> tileArray[atkUpDLeftX][atkUpDLeftY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkUpDLeftX) &&
                        (enemyArray[q].getCurrentY() == atkUpDLeftY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkUpDLeftX][atkUpDLeftY].setEnemy(0);
                            }
                        }
                    }
                    atkUpDLeftX = atkUpDLeftX - 1;
                        atkUpDLeftY = atkUpDLeftY - 1;
                }
            }
            // Up-Right
            for (int counter = 0; counter < 4; counter++)
            {

               if (floor -> tileArray[atkUpDRightX][atkUpDRightY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkUpDRightX) &&
                        (enemyArray[q].getCurrentY() == atkUpDRightY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkUpDRightX][atkUpDRightY].setEnemy(0);
                            }
                        }
                    }
                    atkUpDRightX = atkUpDRightX + 1;
                    atkUpDRightY = atkUpDRightY - 1;
                }
            }

            // Down-Left
            for (int counter = 0; counter < 4; counter++)
            {
               if (floor -> tileArray[atkDownDLeftX][atkDownDLeftY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkDownDLeftX) &&
                        (enemyArray[q].getCurrentY() == atkDownDLeftY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkDownDLeftX][atkDownDLeftY].setEnemy(0);
                            }
                        }
                    }
                    atkDownDLeftX = atkDownDLeftX - 1;
                    atkDownDLeftY = atkDownDLeftY + 1;
                }
            }
            // Down-Right
            for (int counter = 0; counter < 4; counter++)
            {
                if (floor -> tileArray[atkDownDRightX][atkDownDRightY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkDownDRightX) &&
                        (enemyArray[q].getCurrentY() == atkDownDRightY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMeleeDamage(player1.getDamage(), player1.CritHit());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                player1.gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkDownDRightX][atkDownDRightY].setEnemy(0);
                            }
                        }
                    }
                    atkDownDRightX = atkDownDRightX + 1;
                    atkDownDRightY = atkDownDRightY + 1;
                }
            }
            player1.setArrowAmount(player1.getArrowAmount() - 1);
        }

        else
        {
            move(45, 0);
            printw("You're out of arrows!!");
        }
    }
    void enemyMeleeAttack(int inDamage, Player& player1)
    {
        //test to see if it's getting inside this function
        //assert(false);
        player1.takeMeleeDamage(inDamage, player1.evade());
    }
};

#endif
