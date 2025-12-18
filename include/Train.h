#pragma once
#include "glob_enums.h"

class Train {
public:
    Train();

    int Draw();
    int DrawBody(int x_pos);
    int DrawSmoke(int y_pos, int x_pos);

private:
    TrainParameters m_params{};
    TerminalSize m_termSize{};
};