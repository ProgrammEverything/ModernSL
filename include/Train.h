#pragma once
#include "glob_enums.h"

class Train {
public:
    Train(Layout calc_layout, TrainParameters params);

    int Draw(int delay, const char* message, TrainDrawingInformation info);
    int DrawBody(int x_pos, int cur_line, int frame, TrainDrawingInformation drawInfo);
    int DrawTracks(int x_pos, int cur_line);
    int DrawMessage(int x_pos, int cur_line, const char* message);
    int DrawSmoke(int y_pos, int x_pos);
private:
    TrainParameters m_params;

    Layout m_calc_layout;
};