#pragma once
#include <functional>
#include <random>
#include <iostream>
#include <assets.h>
#include "consts.h"
enum TrainParameters {
    TRAIN_DRAW_TRACKS=2,
    NON=0
};

struct Smoke {
    int y, x;
    int ptrn, kind;
    void gen_random(int act_y, int act_x){
        srand(NULL);
        y = act_y + rand() % 5;
        srand(NULL);
        x = rand();
        x = act_x + rand() % 5;
        kind=rand() % 16;

    }
};

struct TerminalSize {
    int line;
    int col;
    bool operator>=(const TerminalSize& other){
        return (this->line >= other.line || this->col >= other.col);
    }
    bool operator<(const TerminalSize& other){
        return (this->line < other.line || this->col < other.col);
    }
};

struct Layout {
    std::function<int(void)> getXPos;
    std::function<int(void)> getYPos;
};

struct TrainDrawingInformation {
    int wheels_speed=2;
    int tile_drawing_offset=0;
    bool draw_tracks=true;
    bool draw_extended=false;
};

// Tiles which are like plain times however animated (e.g. each frame has its own texture)
struct AnimatedTile {
    std::array<std::array<const char*, LOGOHEIGHT + 1>, LOGOPATTERNS> texture;  
};
// Tiles which are plain without much details - e.g. rendered per line
struct LineDepTile {
    std::array<const char*, LOGOHEIGHT+1> coal;
};
