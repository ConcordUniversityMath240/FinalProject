/* curses */
#include <curses.h>
/* strings */
#include <string>
/* srand, rand */
#include <stdlib.h>

using namespace std;

int main()
{
/*
    SETUP
*/
    int ch;
    /* Start curses mode */
	initscr();
	/* Line buffering disabled	*/
	raw();
	/* We get KEYS*/
	keypad(stdscr, TRUE);
	/* Don't echo() while we do getch won't work otherwise */
	noecho();

	// generate map

	char board[10][10];
	int x,y;
	y = 10;
	x = 10;
	int player_x, player_y;
	player_x = 5;
	player_y = 5;

	for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            board[i][j] = '_';
            if (i == player_y && j == player_x) {
                board[i][j] = '@';
            }
            addch(board[i][j]);
        }
        addch('\n');
	}

	// game loop
	while(true) {
	ch = getch();
	addch(board[player_y][player_x] = '_');
    if (ch == KEY_UP) {
        player_y -= 1;
    }
    else if (ch == KEY_DOWN) {
        player_y += 1;
    }
    else if (ch == KEY_LEFT) {
        player_x -= 1;
    }
    else if (ch == KEY_RIGHT) {
        player_x += 1;
    }
    else {
        continue;
    }
	addch(board[player_y][player_x] = '@');
    clear();
    /* Print stuff */
	for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            addch(board[i][j]);
        }
        addch('\n');
	}
	refresh();
	}
    /* End curses mode */
	endwin();

	return 0;
}
