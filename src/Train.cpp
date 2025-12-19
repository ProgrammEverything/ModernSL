#include "Train.h"
#include "assets.h"
#include "consts.h"
#include "glob_enums.h"
#include "ncurses.h"
#include <iostream>
#include <unistd.h>
#include <array>
#include <cstring>
Train::Train(Layout calc_layout, TrainParameters params)
    : m_calc_layout(calc_layout), m_params(params)
{
}
int my_mvaddstr(int y, int x, const char *str)
{
    if (str == nullptr) return ERR;

    // skip leading off-screen chars
    while (x < 0) {
        x++;
        str++;
        if (*str == '\0') {
            // nothing visible
            return ERR;
        }
    }

    // draw until terminator or error
    while (*str != '\0') {
        if (mvaddch(y, x, *str) == ERR) {
            return ERR;
        }
        str++;
        x++;
    }
    return OK;
}

int Train::Draw(int frame, const char* message, TrainDrawingInformation info)
{
    
    if (DrawBody(m_calc_layout.getXPos(), m_calc_layout.getYPos(), frame, info) == ERR) {
        return ERR;
    }
    
    if (info.draw_tracks) {
        if (DrawTracks(m_calc_layout.getXPos(), m_calc_layout.getYPos()) == ERR) {
        }
    } else {
        ClearTracks(m_calc_layout.getXPos(), m_calc_layout.getYPos());
    }

    if (DrawMessage(m_calc_layout.getXPos(), m_calc_layout.getYPos(), message) == ERR) {
        return ERR;
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
    
    if (!drawInfo.draw_extended && draw_x < -LOGOLENGTH - (1 + drawInfo.tile_drawing_offset * 3) )  return ERR;
    if (drawInfo.draw_extended && draw_x < -LOGOLENGTH*4 - drawInfo.tile_drawing_offset*15 - 1 ) return ERR;
    
    int y = (cur_line / 2) - (LOGOHEIGHT / 2);

    // choose a pattern based on frame to animate wheels; tweak divisor to change speed
    int pat = (frame / drawInfo.wheels_speed) % LOGOPATTERNS;
    if (pat < 0) pat += LOGOPATTERNS;

    for (int lvl = 0; lvl <= LOGOHEIGHT; lvl++) {
        
        my_mvaddstr(y + lvl, draw_x,
            train_texture.at(pat).at(lvl));
        my_mvaddstr(y + lvl , draw_x + 21 + drawInfo.tile_drawing_offset, coal[lvl]);
        my_mvaddstr(y + lvl , draw_x + 21*2 + drawInfo.tile_drawing_offset * 2, car.at(lvl));
        my_mvaddstr(y + lvl , draw_x + 21*3 + drawInfo.tile_drawing_offset * 3, car.at(lvl));
        if (drawInfo.draw_extended){
            my_mvaddstr(y + lvl , draw_x + 21*4 + drawInfo.tile_drawing_offset * 4, coal[lvl]);
            my_mvaddstr(y + lvl , draw_x + 21*5 + drawInfo.tile_drawing_offset * 5, car.at(lvl));
            my_mvaddstr(y + lvl , draw_x + 21*6 + drawInfo.tile_drawing_offset * 6, car.at(lvl));
            my_mvaddstr(y + lvl , draw_x + 21*7 + drawInfo.tile_drawing_offset * 7, coal[lvl]);
            my_mvaddstr(y + lvl , draw_x + 21*8 + drawInfo.tile_drawing_offset * 8, car.at(lvl));
            my_mvaddstr(y + lvl , draw_x + 21*9 + drawInfo.tile_drawing_offset * 9, car.at(lvl));
            my_mvaddstr(y + lvl , draw_x + 21*10+ drawInfo.tile_drawing_offset * 10, coal[lvl]);
            my_mvaddstr(y + lvl , draw_x + 21*11+ drawInfo.tile_drawing_offset * 11, car.at(lvl));
            my_mvaddstr(y + lvl , draw_x + 21*12+ drawInfo.tile_drawing_offset * 12, car.at(lvl));
            my_mvaddstr(y + lvl , draw_x + 21*13+ drawInfo.tile_drawing_offset * 13, coal[lvl]);
            my_mvaddstr(y + lvl , draw_x + 21*14+ drawInfo.tile_drawing_offset * 14, car.at(lvl));
            my_mvaddstr(y + lvl , draw_x + 21*15+ drawInfo.tile_drawing_offset * 15, car.at(lvl));
        }
    }
    // enable smoke drawing using the per-frame draw_x
    // DrawSmoke(y - 1, draw_x + LOGOFUNNEL);
    return OK;
}
int Train::DrawTracks(int x_pos, int cur_line)
{
    int y = (cur_line / 2) - (LOGOHEIGHT / 2);

    for (int x=0; x<x_pos; x++){
        my_mvaddstr(y + LOGOHEIGHT, x, "-");
    }
    return OK;
}
int Train::ClearTracks(int x_pos, int cur_line)
{
    int y = (cur_line / 2) - (LOGOHEIGHT / 2);
    // erase the same horizontal region DrawTracks would have written to
    for (int x = 0; x < x_pos; ++x) {
        my_mvaddstr(y + LOGOHEIGHT, x, " ");
    }
    return OK;
}
int Train::DrawMessage(int x_pos, int cur_line, const char *message)
{
    static int last_lines = 0;

    // calculate base line for messages (same as before)
    int y = (cur_line / 2) - (LOGOHEIGHT / 2);

    // Prepare an erase buffer of MAX_WIDTH spaces
    char blanks[MAX_WIDTH + 1];
    std::memset(blanks, ' ', MAX_WIDTH);
    blanks[MAX_WIDTH] = '\0';

    // clear previous message lines
    for (int i = 0; i < last_lines; ++i) {
        int center = static_cast<int>(x_pos / 2);
        int erase_startx = center - static_cast<int>(MAX_WIDTH / 2);
        my_mvaddstr(y - 4 + i, erase_startx, blanks);
    }
    last_lines = 0;

    // nothing to draw
    if (message == nullptr) return OK;

    // draw the new message, honoring '\n' and wrapping to MAX_WIDTH
    size_t len = std::strlen(message);
    size_t off = 0;
    int line = 0;
    while (off < len) {
        // find next newline (or end)
        size_t nl = off;
        while (nl < len && message[nl] != '\n') ++nl;

        // segment [off, nl)
        size_t seglen = nl - off;
        size_t segoff = 0;
        while (segoff < seglen) {
            size_t take = (seglen - segoff > (size_t)MAX_WIDTH) ? MAX_WIDTH : (seglen - segoff);
            char buf[MAX_WIDTH + 1];
            std::memcpy(buf, message + off + segoff, take);
            buf[take] = '\0';

            int startx = static_cast<int>(x_pos / 2) - static_cast<int>(take) / 2;
            my_mvaddstr(y - 4 + line, startx, buf);

            segoff += take;
            ++line;
        }

        // skip the newline if present
        off = nl;
        if (off < len && message[off] == '\n') ++off;
    }

    last_lines = line;
    return OK;
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