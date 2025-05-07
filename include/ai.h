#pragma once
#include "vex.h"


class Goal_AI
{
    private:
        
    int screenHeightDeadzone = 100;
    int goalScreenDivider = 160;

    int goalDistanceSensitivity = 68;

    public:
        Goal_AI();
        Goal_AI(int screenHeightDeadzone, int goalScreenDivider, int goalDistanceSensitivity);
        
        int find_Local_Goals_In_My_Area();
        int find_Local_Goals_In_My_Area(int iteration);
};