/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LF                   motor         20              
// LB                   motor         10              
// RF                   motor         11              
// RB                   motor         1               
// Controller1          controller                    
// LIFT                 motor         4               
// TILT                 motor         2               
// LI                   motor         9               
// RI                   motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "RobotCommands.h"

using namespace vex;

// A global instance of competition
competition Competition;

// A global instance of the robot
RobotCommands robot;

void pre_auton(void)
{
  // Initializing Robot Configuration
  vexcodeInit();
  printf("Code made by Ian Lansdowne, Team 2373R\n");
  printf("Battery Percentage: %-int%%", int (100 * Brain.Battery.voltage(vex::voltageUnits::volt) / 12.8));
  //Print brain artwork
  robot.print2373R();
  //reset motor encoders
  LIFT.setPosition(0, rotationUnits::deg);
  TILT.setPosition(0, rotationUnits::deg);
  //Must return from this function or the autonomous and usercontrol tasks will not be started
  return;
}

void autonomous(void)
{
  /*
  int autonPinConfig [2] = {Brain.ThreeWirePort.A.value(), Brain.ThreeWirePort.B.value()};
  if (autonPinConfig[0] == 0 && autonPinConfig[1] == 0)
  {
    //Red 1
    LIFT.rotateFor(forward, 5, rotationUnits::rev);
    LIFT.rotateFor(reverse, 5, rotationUnits::rev);
    LI.spin(forward, 200, velocityUnits::rpm);
    RI.spin(forward, 200, velocityUnits::rpm);
    robot.driveV2(13, 40);
    LI.stop(brakeType::hold);
    RI.stop(brakeType::hold);
    robot.turn(180, 25, true);
    robot.driveV2(13, 40);
    robot.turn(80, 25, false);
    robot.drive(4, 50);
    robot.tiltTray(true);
    LI.spin(forward, 200, velocityUnits::rpm);
    RI.spin(forward, 200, velocityUnits::rpm);
    robot.drive(-40, 10);
    robot.tiltTray(false);
    LI.stop(brakeType::coast);
    RI.stop(brakeType::coast);
  }
  else if (autonPinConfig[0] == 1 && autonPinConfig[1] == 0)
  {
    //Blue 1
    LIFT.rotateFor(forward, 5, rotationUnits::rev);
    LIFT.rotateFor(reverse, 5, rotationUnits::rev);
    LI.spin(forward, 200, velocityUnits::rpm);
    RI.spin(forward, 200, velocityUnits::rpm);
    robot.driveV2(13, 40);
    LI.stop(brakeType::hold);
    RI.stop(brakeType::hold);
    robot.turn(180, 25, false);
    robot.driveV2(13, 40);
    robot.turn(80, 25, true);
    robot.drive(4, 50);
    robot.tiltTray(true);
    LI.spin(forward, 200, velocityUnits::rpm);
    RI.spin(forward, 200, velocityUnits::rpm);
    robot.drive(-40, 10);
    robot.tiltTray(false);
    LI.stop(brakeType::coast);
    RI.stop(brakeType::coast);
  }
  else if (autonPinConfig[0] == 0 && autonPinConfig[1] == 1)
  {
    
  }
  else if (autonPinConfig[0] == 1 && autonPinConfig[1] == 1)
  {
    
  }
  */
}

void usercontrol(void)
{
  //bool tiltUp = false;
  while (true)
  {
    printf("user control started\n");
    int8_t speed;
    while (true) {
      //Slow down button
      if (Controller1.ButtonA.pressing())
      {
        speed = 4;
      }
      else
      {
        speed = 1;
      }

      //Intake
      if (Controller1.ButtonR1.pressing())
      {
        LI.spin(forward, 200, velocityUnits::rpm);
        RI.spin(forward, 200, velocityUnits::rpm);
      }
      else if (Controller1.ButtonR2.pressing())
      {
        LI.spin(reverse, 200, velocityUnits::rpm);
        RI.spin(reverse, 200, velocityUnits::rpm);
      }
      else
      {
        LI.stop(brakeType::hold);
        RI.stop(brakeType::hold);
      }

      //Lift
      if (Controller1.ButtonUp.pressing())
      {
        LIFT.spin(forward, 100, velocityUnits::rpm);
      }
      else if (Controller1.ButtonDown.pressing())
      {
        LIFT.spin(reverse, 100, velocityUnits::rpm);
      }
      else
      {
        LIFT.stop(brakeType::hold);
      }

      //Tilt
      if(Controller1.ButtonL1.pressing())
      {
        TILT.spin(forward, 150, velocityUnits::rpm);
      }
      else if(Controller1.ButtonL2.pressing())
      {
        TILT.spin(reverse, 150, velocityUnits::rpm);
      }
      else
      {
        TILT.stop(brakeType::hold);
      }

      LF.spin(vex::directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value()/* - Controller1.Axis4.value()*/)/speed, vex::velocityUnits::pct); //(Axis3+Axis1)/2
      LB.spin(vex::directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value()/* + Controller1.Axis4.value()*/)/speed, vex::velocityUnits::pct); //(Axis3+Axis1)/2
      RF.spin(vex::directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value()/* + Controller1.Axis4.value()*/)/speed, vex::velocityUnits::pct); //(Axis3-Axis1)/2        
      RB.spin(vex::directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value()/* - Controller1.Axis4.value()*/)/speed, vex::velocityUnits::pct); //(Axis3-Axis1)/2
      //printf("Axis 1 = %ld\n", Controller.Axis1.value());
      vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
    }
  }
}

int main()
{
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}
