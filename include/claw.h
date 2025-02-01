#pragma once
#include "vex.h"

enum CLAWSTATES {START = 0, INTAKE = 10, SECOND = 123, THIRD = 160, PASSIVE = 80, WALL = 647, ALLIANCE = 580};

class ClawMech
{
    private:

        CLAWSTATES currentState = START;
        motor_group lift;
        float kp, ki, kd, starti, settle_error, settle_time, timeout;

    public:

        led grab;

        ClawMech(motor_group lift, led grab, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);

        CLAWSTATES getCurrentState();
        void setCurrentState(CLAWSTATES state);

        void moveTo(CLAWSTATES state);
};