#include "vex.h"

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(L1,L2,L3,L4),

//Right Motors:
motor_group(R1,R2,R3,R4),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT4,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
2.5,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
1,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

ClawMech claw(motor_group(LLift, RLift), steak, 0.16, 0.1, 0.16, 0, 5, 100, 300);

int current_auton_selection = 0;
bool auto_started = false;
bool team_red = true;

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();
  LLift.setPosition(0,deg);
  RLift.setPosition(0,deg);
  Lift.setPosition(0,deg);
  inrot.setPosition(0,deg);
  chassis.Gyro.calibrate();
  waitUntil(!chassis.Gyro.isCalibrating());

  
}

/**
 * Auton function, which runs the selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */



void autonomous(void) {
  Goal_AI AI;

  if(!team_red) doinker.set(true);
  else doinker.set(false);  
  chassis.drive_distance(24);

  wait(2, sec);


  if(team_red)
  {
    //Red Team Auton
    switch (AI.find_Local_Goals_In_My_Area()) {
      case 0:
        // No Goals
        red_back_pos();
        break;
      case 1:
        // Only Left Goal
        red_back_pos();
        break;
      case 2:
        // Only Right Goal
        red_front_pos();
        break;
      case 3:
        // Both Goals
        red_front_pos();
        break;
    }
  }
  else
  {
    //Blue Team Auton
    switch (AI.find_Local_Goals_In_My_Area()) {
      case 0:
        // No Goals
        doinker.set(false);
        blue_back_neg();
        break;
      case 1:
        // Only Left Goal
        doinker.set(false);
        blue_middle_neg();
        break;
      case 2:
        // Only Right Goal
        doinker.set(false);
        blue_front_neg();
        break;
      case 3:
        // Both Goals
        doinker.set(false);
        blue_front_neg();
    }
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

bool canStopSpin = true;

void goToAlliance(){canStopSpin = false; claw.moveTo(ALLIANCE); canStopSpin = true;}

void goToDefault(){if(!Controller1.ButtonR1.pressing()){canStopSpin = false; claw.moveTo(PASSIVE); canStopSpin = true;}}
void spinIntake(){if(!Controller1.ButtonL1.pressing()){intakeOn = false;}else{intakeOn=true;}}

void goalClamp(){if(Controller1.ButtonL1.pressing() && Controller1.ButtonR1.pressing()) {mog.set(!mog.value()); if(mog.value()) Controller1.rumble("-");}}

void clampRing(){if(!Controller1.ButtonR1.pressing()) steak.set(!steak.value());}

void revIntake(){intake.spinFor(reverse, (78  /12 * 16 / 24) * 385, deg, 100, velocityUnits::pct);}

void movingClaw()
{
  while(1)
  {
    //Manual Lift Control
    if(Controller1.ButtonR1.pressing() && !Controller1.ButtonL1.pressing())
      Lift.spin(fwd, 12, volt);
    else if(Controller1.ButtonR2.pressing())
      Lift.spin(reverse, 12, volt);
    else if(canStopSpin)
      Lift.stop(hold);
  }
}

void usercontrol(void) {

  thread intakeThread = thread(intakee);
  thread moveClawLift = thread(movingClaw);

  claw.moveTo(START);
  

  // L Controls
  Controller1.ButtonL1.pressed(goToDefault);
  Controller1.ButtonL1.pressed(spinIntake);
  Controller1.ButtonL2.pressed(clampRing);

  // Goal Clamp
  Controller1.ButtonR1.pressed(goalClamp);
  Controller1.ButtonL1.pressed(goalClamp);

  // Alliance
  Controller1.ButtonA.pressed(goToAlliance);

  // Reverse Intake incase it gets stuck
  Controller1.ButtonDown.pressed(revIntake);


  steak.set(false);
  //isAutoRunning = false;

  while (1) {

    chassis.control_arcade();


    //Intake PID
    spinIntake();


    //Rush Mech Test
    if(Controller1.ButtonB.pressing())
    {
      doinker.set(true);
    }
    else
    {
      doinker.set(false);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.

    Brain.Screen.clearScreen();
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  inrot.resetPosition();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();


  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
