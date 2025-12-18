#pragma once
#include "glob_enums.h"

class Train {
public:
    Train();

    int Draw();
    int DrawBody(int x);
    int DrawSmoke();

private:
    TrainParameters m_params{};
    TerminalSize m_termSize{};
};