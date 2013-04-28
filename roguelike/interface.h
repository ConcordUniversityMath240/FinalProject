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
        init_pair (6, COLOR_BLACK, COLOR_YELLOW); //stairs
        init_pair (7, COLOR_BLACK, COLOR_GREEN);
        init_pair (8, COLOR_BLACK, COLOR_RED);
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
        char critical[10]= {0};
        sprintf(critical,"%i",player.getCritical());
        //int blk = 219;

        move(0,0);
        printw("Name   : Filburt");
        move(0,20);
        printw("Class    : ");
        move(1,0);
        printw("Level  : ");
        printw(level);
        move(1,20);
        printw("[");
        int tempFill = ((player.getExperience() * 10) / player.getExperience_Cap());


        int temp = 10 - tempFill; //player.getExperience()/10;
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

        printw("\nHealth : ");
        printw(health);printw("/");printw(maxHealth);
        move(3,20);
        printw("[");
        tempFill = ((player.getHealth() * 10 ) / player.getHealthCap());
        temp = 10 - tempFill;


        //char Temp[10]= {0};  123 4567 891
        //sprintf(Temp,"%i",tempFill);
        //printw("TEMPFIL = ");printw(Temp);
        if (tempFill > 7)
            attron (COLOR_PAIR(7)); // green if > 70%
        if (tempFill < 4)
            attron (COLOR_PAIR(8)); // red if < 40%
        if (tempFill > 3 && tempFill < 8)
            attron (COLOR_PAIR(6)); // else yellow

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

        printw("]");
        printw("\nAttack : ");printw(attack);
        move(4,20);printw("Defense : ");printw(defense);
        printw("\nEvade  : ");printw(evade);
        move(5,20);printw("Critical: ");printw(critical);
        printw("\n");

    }

    void drawHelp(Player player1)
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
        printw("'f' to melee attack \n");
        if (player1.getLevel() >= 3)
        {
            printw("'r' to use Directional magic attack \n");
        }
        if (player1.getLevel() >= 4)
        {
            printw("'c' to use Heal magic \n");
        }
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
