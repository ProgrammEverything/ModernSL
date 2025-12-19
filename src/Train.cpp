#include "Train.h"
#include "assets.h"
#include "glob_enums.h"
#include "ncurses.h"
#include <iostream>
#include <unistd.h>
#include <array>
Train::Train(Layout calc_layout)
    : m_calc_layout(calc_layout)
{
}
int my_mvaddstr(int y, int x, const char *str)
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

int Train::Draw(int frame, TrainDrawingInformation info)
{

    if (DrawBody( m_calc_layout.getXPos(),m_calc_layout.getYPos(),  frame, info) == ERR) return ERR ;
    if (info.draw_tracks){ 
    if (DrawTracks(m_calc_layout.getXPos(), m_calc_layout.getYPos()) == ERR) {
        return ERR;
    }
    }
    return OK;
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
int Train::DrawBody(int x_pos, int cur_line, int frame, TrainDrawingInformation drawInfo)
{
    
    static std::array<std::array<const char*, LOGOHEIGHT + 1>, LOGOPATTERNS> train_texture
    = {{
        {{ LOGO1, LOGO2, LOGO3, LOGO4, LWHL11, LWHL12, DELLN }},
        {{ LOGO1, LOGO2, LOGO3, LOGO4, LWHL21, LWHL22, DELLN }},
        {{ LOGO1, LOGO2, LOGO3, LOGO4, LWHL31, LWHL32, DELLN }},
        {{ LOGO1, LOGO2, LOGO3, LOGO4, LWHL41, LWHL42, DELLN }},
        {{ LOGO1, LOGO2, LOGO3, LOGO4, LWHL51, LWHL52, DELLN }},
        {{ LOGO1, LOGO2, LOGO3, LOGO4, LWHL61, LWHL62, DELLN }}
      }};
    std::array<const char*, LOGOHEIGHT+1> coal
        = {LCOAL1, LCOAL2, LCOAL3, LCOAL4, LCOAL5, LCOAL6, DELLN};

    static std::array<const char*, LOGOHEIGHT + 1> car
        = {LCAR1, LCAR2, LCAR3, LCAR4, LCAR5, LCAR6, DELLN};

    // int y, py1 = 0, py2 = 0, py3 = 0;

    // compute the on-screen x for this frame (start at x_pos, move left as frame increases)
    int draw_x = x_pos - frame;
    // fully off-screen to the left?
    if (draw_x < -LOGOLENGTH - (1 + drawInfo.tile_drawing_offset * 3) )  return ERR;

    int y = (cur_line / 2) - (LOGOHEIGHT / 2);

    // choose a pattern based on frame to animate wheels; tweak divisor to change speed
    int pat = (frame / drawInfo.wheels_speed) % LOGOPATTERNS;
    if (pat < 0) pat += LOGOPATTERNS;

    for (int lvl = 0; lvl <= LOGOHEIGHT; lvl++) {
        
        my_mvaddstr(y + lvl, draw_x,
            train_texture.at(pat).at(lvl));
        my_mvaddstr(y + lvl , draw_x + 21 + drawInfo.tile_drawing_offset, coal[lvl]);
        my_mvaddstr(y + lvl , draw_x + 42 + drawInfo.tile_drawing_offset * 2, car.at(lvl));

        if (my_mvaddstr(y + lvl , draw_x + 63 + drawInfo.tile_drawing_offset * 3, car.at(lvl))){
        }
    }
    // enable smoke drawing using the per-frame draw_x
    // DrawSmoke(y - 1, draw_x + LOGOFUNNEL);
    return OK;
}
int Train::DrawTracks(int x_pos, int cur_line)
{
    int y = (cur_line / 2) - (LOGOHEIGHT / 2);

    for (int x=0; x<=x_pos; x++){
        my_mvaddstr(y + LOGOHEIGHT, x, "-");
    }
    return 0;
}
int Train::DrawSmoke(int y_pos, int x_pos)
{
    constexpr int SMOKEPTNS = 16;
    static const char *Smokes[2][SMOKEPTNS]
        = {{"(   )", "(    )", "(    )", "(   )", "(  )",
            "(  )" , "( )"   , "( )"   , "()"   , "()"  ,
            "O"    , "O"     , "O"     , "O"    , "O"   ,
            " "                                          },
           {"(@@@)", "(@@@@)", "(@@@@)", "(@@@)", "(@@)",
            "(@@)" , "(@)"   , "(@)"   , "@@"   , "@@"  ,
            "@"    , "@"     , "@"     , "@"    , "@"   ,
            " "                                          }};
    if (x_pos % 4 == 0){
        Smoke smk;
        smk.gen_random(y_pos, x_pos);
        my_mvaddstr(smk.y + 4, smk.x + 4, Smokes[1][smk.kind]);
    }
    return 0;
}