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
        int load = NULL;
        sqlite sql;
        /*
            // don't re run commands, this is just something to keep track on the commands used so far
            // creates table users
            sql.dbCommand("CREATE TABLE users (id integer primary key, user varchar(64));");
            // adds good ol' Filburt
            sql.dbCommand("INSERT INTO users (id, user) VALUES (NULL, 'Filburt');");
            // reading our previous insert
            sql.dbCommand("SELECT id FROM users WHERE user = 'Filburt';", "READ");
            // create table map
            sql.dbCommand("CREATE TABLE maps (id integer primary key, name varchar(64), content text);");
            //sql.dbCommand("drop table if exists maps");3
            //sql.dbCommand("CREATE TABLE attributes (id integer primary key, pid integer, level integer, health integer, health_cap integer, magicAmount integer, magicAmount_cap integer, damage integer, magicPower integer, defence integer, magicDefence integer, evasion integer,critical integer, experience integer, experience_cap integer);");
            //sql.dbCommand("INSERT INTO attributes (id, pid, level, health, health_cap, magicAmount, magicAmount_cap, damage, magicPower, defence, magicDefence, evasion, critical, experience, experience_cap) VALUES (NULL, 1, 1, 100, 100, 80, 80, 5, 5, 5, 5, 5, 5, 0, 100);");
        */
        // player attributes
        // location of objects
        string username = "Filburt";
        sql.dbCommand("SELECT id FROM users WHERE user = '"+string(username)+"';", "READ");
        string userid = sql.returnRead();
        string s_att[13] = {"level", "health", "health_cap", "magicAmount", "magicAmount_cap", "damage",
                                "magicPower", "defence", "magicDefence", "evasion", "critical",
                                "experience", "experience_cap"};
        int attr[13];

        string option;
        //while (option != "L" || option != "N") {
            cout<<"Please enter Load(L) to load or anything else to begin a new game ";
            cin >> option;
        //}
        if (option == "L") {
            load = 1;
        }
        if (load) {
            for (int i = 0; i < 13; i++) {
                sql.dbCommand("SELECT "+s_att[i]+" FROM attributes WHERE pid = '"+userid+"';", "READ");
                attr[i] = atoi(sql.returnRead().c_str());
                cout<<s_att[i]<<" "<<attr[i]<<endl;
            }
        }
        else {
            attr[0] = 1; attr[1] = 100; attr[2] = 100; attr[3] = 80; attr[4] = 80; attr[5] = 5;
            attr[6] = 5; attr[7] = 5; attr[8] = 5; attr[9] = 5; attr[10] = 5; attr[11] = 0;
            attr[12] = 100;
        }
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
        Player player1(attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], attr[6], attr[7], attr[8],
                       attr[9], attr[10], attr[11], attr[12]);
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
            if (input == 's' || input == 'S') {
                string health = sql.convertInt(player1.getHealth());
                string damage = sql.convertInt(player1.getDamage());
                string defence = sql.convertInt(player1.getDefense());
                string level = sql.convertInt(player1.getLevel());
                string health_cap = sql.convertInt(player1.getHealth_cap());
                string magicAmount = sql.convertInt(player1.getMagicAmount());
                string magicAmount_cap = sql.convertInt(player1.getMagicAmount_Cap());
                string magicPower = sql.convertInt(player1.getMagicPower());
                string magicDefence = sql.convertInt(player1.getMagicDefense());
                string evasion = sql.convertInt(player1.getEvasion());
                string critical = sql.convertInt(player1.getCritical());
                string experience = sql.convertInt(player1.getExperience());
                string experience_cap = sql.convertInt(player1.getExperience_Cap());

                sql.dbCommand("UPDATE attributes SET health = "+string(health)+", damage = "+string(damage)+", defence = "+string(defence)+", level = "+string(level)+", health_cap = "+string(health_cap)+", magicAmount = "+string(magicAmount)+", magicAmount_cap = "+string(magicAmount_cap)+", magicPower = "+string(magicPower)+", magicDefence = "+string(magicDefence)+", critical = "+string(critical)+", evasion = "+string(evasion)+", experience = "+string(experience)+", experience_cap = "+string(experience_cap)+" WHERE pid = '"+userid+"';");
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
