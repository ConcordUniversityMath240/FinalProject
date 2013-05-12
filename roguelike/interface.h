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
        init_pair (5, COLOR_BLACK, COLOR_WHITE);
        init_pair (6, COLOR_YELLOW, COLOR_BLACK); //stairs
        init_pair (7, COLOR_GREEN, COLOR_BLACK);
        init_pair (8, COLOR_RED, COLOR_BLACK);
        init_pair (9, COLOR_GREEN, COLOR_BLACK);
        init_pair (10, COLOR_MAGENTA, COLOR_BLACK);
        attron (A_BOLD);
    }

    void gotoxy(int x,int y)
    {
        printf("%c[%d;%df",0x1B,y,x);
    }
    void drawOver(Player& player)
    {
        clearUpper();
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
        char magicPower[10] = {0};
        sprintf(magicPower,"%i",player.getMagicPower());
        char magicDefence[10] = {0};
        sprintf(magicDefence,"%i",player.getMagicDefense());
        char Arrows[10] = {0};
        sprintf(Arrows,"%i",player.getArrowAmount());
        char Mana[10] = {0};
        sprintf(Mana,"%i",player.getMagicAmount());
        char ManaCap[10] = {0};
        sprintf(ManaCap,"%i",player.getMagicAmount_Cap());
        //int blk = 219;

        move(0,0);
        printw("Name   : Filburt");
        move(0,20);
        printw("Class: ");
        if (player.getType() == 1)
            printw("Fighter");
        else if (player.getType() == 2)
            printw("Mage");
        else if (player.getType() == 3)
            printw("Archer");

        // Level/Experience
        move(1,0);
        printw("Level  : ");
        printw(level);
        move(2,0);
        printw("Exp    : ");
        printw(experience);
        printw("/");
        printw(experience_Cap);
        move(2,20);
        printw("[");
        int tempFill = ((player.getExperience() * 10) / player.getExperience_Cap());
        attron (COLOR_PAIR(10));
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


        // Health + Health Bar
        move(3,0);
        printw("Health : ");
        printw(health);
        printw("/");
        printw(maxHealth);
        move(3,20);
        printw("[");
        tempFill = ((player.getHealth() * 10 ) / player.getHealthCap());

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


        // Magic Meter
        printw("]\n");
        printw("Mana   : ");
        printw(Mana);printw("/");printw(ManaCap);
        move(4,20);
        printw("[");
        tempFill = ((player.getMagicAmount() * 10 ) / player.getMagicAmount_Cap());

        if (tempFill > 7)
            attron (COLOR_PAIR(2)); // green if > 70%
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

        // Other Stats
        move(6,0);
        printw("Attack: ");
        printw(attack);
        move(6,20);
        printw("Defense : ");
        printw(defense);
        move(7,0);
        printw("Evade: ");
        printw(evade);
        move(7,20);
        printw("Critical: ");
        printw(critical);
        move(8,0);
        printw("Magic Attack: ");
        printw(magicPower);
        move(8,20);
        printw("Magic Defense: ");
        printw(magicDefence);
        move(9,0);
        printw("Arrows: ");
        printw(Arrows);
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
        printw("Use the Arrow Keys to move.");
        printw("\n");
        printw("The green lines around your character is how far directional attacks go.");
        printw("\n");
        printw("Press 'F' to use your melee attack \n");
        //printw("\n");
        printw("For the Archer, press 'G' to shoot arrows.");
        printw("\n");
        if (player1.getLevel() >= 3)
        {
            printw("Press 'R' to use your directional magic attack \n");
        }
        if (player1.getLevel() >= 4)
        {
            printw("Press 'C' to use Heal magic \n");
        }
        printw("Press 'I' to view your Inventory.\n");
        printw("Press 'H' to view this screen again.\n");
        printw("Press '9' to exit the game.");
        printw("\n");
        getch();
    }

    void clearLower()
    {
        move(45, 0);
        clrtoeol();
        move(46, 0);
        clrtoeol();
        move(47, 0);
        clrtoeol();
        move(48, 0);
        clrtoeol();
        move(49, 0);
        clrtoeol();
        move(50, 0);
        clrtoeol();
        move(51, 0);
        clrtoeol();
        move(52, 0);
        clrtoeol();
        move(53, 0);
        clrtoeol();
    }

    void clearUpper()
    {
        move(0, 0);
        clrtoeol();
        move(1, 0);
        clrtoeol();
        move(2, 0);
        clrtoeol();
        move(3, 0);
        clrtoeol();
        move(4, 0);
        clrtoeol();
        move(5, 0);
        clrtoeol();
        move(6, 0);
        clrtoeol();
        move(7, 0);
        clrtoeol();
        move(8, 0);
        clrtoeol();
        move(9, 0);
        clrtoeol();
    }

    void drawUnder()
    {
        //printw("(h)elp add more stuff here\n");
        //printw("@@@@@@@    @@@@@@    @@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@@@   @@@  @@@  @@@  @@@\n");
        //printw("@@@@@@@@  @@@@@@@@  @@@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@@@@  @@@  @@@@ @@@  @@@\n");
        //printw("@@!  @@@  @@!  @@@  !@@        @@!  @@@  @@!       @@! @@! @@!  @@!  @@!@!@@@  @@!\n");
        //printw("!@!  @!@  !@!  @!@  !@!        !@!  @!@  !@!       !@! !@! !@!  !@!  !@!!@!@!  !@!\n");
        //printw("@!@!!@!   @!@  !@!  !@! @!@!@  @!@  !@!  @!!!:!    @!! !!@ @!@  !!@  @!@ !!@!  !!@\n");
        //printw("!!@!@!    !@!  !!!  !!! !!@!!  !@!  !!!  !!!!!:    !@!   ! !@!  !!!  !@!  !!!  !!!\n");
        //printw("!!: :!!   !!:  !!!  :!!   !!:  !!:  !!!  !!:       !!:     !!:  !!:  !!:  !!!  !!:\n");
        //printw(":!:  !:!  :!:  !:!  :!:   !::  :!:  !:!  :!:       :!:     :!:  :!:  :!:  !:!  :!:\n");
        //printw("::   :::  ::::: ::   ::: ::::  ::::: ::   :: ::::  :::     ::    ::   ::   ::   ::\n");
        //printw(":   : :   : :  :    :: :: :    : :  :   : :: ::    :      :    :    ::    :   :\n");
    }
};

#endif
