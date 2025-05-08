#pragma once
#include "vex.h"
//24
//enum CLAWSTATES {START = 0, INTAKE = 75, SECOND = 100, SECOND2 = 60, THIRD = 160, PASSIVE = 91, TOP = 220, GRABTOP = 220, ALLIANCE = 475, WALL = 647, BOTTOM = 25, SOMTHING = 120};

//15
enum CLAWSTATES {START = 0, INTAKE = 65, SECOND = 100, SECOND2 = 60, THIRD = 150, PASSIVE = 81, TOP = 225, GRABTOP = 220, ALLIANCE = 475, WALL = 647, BOTTOM = 25, SOMTHING = 120};


class ClawMech
{
    private:

        CLAWSTATES currentState = START;
        motor_group lift;
        float kp, ki, kd, starti, settle_error, settle_time, timeout;

    public:

        float maxVoltage = 12;

        led grab;

        ClawMech(motor_group lift, led grab, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);

        CLAWSTATES getCurrentState();
        void setCurrentState(CLAWSTATES state);

        void moveTo(CLAWSTATES state);
        void setTimeout(float timeout);
};