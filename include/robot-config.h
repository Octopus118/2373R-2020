using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftFront;
extern motor RightFront;
extern motor LeftBack;
extern motor RightBack;
extern controller Controller1;
extern motor I1;
extern motor T;
extern motor I2;
extern motor LIFT;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );