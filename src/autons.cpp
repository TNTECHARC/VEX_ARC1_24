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

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
   // task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}

CLAWSTATES autonState = START;

void autonMoveClaw()
{
  
  CLAWSTATES temp = autonState;
  while(true)
  {
    claw.moveTo(autonState);

    temp = autonState;
    waitUntil(temp != autonState);
  }
}


void rushg()
{
  float startingPosition = chassis.get_left_position_in() + chassis.get_right_position_in();
  wait(100, msec);
  rush.set(true);
  // waitUntil(((chassis.get_left_position_in() + chassis.get_right_position_in() ) / 2) >= 20 + startingPosition);
  // rush.set(false);
}

void stringIntake()
{
  string.spinFor(forward, 0.75, sec, 100, velocityUnits::pct);
}

void blueRouteLeftGoal()
{
  thread autonClaw = thread(autonMoveClaw);
  thread rushMech = thread(rushg);
  thread stringSpin = thread(stringIntake);
  // Rush Mobile Goal
  chassis.drive_distance(24);
  rush.set(false);
  chassis.drive_distance(-30);
  rush.set(true);
  chassis.drive_distance(-5);
  rush.set(false);
  wait(100, msec);

  // Grab Mobile Goal
  chassis.turn_to_angle(180);
  wait(150, msec);
  chassis.drive_distance(-18);
  chassis.drive_distance(-10, 180, 3, 12);
  mog.set(true);
  wait(100, msec);

  // Pick up first ring
  chassis.drive_distance(10);
  chassis.turn_to_angle(32, 6);
  chassis.drive_distance(15, 32, 6, 12);
  steak.set(true);
  wait(200, msec);
  autonState = THIRD;
  chassis.drive_distance(7);
  
  steak.set(false);

}

void blue_route_skills(){
    
  
  chassis.set_heading(90);
  //claw grab
  steak.set(true);
  wait(.5, sec);
  
  //set claw to alliance
  autonState = ALLIANCE;
  chassis.drive_distance(2);
  chassis.turn_to_angle(270);
  chassis.drive_distance(6);
  //score
  chassis.drive_distance(-2);
  chassis.turn_to_angle(220);
  chassis.drive_distance(-51);
  //grab goal
  
  chassis.turn_to_angle(292);
  chassis.drive_distance(15);
  //spin intake
  chassis.turn_to_angle(310);
  chassis.drive_distance(25);
  //spin intake
  chassis.turn_to_angle(136);
  chassis.drive_distance(44);
  //spin intake
  chassis.turn_to_angle(135);
  chassis.drive_distance(30);
  //spin intake
  chassis.drive_distance(-14);
  chassis.turn_to_angle(123);
  chassis.drive_distance(16);
  //spin intake
  chassis.turn_to_angle(133);
  chassis.drive_distance(-75);
  //drop goal
 
  //STEP TWO 
 
  chassis.turn_to_angle(121);
  chassis.drive_distance(43);
  chassis.turn_to_angle(90);
  chassis.drive_distance(32);
  chassis.turn_to_angle(314);
  chassis.drive_distance(-12);
  //grab goal
  chassis.drive_distance(28);
  //claw grab
  //raise to wall
  chassis.turn_to_angle(0);
  chassis.drive_distance(12);
  //spin intake
  //score wall
  chassis.turn_to_angle(116);
  chassis.drive_distance(19);
  //spin intake
  chassis.turn_to_angle(96);
  chassis.drive_distance(25);
  //spin intake
  chassis.turn_to_angle(57);
  chassis.drive_distance(22);
  //spin intake
  chassis.drive_distance(-12);
  chassis.turn_to_angle(237);
  chassis.drive_distance(-10);
  //drop goal

}
