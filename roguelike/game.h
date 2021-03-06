/*******************************************
game.h - Game class header file.

Author: MATH 240 Team

Purpose: Main game method and other related methods.
*******************************************/
#include <curses.h>
#ifndef GAME_H
#define GAME_H
#include <fstream>
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
    populateItemList()      Creates an ordered array of Items and assigns their
                            coordinates.
    printTitle()            prints the title screen
    printDefeat()           prints a game over message
    printVictory()          prints a message when a player wins the game
*************************************************/
class Game
{
private:
    Floor floorArray[LAST_FLOOR];
    Floor floor;

public:

    Enemy enemyArray[50];
    Item itemArray[50];

    // Construct a default Game object.
    Game(){}

    // Start and run the game.
    void run()
    {
        printTitle();
        // create db object
        int load = 0;
        sqlite sql;

        // username's name
        string username = "Filburt";
        // search for user id
        sql.dbCommand("SELECT id FROM users WHERE user = '"+string(username)+"';", "READ");
        // store returned user id
        string userid = sql.returnRead();
        // column names from the db
        string s_att[15] = {"level", "health", "health_cap", "magicAmount", "magicAmount_cap", "damage",
                                "magicPower", "defence", "magicDefence", "evasion", "critical",
                                "experience", "experience_cap", "type", "arrow"};
        // holds attributes returned from db
        int attr[15];

        // player input
        char input;
        char Player_Choice;
        string option;

        cout<<"Please enter Load(L) to load or anything else to begin a new game ";
        cin >> option;

        if (option == "L") {
            load = 1;
        }

        // If the player loads a game, assign stats from the database to the player.
        if (load) {
            // loop through each column for the user id
            for (int i = 0; i < 15; i++) {
                sql.dbCommand("SELECT "+s_att[i]+" FROM attributes WHERE pid = '"+userid+"';", "READ");
                // store attributes
                attr[i] = atoi(sql.returnRead().c_str());
                //cout<<s_att[i]<<" "<<attr[i]<<endl;
            }
        }
        // Otherwise start a new game by allowing the player to choose a class.
        else
        {
                bool Check = false;  //check for if Player put in good information
                while(Check != true)
                {
                    //gets player choice
                    cout << "Enter F for fighter, M for mage, or A for archer: ";
                    cin >> Player_Choice;

                    // Error Checking
                    if((Player_Choice == 'F') || (Player_Choice == 'M') || (Player_Choice == 'A'))
                    {
                        Check = true;
                    }
                    else
                    {
                        Check = false;
                    }
                    clear(); //clears the screen of the choice selection, so game can be printed
                }
        }

        // Construct the Player object with DB stats if a game was loaded or with default class stats if not.
        if (load)
            // load the attributes from db
            Player player1(attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], attr[6], attr[7], attr[8],
                           attr[9], attr[10], attr[11], attr[12], attr[13], attr[14]);
        else
            Player player1(Player_Choice);

        // Initialize Curses
        srand(time(NULL));
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();

        //color and interface init
        Interface interface;
        interface.init();

        // Create objects.
        Player player1(Player_Choice);
        Combat combat1;
        Floor* currentFloor = &floorArray[0];

        // Initialization.
        setupFloors();
        updatePlayerLocation(player1, currentFloor);
        populateEnemyList(floorArray);
        populateItemList(floorArray);
        int toEquip;

        // Get Input
        while (input != '9')
        {
            halfdelay(10);
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
                player1.Recover_Magic();
                floor.Perimeter();
                refresh();
                interface.clearLower();
                player1.movePlayer(input, currentFloor, enemyArray, itemArray);
                    for (int q = 0; q < 50; q++)
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
                combat1.playerMeleeAttack(currentFloor, player1, enemyArray);
                if (enemyArray[50].getHealth() < 1)
                {
                    printw("You win!");
                    getch();
                    exit(1);
                }
            }

            //Attack that only archer can use
            if ((input == 'g' || input == 'G') && (Player_Choice == 'A'))
            {
                erase();
                refresh();
                combat1.playerArrowAtk(currentFloor, player1, enemyArray);
            }

            // Heal (Available to all at different times)
            if ((input == 'c' || input == 'C') && ((player1.getLevel() >= 4) || (Player_Choice == 'M')))
            {
                refresh();
                interface.clearLower();
                player1.healMagic();
                interface.clearLower();
            }
            // Directional Magic (available to all at different times)
            if ((input == 'r' || input == 'r') && ((player1.getLevel() >= 3) || (Player_Choice == 'M')))
            {
                refresh();
                interface.clearLower();
                combat1.playerDirMagicAtk(currentFloor, player1, enemyArray);
            }

            // Fire Arrows
            if (input == 'g' || input == 'G')
            {
                erase();
                refresh();
                combat1.playerArrowAtk(currentFloor, player1, enemyArray);
            }
            // Help Screen
            if (input == 'h' || input == 'H')
            {
                nocbreak();
                interface.drawHelp(player1);
                erase();
                refresh();
            }


            // Inventory Screen
            if (input == 'i' || input == 'I')
            {
                nocbreak();
                erase();
                refresh();
                player1.printEquipped();

                toEquip = player1.playerInventory.print();
                if (toEquip != 99)
                    player1.equipItem(toEquip);

                erase();
                refresh();
            }
            // save game
            if (input == 's' || input == 'S') {
                // get values to update database
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
                string type = sql.convertInt(player1.getType());
                string arrow = sql.convertInt(player1.getArrows());
                // update the database
                sql.dbCommand("UPDATE attributes SET health = "+string(health)+", damage = "+string(damage)+", defence = "+string(defence)+", level = "+string(level)+", health_cap = "+string(health_cap)+", magicAmount = "+string(magicAmount)+", magicAmount_cap = "+string(magicAmount_cap)+", magicPower = "+string(magicPower)+", magicDefence = "+string(magicDefence)+", critical = "+string(critical)+", evasion = "+string(evasion)+", experience = "+string(experience)+", experience_cap = "+string(experience_cap)+", type = "+string(type)+", arrow = "+string(arrow)+" WHERE pid = '"+userid+"';");
            }

            // Death Test
            if (player1.getHealth() < 1)
            {
                printDefeat();
                printw("  You were killed!! How embarrasing...\n Game Over!! \n Press any key to exit...");
                getch();
                exit(1);
            }

            // Win Test
            if (currentFloor -> getNumEnemies() == 0 && currentFloor -> getFloorLevel() == LAST_FLOOR)
            {
                printVictory();
                printw(" You are victorious! \n Game Over!! \n Press any key to exit...");
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
                    if (floorArray[i].tileArray[x][y].hasEnemy() == 1)
                    {
                        enemyArray[counter].setCurrentFloorLevel(i+1);
                        enemyArray[counter].setCurrentX(x);
                        enemyArray[counter].setCurrentY(y);
                        counter++;
                    }

                    if (counter == 50)
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

    // Print the title screen.
    void printTitle()
    {
        ifstream title("title.txt");
        title.unsetf(ios_base::skipws);
        char temp;
        while(!title.eof())
        {
            title >> temp;
            cout << temp;
        }
        cout << endl;
    }

    // Print victory screen.
    void printVictory()
    {
        erase();
        ifstream victory("victory.txt");
        victory.unsetf(ios_base::skipws);
        char temp;
        while(!victory.eof())
        {
            victory >> temp;
            addch(temp);
        }
        addch('\n');
    }

    // Print game over screen.
    void printDefeat()
    {
        erase();
        ifstream defeat("defeat.txt");
        defeat.unsetf(ios_base::skipws);
        char temp;
        while(!defeat.eof())
        {
            defeat >> temp;
            addch(temp);
        }
        addch('\n');
    }
};

#endif
