using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LLift;
extern motor RLift;
extern motor_group Lift;
extern controller Controller1;
extern led steak;
extern motor L1;
extern motor L2;
extern motor L3;
extern motor L4;
extern motor R1;
extern motor R2;
extern motor R3;
extern motor R4;
extern motor Lin;
extern motor Rin;
extern led mog;

enum CLAWSTATES {INTAKE = 10, SECOND = 123, THIRD = 160, PASSIVE = 80, WALL = 647, ALLIANCE = 580};

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );