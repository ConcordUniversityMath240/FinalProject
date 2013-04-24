/************************************************
interface.h - interface classes header file.
      - init()
        Inits color, color pairs,
      - drawOver(Player)
      - drawUnder()
      - drawHelp()

Author: jay

Purpose: Just do it
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
        init_pair (5, COLOR_BLACK,COLOR_WHITE);
        init_pair (6, COLOR_YELLOW, COLOR_BLACK); //stairs
        attron (A_BOLD);
    }

    void gotoxy(int x,int y)
    {
        printf("%c[%d;%df",0x1B,y,x);
    }
    void drawOver(Player& player)
    {
        //change ints to char arrays for printing to screen
        attron (COLOR_PAIR(4));
        char health[10]= {0};
        sprintf(health,"%i",player.getHealth());
        char maxHealth[10]= {0};
        sprintf(maxHealth,"%i",player.getHealthCap());
        char level[10]= {0};
        sprintf(level,"%i",player.getLevel());
        char experience[10]= {0};
        sprintf(experience,"%i",player.getExperience());
        char experience_Cap[10]= {0};
        sprintf(experience_Cap,"%i",player.getExperience_Cap());
        char attack[10]= {0};
        sprintf(attack,"%i",player.getDamage());
        char defense[10]= {0};
        sprintf(defense,"%i",player.getDefense());
        char evade[10]= {0};
        sprintf(evade,"%i",player.getEvasion());

        //int blk = 219;

        move(0,0);
        printw("Name   : Filburt");
        move(0,20);
        printw("Class  : ");
        move(1,0);
        printw("Level  : ");
        printw(level);
        move(1,20);
        printw("[");
        int temp = player.getExperience_Cap();
        int tempFill = player.getExperience()/10;
        attron (COLOR_PAIR(5));
        for (int i=0; i<tempFill; i++)
        {
                addch(219);
                addch(219);
        }
        attron (COLOR_PAIR(4));
        for (int i = 10; i > tempFill; i--)
        {
            addch(219);
            addch(219);
        }
        printw("]\n");
        printw("Exp    : "); printw(experience);printw("/");printw(experience_Cap);

        move(2,20);
        temp = player.getHealth();


        printw("\nHealth : ");
        printw(health);printw("/");printw(maxHealth);printw("\n");
        printw("Attack : ");printw(attack);
        move(4,20);printw("Defense : ");printw(defense);
        printw("\nEvade  : ");printw(evade);

//        int temp = player.getHealth();


        // move(2,15);//printf(blk);

        //printw("Exp     : ");
        //printw(experience);
        printw("\n");
        //printw("");
    }

    void drawHelp()
    {
        erase();
        printw("\n");
        printw(" __   __  _______  ___      _______");
        printw("\n");
        printw("|  | |  ||       ||   |    |       |");
        printw("\n");
        printw("|  |_|  ||    ___||   |    |    _  |");
        printw("\n");
        printw("|       ||   |___ |   |    |   |_| |");
        printw("\n");
        printw("|       ||    ___||   |___ |    ___|");
        printw("\n");
        printw("|   _   ||   |___ |       ||   |");
        printw("\n");
        printw("|__| |__||_______||_______||___|");
        printw("\n");
        printw("HELP SCREEN");
        printw("\n");
        printw("Arrow Keys to move 9 to exit f to fight");
        printw("\n");
        printw("other help crap goes here and needs added");
        printw("\n");
        getch();
    }

    void drawUnder()
    {
      //  printw("(h)elp add more stuff here\n");
printw("@@@@@@@    @@@@@@    @@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@@@   @@@  @@@  @@@  @@@\n");
printw("@@@@@@@@  @@@@@@@@  @@@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@@@@  @@@  @@@@ @@@  @@@\n");
printw("@@!  @@@  @@!  @@@  !@@        @@!  @@@  @@!       @@! @@! @@!  @@!  @@!@!@@@  @@!\n");
printw("!@!  @!@  !@!  @!@  !@!        !@!  @!@  !@!       !@! !@! !@!  !@!  !@!!@!@!  !@!\n");
printw("@!@!!@!   @!@  !@!  !@! @!@!@  @!@  !@!  @!!!:!    @!! !!@ @!@  !!@  @!@ !!@!  !!@\n");
printw("!!@!@!    !@!  !!!  !!! !!@!!  !@!  !!!  !!!!!:    !@!   ! !@!  !!!  !@!  !!!  !!!\n");
printw("!!: :!!   !!:  !!!  :!!   !!:  !!:  !!!  !!:       !!:     !!:  !!:  !!:  !!!  !!:\n");
printw(":!:  !:!  :!:  !:!  :!:   !::  :!:  !:!  :!:       :!:     :!:  :!:  :!:  !:!  :!:\n");
printw("::   :::  ::::: ::   ::: ::::  ::::: ::   :: ::::  :::     ::    ::   ::   ::   ::\n");
 printw(":   : :   : :  :    :: :: :    : :  :   : :: ::    :      :    :    ::    :   :\n");
}
};

#endif
