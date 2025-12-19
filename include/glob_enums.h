#pragma once

enum class TrainParameters {
    TRAIN_ACCIDENT,
    TRAIN_LOGO,
    TRAIN_FLY
};
struct Smoke {
        int y, x;
        int ptrn, kind;
};

struct TerminalSize {
    int rows;
    int cols;
};