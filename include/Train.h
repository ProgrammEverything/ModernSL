#pragma once
#include "glob_enums.h"

class Train {
public:
    Train(TerminalSize termSize, Layout calc_layout);

    int Draw(int delay);
    int DrawBody(int x_pos, int cur_line, int frame);
    int DrawSmoke(int y_pos, int x_pos);

private:
    TrainParameters m_params{};
    TerminalSize m_termSize{};
    Layout m_calc_layout;
};