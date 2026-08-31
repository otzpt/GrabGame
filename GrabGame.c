// KEEP UNUSED LIBRARIES FOR NOW THEY MIGHT BE NECESSARY
#include<ncurses.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

// macros / defines(defining colision etc)
#define MAX_X (GAME_WIDTH - 4 - 1)
#define GAME_WIDTH 30
#define GAME_HEIGHT 31
#define MAX_OBJECT 30

int PlatColision(int object_x[], int object_y[], int platform_x, int platform_y, int j);

// functions
void test_ground(int object_y[], int object_x[], int start_y, int start_x, int platform_x, int platform_y, int *objectGen)
{
    // this function generates the object '@'
    // and keeps track of how many objects are on screen
    // to avoid overflows;
    // every loop is one object
    for(int i = 0; i < MAX_OBJECT; i++) {
        // check for colison
        if(PlatColision(object_x, object_y, platform_x, platform_y, i)) {
            (*objectGen)--; // if theres a colision remove one to the tota ammount
        }
        // spawns object at a random delay
        if (*objectGen < MAX_OBJECT) {
            int delay = rand() % 201 + 100; // calculates a random delay between spawns
            object_x[i] = rand() % (GAME_WIDTH - 2) + 1; // generates object at random x position
            usleep(delay * 1000); // usleep is in micro seconds so *1000
            // generates the object and aupdates the counter
            mvaddch(start_y + object_y[i], start_x + object_x[i], '@');
            (*objectGen)++;
        } else {
            ;
        }
    }
}

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
    for (x = 0; x < GAME_WIDTH; x++) {
        mvaddch(start_y, start_x + x, '-'); // adds '-' at the top borders
        mvaddch(start_y + GAME_HEIGHT - 1, start_x + x, '-'); // adds '-' at bottom borders
    }
    for (y = 0; y < GAME_HEIGHT; y++) {
        // adds '|' to the sides
        mvaddch(start_y + y, start_x, '|');
        mvaddch(start_y + y, start_x + GAME_WIDTH - 1, '|');
    }
}

void Object_reset(int object_x[], int object_y[], int platform_x, int platform_y, int i) // dont be tricked by this function names it does more than the name sugests
{
    (object_y[i])++; // moves thee object down
    // resets to top
    if (PlatColision(object_x, object_y, platform_x, platform_y, i)) {
        object_y[i] = 1;
    }
    if (object_y[i] >= GAME_HEIGHT) {
        object_y[i] = 1;
    }
}

void Object_genaration(int object_y[], int object_x[], int start_y, int start_x, int platform_x, int platform_y, int *objectGen)
{
    // this function generates the object '@'
    // and keeps track of how many objects are on screen
    // to avoid overflows;
    // every loop is one object
    for(int i = 0; i < MAX_OBJECT; i++) {
        // check for colison
        if(PlatColision(object_x, object_y, platform_x, platform_y, i)) {
            (*objectGen)--; // if theres a colision remove one to the tota ammount
        }
        // spawns object at a random delay
        if (*objectGen < MAX_OBJECT) {
            int delay = rand() % 201 + 100; // calculates a random delay between spawns
            object_x[i] = rand() % (GAME_WIDTH - 2) + 1; // generates object at random x position
            usleep(delay * 1000); // usleep is in micro seconds so *1000
            // generates the object and aupdates the counter
            mvaddch(start_y + object_y[i], start_x + object_x[i], '@');
            (*objectGen)++;
        } else {
            ;
        }
    }
}

int PlatColision(int object_x[], int object_y[], int platform_x, int platform_y, int j)
{
    if (object_y[j] == platform_y && object_x[j] >= platform_x && object_x[j] < platform_x + 4) {
        return 1;
    }
    return 0;
}

int main(void) {
    int objectGen = 0;
    int j;
    int i;
    int x = (GAME_WIDTH - 4) / 2;
    int running = 1;
    int object_x[MAX_OBJECT], object_y[MAX_OBJECT], object_timer = 0; // objectC is short for object counter, counts how many @ are in screnn there is a cap of 10 @

    srand(time(NULL));

    for (int k = 0; k < MAX_OBJECT; k++) {
        object_y[k] = 1;
    }

    initscr();// init terminal src
    curs_set(0);// hides cursor

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    int y = GAME_HEIGHT - 2; // puts platform on MENU bottom

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
        // colision
        for(j = 0; j <= MAX_OBJECT - 1; j++) {
            if (PlatColision(object_x, object_y, x, y, j)) {
                object_y[j] = 1; // resets @ to the top if colision is detected with platform
            }
        }

        // to close the game only when user presses 'q'
        if (ch == 'q') {
            running = 0;
        }

        erase(); // erases the old screen

        borders(x, y, start_y, start_x);
        mvaddstr(start_y + y, start_x + x, "cccc"); // Draw "cccc" at the platform's position (x,y) plus the game's position (start_x,start_y)
        refresh(); // refreshes scree

        object_timer++;

        // faling object speed
        if (object_timer >= 20) {
            for (i = 0; i <= MAX_OBJECT - 1; i++) {
                Object_reset(object_x, object_y, x, y, i);
            }
            object_timer = 0;
        }

        Object_genaration(object_y, object_x, start_y, start_x, x, y, &objectGen);

        usleep(10000);
    }
    endwin();
    return 0;
}
