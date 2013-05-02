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
#include "inventory.h"
#include "player.h"
#include "interface.h"
#include "combat.h"
#include "sql.cpp"

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

    Enemy enemyArray[51];
    Item itemArray[50];

    Game()
    {
    }

    // Start and run the game.
    void run()
    {
        // create db object
        sqlite sql;
        sql.dbCommand("SELECT * FROM users", "READ");
        //sql.returnRead();
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
        populateItemList(floorArray);

        int toEquip;

        halfdelay(5);
        // Get Input
        while (input != '9')
        {
            refresh();
            interface.drawOver(player1); // stuff above board
            printw("%s\n", "--------------------------------------------------------------------------------");
            currentFloor -> displayFloor();
            printw("%s\n", "--------------------------------------------------------------------------------");
            interface.drawUnder(); // draw below board
            input = getch();

            // Player Movement
            if (input == KEY_UP || input == KEY_LEFT || input == KEY_DOWN || KEY_RIGHT)
            {
                refresh();
                interface.clearLower();
                player1.movePlayer(input, currentFloor, enemyArray, itemArray);
                for (int q = 0; q < 51; q++)
                {
                    if (enemyArray[q].getCurrentFloorLevel() == currentFloor -> getFloorLevel())
                    {
                        enemyArray[q].move(currentFloor);
                        if ((enemyArray[q].getAtkStatus() == true) && enemyArray[q].getHealth() > 0)
                        {
                            combat1.enemyMeleeAttack(enemyArray[q].getDamage(), player1);
                            enemyArray[q].setAtkStatus(false);
                        }
                    }
                }
            }
            // Use Stairs
            if(input == ' ')
            {
                refresh();
                interface.clearLower();
                player1.useStairs(currentFloor);
                updatePlayerLocation(player1, currentFloor);
            }
            // Melee Attack
            if (input == 'f' || input == 'F')
            {
                interface.clearLower();
                refresh();
                player1.attack(currentFloor, enemyArray);
                if (enemyArray[50].getHealth() < 1)
                {
                    printw("You win!");
                    getch();
                    exit(1);
                }
            }
            // Heal
            if ((input == 'c' || input == 'C') && (player1.getLevel() >= 4))
            {
                refresh();
                interface.clearLower();
                player1.healMagic();
                interface.clearLower();
            }
            // Directional Magic
            if ((input == 'r' || input == 'r') && (player1.getLevel() >= 3))
            {
                refresh();
                interface.clearLower();
                player1.directionalMagic(currentFloor, enemyArray);
            }
            // Help Screen
            if (input == 'h' || input == 'H')
            {
                interface.drawHelp(player1);
                erase();
                refresh();
            }
            // Inventory Screen
            if (input == 'i' || input == 'I')
            {

                erase();
                refresh();
                player1.printEquipped();
                toEquip = player1.playerInventory.print();
                if (toEquip != 99)
                    player1.equipItem(toEquip);

                erase();
                refresh();
            }

            // Death Test
            if (player1.getHealth() < 1)
            {
                printw("  You were killed!! \n  Game Over!! \n Press any key to exit...");
                getch();
                exit(1);
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

    // Set up Floors and their relation to each other.
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

    // Populates the Game enemy array with the proper coordinates.
    void populateEnemyList(Floor floorArray[LAST_FLOOR])
    {
        int counter = 0;
        for (int i = 0; i < LAST_FLOOR; i++)
            for (int x = 0; x < XSIZE; x++)
                for (int y = 0; y < YSIZE; y++)
                {
                    if (floorArray[i].tileArray[x][y].hasBoss() == 1)
                    {
                        enemyArray[50].setBoss(1);
                        enemyArray[counter].setCurrentFloorLevel(i+1);
                        enemyArray[counter].setCurrentX(x);
                        enemyArray[counter].setCurrentY(y);
                        enemyArray[50].setHealth(500);
                        counter++;
                    }

                    else if (floorArray[i].tileArray[x][y].hasEnemy() == 1)
                    {
                        enemyArray[counter].setCurrentFloorLevel(i+1);
                        enemyArray[counter].setCurrentX(x);
                        enemyArray[counter].setCurrentY(y);
                        counter++;
                    }

                    if (counter == 49)
                        return;
                }
    }

    // Populates the Game item array with the proper coordinates.
    void populateItemList(Floor floorArray[LAST_FLOOR])
    {
        int counter = 0;
        for (int i = 0; i < LAST_FLOOR; i++)
            for (int x = 0; x < XSIZE; x++)
                for (int y = 0; y < YSIZE; y++)
                {
                    if (floorArray[i].tileArray[x][y].hasItem() == 1)
                    {
                        itemArray[counter].setCurrentFloorLevel(i+1);
                        itemArray[counter].setCurrentX(x);
                        itemArray[counter].setCurrentY(y);
                        itemArray[counter].randomize();
                        counter++;
                        if (counter == 49)
                            return;
                    }
                }
    }
};

#endif
