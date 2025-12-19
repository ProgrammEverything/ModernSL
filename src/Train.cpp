#include "Train.h"
#include "assets.h"
#include "glob_enums.h"
#include "ncurses.h"
#include <iostream>
int my_mvaddstr(int y, int x, char *str)
{

    for ( ; x < 0; ++x, ++str)
        if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++str, ++x)
        if (mvaddch(y, x, *str) == ERR)  return ERR;
    return OK;
}
Train::Train()
{
}
int Train::Draw()
{
    DrawSmoke();
    return 0;
}
int Train::DrawBody(int x)
{
    static char *sl[LOGOPATTERNS][LOGOHEIGHT + 1]
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

    int i, y, py1 = 0, py2 = 0, py3 = 0;

    if (x < - LOGOLENGTH)  return ERR;
    y = LINES / 2 - 3;
    for (i = 0; i <= LOGOHEIGHT; ++i) {
        my_mvaddstr(y + i, x, sl[(LOGOLENGTH + x) / 3 % LOGOPATTERNS][i]);
        my_mvaddstr(y + i + py1, x + 21, coal[i]);
        my_mvaddstr(y + i + py2, x + 42, car[i]);
        my_mvaddstr(y + i + py3, x + 63, car[i]);
    }
    return OK;
}
int Train::DrawSmoke()
{
    // static Smoke S[100];
    // const int SMOKEPTNS = 16;
    // static int sum = 0;
    // static char *Smoke[2][SMOKEPTNS]
    //     = {{"(   )", "(    )", "(    )", "(   )", "(  )",
    //         "(  )" , "( )"   , "( )"   , "()"   , "()"  ,
    //         "O"    , "O"     , "O"     , "O"    , "O"   ,
    //         " "                                          },
    //        {"(@@@)", "(@@@@)", "(@@@@)", "(@@@)", "(@@)",
    //         "(@@)" , "(@)"   , "(@)"   , "@@"   , "@@"  ,
    //         "@"    , "@"     , "@"     , "@"    , "@"   ,
    //         " "                                          }};
    // static char *Eraser[SMOKEPTNS]
    //     =  {"     ", "      ", "      ", "     ", "    ",
    //         "    " , "   "   , "   "   , "  "   , "  "  ,
    //         " "    , " "     , " "     , " "    , " "   ,
    //         " "                                          };
    // static int dy[SMOKEPTNS] = { 2,  1, 1, 1, 0, 0, 0, 0, 0, 0,
    //                              0,  0, 0, 0, 0, 0             };
    // static int dx[SMOKEPTNS] = {-2, -1, 0, 1, 1, 1, 1, 1, 2, 2,
    //                              2,  2, 2, 3, 3, 3             };
    // int i;

    // if (x % 4 == 0) {
    //     for (i = 0; i < sum; ++i) {
    //         my_mvaddstr(S[i].y, S[i].x, Eraser[S[i].ptrn]);
    //         S[i].y    -= dy[S[i].ptrn];
    //         S[i].x    += dx[S[i].ptrn];
    //         S[i].ptrn += (S[i].ptrn < SMOKEPTNS - 1) ? 1 : 0;
    //         my_mvaddstr(S[i].y, S[i].x, Smoke[S[i].kind][S[i].ptrn]);
    //     }
    //     my_mvaddstr(y, x, Smoke[sum % 2][0]);
    //     S[sum].y = y;    S[sum].x = x;
    //     S[sum].ptrn = 0; S[sum].kind = sum % 2;
    //     sum ++;
    // }
    return 0;
}
