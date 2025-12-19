#include <ncurses.h>
#include "Train.h"
#include <format>
#include <iostream>
#include <print>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
int main(){
    initscr();

    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    Train t{};

    while (true){
    for (int x = COLS - 1; ; --x) {
        if (t.DrawBody(x) == ERR) break;
        getch();
        refresh();
        usleep(5000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
}
    
    endwin();
}