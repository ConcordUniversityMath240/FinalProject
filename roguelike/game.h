/*******************************************
game.h - Game class header file.

Author:

Purpose:
*******************************************/
#include <curses.h>
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "map.h"
#include "object.h"
#include "interface.h"

using namespace std;

/************************************************
Game class

Member functions:
    Game()
    run()
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
        Floor* currentFloor = &floorArray[0];

        // Initialization.
        setupFloors();
        updatePlayerLocation(player1, currentFloor);
        populateEnemyList(floorArray);

        // Get Input
        while (input != '9')
        {
            if (player1.getHealth() < 1)
            {
                printw("  You were killed!! \n  Game Over!! \n");
                //need to make this end game

            }
            interface.drawOver(player1); // stuff above board
            printw("%s\n", "--------------------------------------------------------------------------------");
            currentFloor -> displayFloor();
            printw("%s\n", "--------------------------------------------------------------------------------");
            interface.drawUnder(); // draw below board

            input = getch();

            if (input == KEY_UP || input == KEY_LEFT || input == KEY_DOWN || KEY_RIGHT)
                {
                    player1.move(input, currentFloor);
                    erase();
                    refresh();
                    for (int q = 1; q < 11; q++)
                    {
                        enemyArray[q].move(currentFloor/*, player1*/);
                    }
                    erase();
                    refresh();
                }

            if(input == ' ')
                {
                    player1.useStairs(currentFloor);
                    updatePlayerLocation(player1, currentFloor);
                    erase();
                    refresh();
                }

            if (input == 'f' || input == 'F')
            {
                erase();
                refresh();
                player1.attack(currentFloor, enemyArray);
            }

            if (input == 'h' || input == 'H')
            {
                interface.drawHelp();
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
                        enemyArray[counter].setCurrentX(x);
                        enemyArray[counter].setCurrentY(y);
                        counter++;
                    }
                }
    }


};

#endif
