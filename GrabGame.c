// KEEP UNUSED LIBRARIES FOR NOW THEY MIGHT BE NECESSARY
#include<stdio.h>
#include<ncurses.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

// macros / defines(defining colision etc)
#define MAX_X (GAME_WIDTH - 4 - 1)
#define GAME_WIDTH 30
#define GAME_HEIGHT 31
#define MAX_OBJECT 10

// functions
void PlatMove(int ch, int *x)
{
    if (ch == KEY_RIGHT && *x < MAX_X) {
        (*x)++;
    } else if (ch == KEY_LEFT && *x > 1) {
        (*x)--;
    } else {
        ; // in case user pesses up or down it does nothing
    }
}

void borders(int x, int y, int start_y, int start_x)
{
    for (int x = 0; x < GAME_WIDTH; x++) {
        mvaddch(start_y, start_x + x, '-'); // adds '-' at the top borders
        mvaddch(start_y + GAME_HEIGHT - 1, start_x + x, '-'); // adds '-' at bottom borders
    }
    for (int y = 0; y < GAME_HEIGHT; y++) {
        // adds '|' to the sides
        mvaddch(start_y + y, start_x, '|');
        mvaddch(start_y + y, start_x + GAME_WIDTH - 1, '|');
    }
}

void Object(int *y)
{
    (*y)++;

    if (*y >= GAME_HEIGHT) {
        *y = 1;
    }
}

int PlatColision(int object_x, int object_y, int platform_x, int platform_y)
{
    if (object_y == platform_y && object_x >= platform_x && object_x < platform_x + 4) {
        return 1;
    }
    return 0;
}

int main(void) {
    int x = (GAME_WIDTH - 4) / 2;
    int running = 1;
    int object_x[MAX_OBJECT], object_y[MAX_OBJECT], object_timer = 0, objectC = 1; // objectC is short for object counter, counts how many @ are in screnn there is a cap of 10 @

    srand(time(NULL));

    initscr();// init terminal src
    curs_set(0);// hides cursor

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    int y = GAME_HEIGHT - 2; // puts platform on MENU BOTTOM bottom

    // centers the game
    int start_x = (cols - GAME_WIDTH) / 2;
    int start_y = (rows - GAME_HEIGHT) / 2;

    raw(); // raw terminal input
    noecho();
    keypad(stdscr, TRUE); // allow arrow keys
    nodelay(stdscr, TRUE); // remove delay of waiting for user input

    while (running) {
        int ch = getch();

        PlatMove(ch, &x);
        if (PlatColision(object_x, object_y, x, y)) {
            object_y = 1; // resets @ to the top if colision is detected with platform
            object_x = rand() % (GAME_WIDTH - 2) + 1; // randomizes @ position
        }

        if (ch == 'q') {
            running = 0;
        }

        erase(); // erases the old screen

        borders(x, y, start_y, start_x);
        mvaddstr(start_y + y, start_x + x, "cccc"); // Draw "cccc" at the platform's position (x,y) plus the game's position (start_x,start_y)
        mvaddch(start_y + object_y, start_x + object_x, '@'); // draws the falling object
        refresh(); // refreshes scree

        object_timer++;

        if (object_timer >= 20) {
            Object(&object_y);
            object_timer = 0;
        }
        usleep(10000);
    }
    endwin();
    return 0;
}
