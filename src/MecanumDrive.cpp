#include "Robot.h"

void MecanumDrive::driveBase()
{
  //FB, RL, Turn
  LF.spin(vex::directionType::fwd, ControllerPtr->Axis3.value() - ControllerPtr->Axis4.value() - ControllerPtr->Axis1.value(), vex::velocityUnits::pct);
  LB.spin(vex::directionType::fwd, ControllerPtr->Axis3.value() - ControllerPtr->Axis4.value() + ControllerPtr->Axis1.value(), vex::velocityUnits::pct);
  RF.spin(vex::directionType::fwd, ControllerPtr->Axis3.value() + ControllerPtr->Axis4.value() + ControllerPtr->Axis1.value(), vex::velocityUnits::pct);
  RB.spin(vex::directionType::fwd, ControllerPtr->Axis3.value() + ControllerPtr->Axis4.value() - ControllerPtr->Axis1.value(), vex::velocityUnits::pct);
}

//Dunno if this is going to work...
void MecanumDrive::drive(double inches, double velocity, double degrees)
{
  printf("Driving %f inches at a speed of %f at %f degrees", inches, velocity, degrees);
  if(reversed){degrees += 180;}
  LF.startRotateFor(forward, inchesToRotations(inches) * sin(degrees), rotationUnits::rev, velocity * sin(degrees), velocityUnits::rpm);
  RF.startRotateFor(forward, inchesToRotations(inches) * cos(degrees), rotationUnits::rev, velocity * cos(degrees), velocityUnits::rpm);
  LB.startRotateFor(forward, inchesToRotations(inches) * cos(degrees), rotationUnits::rev, velocity * cos(degrees), velocityUnits::rpm);
  RB.rotateFor(forward, inchesToRotations(inches) * sin(degrees), rotationUnits::rev, velocity * sin(degrees), velocityUnits::rpm);
}

void MecanumDrive::driveTime(int time, double velocity, double degrees)
{
  //FIX XDRIVE
  printf("Driving for %d milliseconds at a speed of %f at %f degrees", time, velocity, degrees);
  //Currently waits for completion
  LF.spin(forward, velocity, velocityUnits::rpm);
  RF.spin(forward, velocity, velocityUnits::rpm);
  LB.spin(forward, velocity, velocityUnits::rpm);
  RB.spin(forward, velocity, velocityUnits::rpm);
  wait(time, msec);
  LF.stop();
  RF.stop();
  LB.stop();
  RB.stop();
}

void MecanumDrive::turn(double degrees, turnType direction, double velocity)
{
  calcTurnCircumference();
  switch (direction)
  {
    case turnType::right:
      printf("Turning right %f\370 at a speed of %f", degrees, velocity);
      LF.startRotateFor(forward, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      RF.startRotateFor(reverse, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      LB.startRotateFor(forward, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      RB.rotateFor(reverse, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
    break;
    case turnType::left:
      printf("Turning left %f\370 at a speed of %f", degrees, velocity);
      LF.startRotateFor(reverse, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      RF.startRotateFor(forward, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      LB.startRotateFor(reverse, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      RB.rotateFor(forward, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
    break;
  }
}