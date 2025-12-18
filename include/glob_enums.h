#pragma once
#include <functional>
#include <random>
#include <iostream>
enum class TrainParameters {
    TRAIN_ACCIDENT,
    TRAIN_LOGO,
    TRAIN_FLY
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
};

struct Layout {
    std::function<int(void)> getXPos;
    std::function<int(void)> getYPos;
};