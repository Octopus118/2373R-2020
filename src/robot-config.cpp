#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftFront = motor(PORT1, ratio18_1, false);
motor RightFront = motor(PORT10, ratio18_1, true);
motor LeftBack = motor(PORT11, ratio18_1, false);
motor RightBack = motor(PORT20, ratio18_1, true);
controller Controller1 = controller(primary);
motor I1 = motor(PORT9, ratio18_1, true);
motor T = motor(PORT12, ratio18_1, false);
motor I2 = motor(PORT4, ratio18_1, false);
motor LIFT = motor(PORT2, ratio18_1, true);
led LEDA = led(Brain.ThreeWirePort.A);
led LEDH = led(Brain.ThreeWirePort.H);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}