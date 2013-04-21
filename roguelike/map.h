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

using namespace std;

const int XSIZE = 32;
const int YSIZE = 79;


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
    public:
        Tile()
        {
            isPlayer = 0;
            isEnemy = 0;
            isWall = 0;
            isFloor = 0;
            isVoid = 0;
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
    public:
        // An array of Tile objects.
        Tile tileArray[XSIZE][YSIZE];
        char test;

        void initializeFloor()
        {
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
                    else if (test == '*')
                        tileArray[i][j].setWall(1);
                    else if (test == '-')
                        tileArray[i][j].setFloor(1);
                }


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
                        addch('P');
                    else if (tileArray[i][j].hasEnemy() == 1)
                        addch('E');
                    else if (tileArray[i][j].hasWall() == 1)
                        addch('*');
                    else if (tileArray[i][j].hasFloor() == 1)
                        addch('-');
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
            int x = rand() % XSIZE;
            int y = rand() % YSIZE;

            // Spawn player
            while (counter < 1)
            {
                if(tileArray[x][y].hasFloor() == 1)
                {
                    tileArray[x][y].setPlayer(1);
                    counter++;
                }
                else
                {
                    x = rand() % XSIZE;
                    y = rand() % YSIZE;
                }
            }
            x = rand() % XSIZE;
            y = rand() % YSIZE;
            counter = 0;
            while (counter < 1)
            {
                if (tileArray[x][y].hasFloor() == 1)
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
