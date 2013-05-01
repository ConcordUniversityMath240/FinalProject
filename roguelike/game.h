/*******************************************
game.h - Game class header file.

Author: MATH 240 Team

Purpose: Main game method and other related methods.
*******************************************/
#include <curses.h>
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include "map.h"
#include "object.h"
#include "enemy.h"
#include "player.h"
#include "interface.h"
#include "combat.h"

using namespace std;

/************************************************
Game class

Member functions:
    Game()                  Creates a game object.
    run()                   Starts, recieves input, and ends the game.
    updatePlayerLocation()  Keeps a Player object's coordinates up to date.
    setupFloors()           Creates, orders, and links the Floor objects.
    populateEnemyList()     Creates an ordered array of Enemies and assigns
                            their coordinates.
*************************************************/
class Game
{
private:
    Floor floorArray[LAST_FLOOR];

public:

    Enemy enemyArray[50];

    Game()
    {
    }

    // Start and run the game.
    void run()
    {
        // moved here from main, don't erase :P
        srand(time(NULL));
        char input;
        /* Start curses mode */
        initscr();
        /* Line buffering disabled	*/
        raw();
        /* We get KEYS*/
        keypad(stdscr, TRUE);
        /* Don't echo() while we do getch won't work otherwise */
        noecho();

        //color and interface init
        Interface interface;
        interface.init();

        // Create objects.
        Player player1;
        Combat combat1;
        Floor* currentFloor = &floorArray[0];

        // Initialization.
        setupFloors();
        updatePlayerLocation(player1, currentFloor);
        populateEnemyList(floorArray);

        halfdelay(5);
        // Get Input
        while (input != '9')
        {
            if (player1.getHealth() < 1)
            {
                printw("  You were killed!! \n  Game Over!! \n");
                // need to make it wait for a few seconds before exiting
                exit(1);
            }
            interface.drawOver(player1); // stuff above board
            printw("%s\n", "--------------------------------------------------------------------------------");
            currentFloor -> displayFloor();
            printw("%s\n", "--------------------------------------------------------------------------------");
            interface.drawUnder(); // draw below board

            input = getch();
            //move
            if (input == KEY_UP || input == KEY_LEFT || input == KEY_DOWN || KEY_RIGHT)
                {
                    player1.move(input, currentFloor, enemyArray);
                    erase();
                    refresh();
                    for (int q = 0; q < 50; q++)
                    {
                        if (enemyArray[q].getCurrentFloorLevel() == currentFloor -> getFloorLevel())
                        {
                            enemyArray[q].move(currentFloor);
                            if (enemyArray[q].getAtkStatus() == true)
                            {
                                combat1.enemyMeleeAttack(enemyArray[q].getDamage(), player1);
                                enemyArray[q].setAtkStatus(0);
                            }
                        }
                    }
                    erase();
                    refresh();
                }
            //use stairs
            if(input == ' ')
                {
                    player1.useStairs(currentFloor);
                    updatePlayerLocation(player1, currentFloor);
                    erase();
                    refresh();
                }
            //melee attack
            if (input == 'f' || input == 'F')
            {
                erase();
                refresh();
                combat1.playerMeleeAttack(currentFloor, player1, enemyArray);
            }
            if ((input == 'c' || input == 'C') && (player1.getLevel() >= 4))
            {
                erase();
                refresh();
                player1.healMagic();
            }
            if ((input == 'r' || input == 'r') && (player1.getLevel() >= 3))
            {
                erase();
                refresh();
                combat1.playerDirMagicAtk(currentFloor, player1, enemyArray);
            }
            //help screen
            if (input == 'h' || input == 'H')
            {
                interface.drawHelp(player1);
                erase();
                refresh();
            }
        }
        endwin();
    }

    // Search through the floor to find the player, then update its coordinates.
    void updatePlayerLocation(Player& player, Floor*& currentFloor)
    {
        for (int x = 0; x < XSIZE; x++)
            for (int y = 0; y < YSIZE; y++)
            {
                if(currentFloor -> tileArray[x][y].hasPlayer() == 1)
                {
                    player.setCurrentX(x);
                    player.setCurrentY(y);
                    refresh();
                }
            }
    }

    void setupFloors()
    {
        for (int i = 0; i < LAST_FLOOR; i++)
        {
            floorArray[i].prev = &floorArray[i-1];
            floorArray[i].next = &floorArray[i+1];
            floorArray[i].setFloorLevel(i+1);
            floorArray[i].initializeFloor();
            floorArray[i].populateFloor();
        }
    }

    void populateEnemyList(Floor floorArray[LAST_FLOOR])
    {
        int counter = 0;
        for (int i = 0; i < LAST_FLOOR; i++)
            for (int x = 0; x < XSIZE; x++)
                for (int y = 0; y < YSIZE; y++)
                {
                    if (floorArray[i].tileArray[x][y].hasEnemy() == 1)
                    {
                        enemyArray[counter].setCurrentFloorLevel(i+1);
                        enemyArray[counter].setCurrentX(x);
                        enemyArray[counter].setCurrentY(y);
                        counter++;
                    }
                }
    }


};

#endif
