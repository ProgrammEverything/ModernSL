#pragma once
#include "glob_enums.h"

class Train {
public:
    Train(Layout calc_layout);

    int Draw(int delay, TrainDrawingInformation info);
    int DrawBody(int x_pos, int cur_line, int frame, TrainDrawingInformation drawInfo);
    int DrawTracks(int x_pos, int cur_line);
    int DrawSmoke(int y_pos, int x_pos);
private:
    TrainParameters m_params{};
    
    Layout m_calc_layout;
};