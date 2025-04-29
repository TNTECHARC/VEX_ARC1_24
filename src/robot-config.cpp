#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LLift = motor(PORT18, ratio18_1, true);
motor RLift = motor(PORT13, ratio18_1, false);
motor_group Lift = motor_group(LLift, RLift);

controller Controller1 = controller(primary);
led steak = led(Brain.ThreeWirePort.C);
motor L1 = motor(PORT20, ratio6_1, false);
motor L2 = motor(PORT10, ratio6_1, false);
motor L3 = motor(PORT19, ratio6_1, false);
motor L4 = motor(PORT9, ratio6_1, true);
motor R1 = motor(PORT11, ratio6_1, true);
motor R2 = motor(PORT1, ratio6_1, true);
motor R3 = motor(PORT12, ratio6_1, true);
motor R4 = motor(PORT2, ratio6_1, false);
motor Lin = motor(PORT8, ratio6_1, true);
motor Rin = motor(PORT3, ratio6_1, false);
motor string = motor(PORT15, ratio6_1, false);
motor_group intake = motor_group(Lin, Rin);
led mog = led(Brain.ThreeWirePort.A);
led rush = led(Brain.ThreeWirePort.H);
rotation inrot = rotation(PORT5,true);
led doinker = led(Brain.ThreeWirePort.D);

//index, red, green, blue, hangle, hdsat
aivision::colordesc Green = aivision::colordesc(1, 181, 203, 15, 10.00, 0.2);
aivision aiVision = aivision(PORT21);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}