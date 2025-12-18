#include "Train.h"
#include "assets.h"
#include "glob_enums.h"
#include "ncurses.h"
#include <iostream>
int my_mvaddstr(int y, int x, char *str)
{
    while (x < 0) { 
        x++; str++; 
        if (*str == '\0')  return ERR;
    }
    while (*str != '\0'){
        if (mvaddch(y, x, *str) == ERR)  return ERR;
        str++, x++;
    }
    return OK;
}
Train::Train()
{
}
int Train::Draw()
{
    return 0;
}
/*
So how does it work?
Let's break down the function parameters and variables:
    x_pos is the current X Position to draw your train at.
    train_texture is a 2D array that holds different parts of the train's ASCII art
x_pos is checked to see if it's less than -LOGOLENGTH, which means the train has moved off-screen to the left, and the function returns ERR in that case.
y is calculated to center the train vertically in the terminal window.
A for loop iterates through each level (or row) of the train's height (from 0 to LOGOHEIGHT).
Inside the loop:

*/
int Train::DrawBody(int x_pos)
{
    static char *train_texture[LOGOPATTERNS][LOGOHEIGHT + 1]
        = {{LOGO1, LOGO2, LOGO3, LOGO4, LWHL11, LWHL12, DELLN},
           {LOGO1, LOGO2, LOGO3, LOGO4, LWHL21, LWHL22, DELLN},
           {LOGO1, LOGO2, LOGO3, LOGO4, LWHL31, LWHL32, DELLN},
           {LOGO1, LOGO2, LOGO3, LOGO4, LWHL41, LWHL42, DELLN},
           {LOGO1, LOGO2, LOGO3, LOGO4, LWHL51, LWHL52, DELLN},
           {LOGO1, LOGO2, LOGO3, LOGO4, LWHL61, LWHL62, DELLN}};

    static char *coal[LOGOHEIGHT + 1]
        = {LCOAL1, LCOAL2, LCOAL3, LCOAL4, LCOAL5, LCOAL6, DELLN};

    static char *car[LOGOHEIGHT + 1]
        = {LCAR1, LCAR2, LCAR3, LCAR4, LCAR5, LCAR6, DELLN};

    int y, py1 = 0, py2 = 0, py3 = 0;

    if (x_pos < - LOGOLENGTH)  return ERR;
    y = (LINES / 2) - (LOGOHEIGHT / 2);
    // y coordinate to draw the train on
    // LINES/2 => middle of terminal height
    // LOGOHEIGHT/2 => half of train height
    // Reminder: y - NUMBER makes the position go UP not down!
    for (int lvl = 0; lvl <= LOGOHEIGHT; lvl++) {
        my_mvaddstr(y + lvl, x_pos, 
            train_texture
            [((LOGOLENGTH + x_pos) / 3) %
                 LOGOPATTERNS][lvl]
        );
        my_mvaddstr(y + lvl + py1, x_pos + 21, coal[lvl]);
        my_mvaddstr(y + lvl + py2, x_pos + 42, car[lvl]);
        my_mvaddstr(y + lvl + py3, x_pos + 63, car[lvl]);
    }
    DrawSmoke(y - 1, x_pos + LOGOFUNNEL);
    return OK;
}
int Train::DrawSmoke(int y_pos, int x_pos)
{
    static Smoke S[100];
    const int SMOKEPTNS = 16;
    static int sum = 0;
    static char *Smoke[2][SMOKEPTNS]
        = {{"(   )", "(    )", "(    )", "(   )", "(  )",
            "(  )" , "( )"   , "( )"   , "()"   , "()"  ,
            "O"    , "O"     , "O"     , "O"    , "O"   ,
            " "                                          },
           {"(@@@)", "(@@@@)", "(@@@@)", "(@@@)", "(@@)",
            "(@@)" , "(@)"   , "(@)"   , "@@"   , "@@"  ,
            "@"    , "@"     , "@"     , "@"    , "@"   ,
            " "                                          }};
    static char *Eraser[SMOKEPTNS]
        =  {"     ", "      ", "      ", "     ", "    ",
            "    " , "   "   , "   "   , "  "   , "  "  ,
            " "    , " "     , " "     , " "    , " "   ,
            " "                                          };
    static int dy[SMOKEPTNS] = { 2,  1, 1, 1, 0, 0, 0, 0, 0, 0,
                                 0,  0, 0, 0, 0, 0             };
    static int dx[SMOKEPTNS] = {-2, -1, 0, 1, 1, 1, 1, 1, 2, 2,
                                 2,  2, 2, 3, 3, 3             };

    if (x_pos % 4 == 0) {
        for (int i = 0; i < sum; ++i) {
            my_mvaddstr(S[i].y, S[i].x, Eraser[S[i].ptrn]);
            S[i].y    -= dy[S[i].ptrn];
            S[i].x    += dx[S[i].ptrn];
            S[i].ptrn += (S[i].ptrn < SMOKEPTNS - 1) ? 1 : 0;
            my_mvaddstr(S[i].y, S[i].x, Smoke[S[i].kind][S[i].ptrn]);
        }
        my_mvaddstr(y_pos, x_pos, Smoke[sum % 2][0]);
        S[sum].y = y_pos;    S[sum].x = x_pos;
        S[sum].ptrn = 0; S[sum].kind = sum % 2;
        sum ++;
    }
    return 0;
}
