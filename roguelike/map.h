/************************************************
map.h - Map related classes header file.
      - Sector
      - Quadrant
      - Galaxy

Author: Derek Royse & Andy Pritt

Purpose: These classes store and print locational data.
*************************************************/
#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int LAST_FLOOR = 5;
const int XSIZE = 32;
const int YSIZE = 80;
const int MAX_NUM_ENEMIES = 10;
const int MAX_NUM_ITEMS = 2;

using namespace std;

/************************************************
Tile class

Member functions:
    Tile()
*************************************************/
class Tile
{
    private:
        bool isPlayer;
        bool isEnemy;
        bool isWall;
        bool isFloor;
        bool isVoid;
        bool isUpStairs;
        bool isDownStairs;
        bool isItem;
        bool isBoss;
    public:
        Tile()
        {
            isPlayer = 0;
            isEnemy = 0;
            isWall = 0;
            isFloor = 0;
            isVoid = 0;
            isDownStairs = 0;
            isUpStairs = 0;
            isItem = 0;
            isBoss = 0;
        }
        bool hasBoss()
        {
            return isBoss;
        }

        bool hasPlayer()
        {
            return isPlayer;
        }

        bool hasEnemy()
        {
            return isEnemy;
        }

        bool hasWall()
        {
            return isWall;
        }

        bool hasFloor()
        {
            return isFloor;
        }

        bool hasVoid()
        {
            return isVoid;
        }

        bool hasDownStairs()
        {
            return isDownStairs;
        }

        bool hasUpStairs()
        {
            return isUpStairs;
        }

        bool hasItem()
        {
            return isItem;
        }

        void setPlayer(int input)
        {
            isPlayer = input;
        }

        void setEnemy(int input)
        {
            isEnemy = input;
        }

        void setWall(int input)
        {
            isWall = input;
        }

        void setFloor(int input)
        {
            isFloor = input;
        }

        void setVoid(int input)
        {
            isVoid = input;
        }

        void setDownStairs(int input)
        {
            isDownStairs = input;
        }

        void setUpStairs(int input)
        {
            isUpStairs = input;
        }

        void setItem(int input)
        {
            isItem = input;
        }

        void setBoss(int input)
        {
            isBoss = input;
        }
};

/************************************************
Floor class

Member functions:
    initializeFloor()           Generates the structure of a floor from a
                                randomly selected text file.
    populateFloor()             Randomly places enemies and items on the floor.
    displayFloor()              Prints the floor to the screen.
    getNumEnemies()             Returns the number of living enemies on the current floor.
*************************************************/
class Floor
{
    private:
        int floorLevel;
    public:
        // An array of Tile objects.
        Tile tileArray[XSIZE][YSIZE];
        Floor* prev;
        Floor* next;

        Floor()
        {
            floorLevel = 0;
            prev = NULL;
            next = NULL;
        }

        void setFloorLevel(int input)
        {
           floorLevel = input;
        }

        int getFloorLevel()
        {
            return floorLevel;
        }

        void initializeFloor()
        {
            char test;
            // Random number between 1 and 3.
            // Update this later to be between 1 and (number of floors we decide on)
            int random = rand() % 3 + 1;

            // Choose a random text file to create the floor with.
            ifstream map1;
            if (random == 1)
                map1.open("map1.txt");
            else if (random == 2)
                map1.open("map2.txt");
            else if (random == 3)
                map1.open("map3.txt");
            map1.unsetf(ios_base::skipws);

            // Copy the text file's layout to the Floor's tileArray.
            for (int i = 0; i < XSIZE; i++)
                for (int j = 0; j < YSIZE; j++)
                {
                    map1 >> test;
                    if (test == ' ' || test == '$' || test == '#')
                        tileArray[i][j].setVoid(1);
                    else if (test == '@')
                    {
                        tileArray[i][j].setItem(1);
                        tileArray[i][j].setFloor(1);
                    }
                    else if (test == 'B' && floorLevel == LAST_FLOOR)
                    {
                        tileArray[i][j].setBoss(1);
                        tileArray[i][j].setEnemy(1);
                        tileArray[i][j].setFloor(1);
                    }
                    else if (test == 'B' && floorLevel != LAST_FLOOR)
                    {
                        tileArray[i][j].setFloor(1);
                    }
                    else if (test == '*')
                    {
                       tileArray[i][j].setWall(1);
                    }
                    else if (test == 'P')
                    {
                        tileArray[i][j].setPlayer(1);
                        tileArray[i][j].setFloor(1);
                    }
                    else if (test == 'D' && floorLevel != LAST_FLOOR)
                    {
                        tileArray[i][j].setDownStairs(1);
                        tileArray[i][j].setFloor(1);
                    }
                    else if (test == 'D' && floorLevel == LAST_FLOOR)
                        tileArray[i][j].setFloor(1);

                    else if (test == 'U' && floorLevel != 1)
                    {
                        tileArray[i][j].setUpStairs(1);
                        tileArray[i][j].setFloor(1);
                    }
                    else if (test == 'U' && floorLevel == 1)
                        tileArray[i][j].setFloor(1);

                    else if (test == '-')
                        tileArray[i][j].setFloor(1);
                }

                // Picks up carriage return at end of line.
                map1 >> test;
        }

        // Loop through the tileArray, displaying an appropriate symbol
        // for the content of each Tile.
        void displayFloor()
        {
            for (int i = 0; i < XSIZE; i++)
            {
                for (int j = 0; j < YSIZE; j++)
                {
                    if (tileArray[i][j].hasPlayer() == 1)
                        {
                            attron (COLOR_PAIR(4));
                            addch('P');
                        }
                    else if (tileArray[i][j].hasBoss() == 1)
                    {
                        attron (COLOR_PAIR(3));
                        addch('B');
                    }
                    else if (tileArray[i][j].hasDownStairs() == 1)
                    {
                            attron (COLOR_PAIR(6));
                            addch(287);
                    }

                    else if (tileArray[i][j].hasUpStairs() == 1)
                    {
                            attron (COLOR_PAIR(6));
                            addch(286);
                    }

                    else if (tileArray[i][j].hasEnemy() == 1)
                        {
                            attron (COLOR_PAIR(3));
                            addch('E');
                        }
                    else if (tileArray[i][j].hasWall() == 1)
                        {
                            attron (COLOR_PAIR(2));
                            addch('*');
                        }
                    else if (tileArray[i][j].hasItem() == 1)
                        {
                            attron (COLOR_PAIR(6));
                            addch('@');
                        }
                    else if (tileArray[i][j].hasFloor() == 1)
                        {
                        attron (COLOR_PAIR(1));
                        addch('-');
                        }
                    else if (tileArray[i][j].hasVoid() == 1)
                        addch(' ');
                    else
                        addch('\n');
                }
            }
            addch('\n');
        }
        // Places the player, items, and enemies on the floor.
        void populateFloor()
        {
            int counter = 0;

            // x, y range between 32 and 79.
            int x;
            int y;

            // Spawn enemies.
            while (counter < MAX_NUM_ENEMIES)
            {
                x = rand() % XSIZE;
                y = rand() % YSIZE;
                if(tileArray[x][y].hasFloor() == 1 &&
                   tileArray[x][y].hasUpStairs() == 0 &&
                   tileArray[x][y].hasDownStairs() == 0)
                {
                    tileArray[x][y].setEnemy(1);
                    counter++;
                }
                else
                {
                    x = rand() % XSIZE;
                    y = rand() % YSIZE;
                }
            }

            // Spawn items.
            counter = 0;
            while (counter < MAX_NUM_ITEMS)
            {
                x = rand() % XSIZE;
                y = rand() % YSIZE;
                if(tileArray[x][y].hasFloor() == 1 &&
                   tileArray[x][y].hasUpStairs() == 0 &&
                   tileArray[x][y].hasDownStairs() == 0)
                {
                    tileArray[x][y].setItem(1);
                    counter++;
                }
                else
                {
                    x = rand() % XSIZE;
                    y = rand() % YSIZE;
                }
            }

        }

        // Return the number of enemies on the floor.
        char getNumEnemies()
        {
            int counter = 0;
            for (int i = 0; i < XSIZE; i++)
                for (int j = 0; j < YSIZE; j++)
                    if (tileArray[i][j].hasEnemy() == 1)
                        counter++;

            if (counter < 0 || counter > 9)
                return '*';
            else
                return '0' + counter;
        }

};

#endif
