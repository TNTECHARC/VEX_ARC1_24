#pragma once
#include "vex.h"
enum CLAWSTATES {START = 0, INTAKE = 75, SECOND = 110, THIRD = 159, PASSIVE = 91, TOP = 200, GRABTOP = 220, ALLIANCE = 475};


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
};