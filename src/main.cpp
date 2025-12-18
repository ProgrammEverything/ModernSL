#include <ncurses.h>
#include "Train.h"
#include <format>
#include <iostream>
#include <print>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "assets.h"
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
    int i = 0;
    
    Layout func;
    int cols = COLS;
    int lns = LINES;
    func.getXPos = [&]() {
        return cols ;
        
    };
    func.getYPos = [&]() {

        return lns ;
    };
    Train t(TerminalSize{LINES, COLS}, func);
    
    while (true){
        i += 1;
        for (int i = 0; i<=cols; i++){
            t.Draw(i);
            mvcur(0, COLS, LINES, 0);
            refresh();
            getch();
            usleep(20000);
            
        }
        erase();
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
}