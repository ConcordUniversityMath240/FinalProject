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

        // Create objects.
        Player player1;
        Floor* currentFloor = &floorArray[0];

        // Initialization.
        setupFloors();
        updatePlayerLocation(player1, currentFloor);

        printw("%s\n", "Enter arrows to move or 9 to exit.");
        printw("%s\n\n", "Press the spacebar when standing on stairs to go up or down.");
        // Get Input
        while (input != '9')
        {
            printw("%s\n", "--------------------------------------------------------------------------------");
            currentFloor -> displayFloor();
            printw("%s\n", "--------------------------------------------------------------------------------");
            // Print player stats here later.
            input = getch();
            if (input == KEY_UP || input == KEY_LEFT || input == KEY_DOWN || KEY_RIGHT)
                {
                    erase();
                    refresh();
                    player1.move(input, currentFloor);
                }

            if(input == ' ')
                {
                    erase();
                    refresh();
                    player1.useStairs(currentFloor);
                    updatePlayerLocation(player1, currentFloor);
                }
        }
        endwin();
    }

    void printHeader()
    {
        printw("s%", "TEST LINE \n");
        printw("s%", "---------------------------------------------------------- \n");
    }

    void printFooter()
    {
        printw("%s", "----------------------------------------------------------");
        printw("%s", "TEST LINE \n");
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

//        floorArray[0].prev = NULL;
//        floorArray[LAST_FLOOR].next = NULL;
    }
};

#endif
