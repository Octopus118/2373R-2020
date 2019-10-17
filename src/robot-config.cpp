#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LF = motor(PORT20, ratio18_1, false);
motor LB = motor(PORT10, ratio18_1, false);
motor RF = motor(PORT11, ratio18_1, true);
motor RB = motor(PORT1, ratio18_1, true);
controller Controller1 = controller(primary);
motor LIFT = motor(PORT4, ratio18_1, true);
motor TILT = motor(PORT2, ratio18_1, true);
motor LI = motor(PORT9, ratio18_1, true);
motor RI = motor(PORT3, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}