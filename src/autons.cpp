#include "vex.h"
/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
    chassis.set_drive_constants(12, 1.5, 0, 10, 0);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_turn_constants(10, .4, .03, 3, 15);
    chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_drive_exit_conditions(1.5, 50, 5000);
    chassis.set_turn_exit_conditions(1, 300, 3000);
    chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
    default_constants();
    chassis.heading_max_voltage = 10;
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
    chassis.boomerang_lead = .5;
    chassis.drive_min_voltage = 0;
}

CLAWSTATES autonState = START;

void autonMoveClaw()
{
    autonState = START;
    CLAWSTATES temp = START;
    while(true)
    {
        claw.moveTo(autonState);

        temp = autonState;
        waitUntil(temp != autonState);
    }
}

void initAutonThreads()
{
    thread autonClaw = thread(autonMoveClaw);
    thread intakeThread = thread(intakee);
}

// Score Goal in negative zone
void blue_Right()
{
    initAutonThreads();

    // Obtain Goal
    chassis.drive_distance(17);
    chassis.turn_to_angle(45);
    chassis.drive_distance(15);
    doinker.set(true);
    wait(300, msec);
    chassis.drive_distance(-19);
    doinker.set(false);
    wait(100, msec);
    chassis.turn_to_angle(215);
    wait(100, msec);
    chassis.drive_distance(-17, 215, 4, 4);
    wait(100, msec);
    mog.set(true);
    wait(500, msec);

    // Get First Ring
    chassis.turn_to_angle(135);
    autonState = INTAKE;
    chassis.drive_distance(10);
    intakeOn = true;
    chassis.drive_distance(5);
    intakeOn = false;

    // Second Ring
    chassis.turn_to_angle(40);
    chassis.drive_distance(12);
    doinker.set(true);
    wait(300, msec);
    chassis.drive_distance(-13);
    doinker.set(false);
    wait(100, msec);

    chassis.turn_to_angle(25);
    chassis.drive_distance(8);
    intakeOn = true;
    chassis.drive_distance(5);
    intakeOn = false;

    // Third Ring
    chassis.drive_distance(-1);
    chassis.turn_to_angle(270);
    chassis.drive_distance(20);
    intakeOn = true;
    chassis.drive_distance(6, 270, 4, 4);
    wait(100, msec);
    intakeOn = false;

    // Fourth Ring
    chassis.turn_to_angle(180);
    chassis.drive_distance(10);
    chassis.turn_to_angle(135);
    autonState = START;
    chassis.drive_distance(20);
    chassis.drive_distance(6, 135, 4, 4);
    steak.set(true);
    chassis.drive_distance(-8);
    autonState = THIRD;
    chassis.drive_distance(12);
    intakeOn = true;
    chassis.drive_distance(4, 135, 4, 4);
    intakeOn = false;

    // Drop current ring
    chassis.turn_to_angle(45);
    steak.set(false);
    wait(200, msec);
    chassis.turn_to_angle(130);

    // Edging the corner for enemy rings
    autonState = TOP;
    chassis.drive_distance(12, 130, 4, 4);
    autonState = GRABTOP;
    wait(100, msec);
    steak.set(true);
    wait(200, msec);
    chassis.drive_distance(-9);
    autonState = START;
    steak.set(false);
    autonState = INTAKE;
    intakeOn = true;
    wait(100, msec);
    intakeOn = false;

    autonState = SECOND;
    chassis.drive_distance(9, 130, 4, 4);
    steak.set(true);
    wait(300, msec);
    chassis.drive_distance(-9);
    autonState = START;
    steak.set(false);
    autonState = INTAKE;
    intakeOn = true;
    wait(100, msec);
    intakeOn = false;

}
