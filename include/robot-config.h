using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LF;
extern motor LB;
extern motor RF;
extern motor RB;
extern controller Controller1;
extern motor LIFT;
extern motor TILT;
extern motor LI;
extern motor RI;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );