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
        Floor floor1;
        Floor floor2;
        Floor floor3;
        Floor* currentFloor = &floor1;

        // Initialization.
        floor1.initializeFloor();
        floor1.populateFloor();
        floor2.initializeFloor();
        floor3.initializeFloor();
        updatePlayerLocation(player1, currentFloor);

        char counter = '0';

        // Get Input
        while (input != '9')
        {
            printw("%s\n", "Enter arrows to move or 9 to exit");

            // Testing Stuff:
            // See what the integer value for the key pressed is:
            //printw("%i\n", input);
            currentFloor -> displayFloor();
            input = getch();
            if (input == KEY_UP || input == KEY_LEFT || input == KEY_DOWN || KEY_RIGHT)
                {
                    player1.move(input, currentFloor);
                    erase();
                    refresh();
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
};

#endif
