// you're coding while starting to feel like you've understood the meaning of life 
#include<stdio.h>
#include<ncurses.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

// structs
struct win {
  int heightW;
  int lenghtW;
  int startX;
  int startY;  
};

// fucntions
void PressedKey(int ch) {
    if (ch == KEY_RIGHT) {
      printw("you pressed the right arrow!!\n");

    } else {
      // i tried to print the key you pressed the
      // then decided to folow tuturial now it prints what
      // pressed in bold 
      printw("the pressed key is "); 
      attron(A_BOLD);
      printw("%c", ch);
      attroff(A_BOLD);
    }
}

void Window(void) {
  // my first ever window
  // kinda nervous
  char string[20] = "hello";
  int x = 5;
  int y = 5;
  char ch = '@';

  struct win win = {
    10, // height
    10, // lenght
    1, // starting x position
    1 // startin y position
  };
  
  WINDOW *ncwin = newwin(win.heightW, win.lenghtW, win.startX, win.startY);
    mvprintw(y, x, string);// move to y, x then print string
    wprintw(ncwin, string);  // prints with a window
    mvwprintw(ncwin, y, x, string); // move to y, x relative window
    wrefresh(ncwin); // refreshs the window or smt idk
    move(3,6);
    addch(ch | A_BOLD);
}

int main(void) {
  int ch;
  
  // starts the terminal thinggy
  initscr();
  raw(); // gets raw input; It puts the terminal into raw mode, meaning input is passed through with very little processing
  keypad(stdscr, TRUE); // allows use of arrows keys and 'F' keys and numpad keys etc you get it
  noecho(); /* Don't echo() while we do getch */

    //printw("hello this is my first use of ncurses\n");
    //printw("Press any key on your keyboard!!\n");
    //ch = getch(); // if we didnt use raw we would need to press enter to get to program

    Window();

  refresh(); // idk i just know you need to use it in the end in case you use printw
  getch(); // gets the character so the program closes
  endwin(); // ends the program withot this is like 90% chance it crashes

  return 0;
}
