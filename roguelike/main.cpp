/************************************************
Roguelike

Authors: Derek Royse
         Ioan Istrate
         Jay Bingley
         Gary Danovich
         Andy Pritt
         Adam McCroskey
         Zach England

Purpose: A text-based Rogue-like game.
*************************************************/

#include "game.h"

using namespace std;

/*********************************************************************
Game begins here.
**********************************************************************/

int main()
{
    srand(time(NULL));
    Game mainGame;
    mainGame.run();
    return 0;
}
