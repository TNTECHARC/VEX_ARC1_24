#include "claw.h"

ClawMech::ClawMech(motor_group lift, led grab, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout) :
    lift(lift),
    grab(grab),
    kp(kp),
    ki(ki),
    kd(kd),
    starti(starti),
    settle_error(settle_error),
    settle_time(settle_time),
    timeout(timeout)
{lift.resetPosition();}

CLAWSTATES ClawMech::getCurrentState()
{
    return currentState;
}

void ClawMech::setCurrentState(CLAWSTATES state)
{
    currentState = state;
}

void ClawMech::moveTo(CLAWSTATES state)
{
    PID clawPID(state, kp, ki, kd, starti, settle_error, settle_time, timeout);
    
    while (!clawPID.is_settled()) 
    {
        // Get the current position (this should come from a sensor, such as an encoder)
        double currentPosition = (LLift.position(deg) + RLift.position(deg))/2;

        // Calculate error
        double error = state - currentPosition;
        double correction = clawPID.compute(error);

        correction = clamp(correction, -maxVoltage, maxVoltage);

        // Apply correction to motors
        lift.spin(forward, correction, voltageUnits::volt);

        // Sleep to control loop rate
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Is running");
        wait(20, msec);
    }
    lift.stop(hold);
    currentState = state;
}

void ClawMech::setTimeout(float timeout)
{
    this->timeout = timeout;
}