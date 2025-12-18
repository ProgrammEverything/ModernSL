#include <ncurses.h>
#include "Train.h"
#include <format>
#include <iostream>
#include <print>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
/*
Basic structure:
    The train is drawn using a for loop which loops through reverse of x.
        The reason for that is to make the train go towards the LEFT side of the screen. Since x-1 is going towards the left If we are
        Starting at the most highest COL in the terminal.

*/
int main(){
    initscr();

    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    Train t{};

    while (true){
    for (int x = COLS - 1;; x--) {
        
        if (t.DrawBody(x) == ERR) break;
        getch();
        refresh();
        usleep(50000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
}
    
    endwin();
}