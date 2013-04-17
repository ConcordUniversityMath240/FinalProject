/************************************************
Roguelike

Author:

Purpose:
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
