/************************************************
interface.h - interface classes header file.
      - init()
        Inits color, color pairs,
      - drawOver(board)
      - drawUnder()
      - drawHelp()

Author: jay

Purpose:
*************************************************/
using namespace std;

#ifndef INTERFACE_H
#define INTERFACE_H
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Interface
{
public:

    Interface() {}
    void init()
    {

        //Color Init
        start_color();
        //attron (COLOR_PAIR (1));
        init_pair (1, COLOR_BLUE, COLOR_BLACK); //1 is default white on black
        init_pair (2, COLOR_CYAN, COLOR_BLACK); // WALLS
        init_pair (3, COLOR_RED, COLOR_BLACK);  //enemies
        init_pair (4, COLOR_WHITE, COLOR_BLACK);  //player
        attron (A_BOLD);
    }

    void drawOver(Player& player)
    {
        attron (COLOR_PAIR(4));
        char hp[10]= {0};
        sprintf(hp,"%i",player.getHealth());
        printw("Name Goes Here");
        printw("\n");
        printw("HP    : ");
        printw(hp);
        printw("\n");
        printw("MP    : -- needs added");
        printw("\n");
        printw("all other player stuff can go up here\n");
    }

    void drawHelp()
    {
        erase();
        printw("\n");
        printw(" __   __  _______  ___      _______");printw("\n");
        printw("|  | |  ||       ||   |    |    _  |");printw("\n");
        printw("|  |_|  ||    ___||   |    |   | | |");printw("\n");
        printw("|       ||   |___ |   |    |   |_| |");printw("\n");
        printw("|   _   ||    ___||   |___ |    ___|");printw("\n");
        printw("|  | |  ||   |___ |       ||   |");printw("\n");
        printw("|__| |__||_______||_______||___|");     printw("\n");
        printw("HELP SCREEN");
        printw("\n");
        printw("Press the Arrow Keys to move");
        printw("\n");
        printw("Press the 'F' Key to attack");
        printw("\n");
        printw("Press the '9' Key to exit the game");
        printw("\n");
        printw("other help crap goes here and needs added");
        printw("\n");
        getch();
    }

    void drawUnder()
    {
        printw("(h)elp add more stuff here");
    }
};

#endif
