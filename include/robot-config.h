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
extern motor_group intake;
extern led mog;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );