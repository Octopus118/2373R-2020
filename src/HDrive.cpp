#include "Robot.h"

void HDrive::driveBase(driveType type/*, bool relative*/)
{
  switch (type)
  {
    case Tank:
    RF.spin(forward, ControllerPtr->Axis2.value(), velocityUnits::pct);
    RB.spin(forward, ControllerPtr->Axis2.value(), velocityUnits::pct);
    LF.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    LB.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    break;

    case Arcade:
    RF.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    RB.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    LF.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    LB.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    M.spin(forward, ControllerPtr->Axis4.value(), velocityUnits::pct);
    break;
    
    case SplitArcade:
    /*if (relative)
    {
      LF.spin(forward, (cos(ControllerPtr->Axis3.value() * 360 / 127) + ControllerPtr->Axis4.value() / 127) * 100, velocityUnits::pct);
      LB.spin(forward, (cos(ControllerPtr->Axis3.value() * 360 / 127) + ControllerPtr->Axis4.value() / 127) * 100, velocityUnits::pct);
      RF.spin(forward, (cos(ControllerPtr->Axis3.value() * 360 / 127) + ControllerPtr->Axis4.value() / 127) * 100, velocityUnits::pct);
      RB.spin(forward, (cos(ControllerPtr->Axis3.value() * 360 / 127) + ControllerPtr->Axis4.value() / 127) * 100, velocityUnits::pct);
      M.spin(forward, sin(ControllerPtr->Axis1.value() * 360 / 127) * 100, velocityUnits::pct);
    }
    else
    {
      LF.spin(forward, 100 * (ControllerPtr->Axis1.value() + ControllerPtr->Axis4.value()) / 127, velocityUnits::pct);
      LB.spin(forward, 100 * (ControllerPtr->Axis3.value() + ControllerPtr->Axis4.value()) / 127, velocityUnits::pct);
      RF.spin(forward, 100 * (ControllerPtr->Axis3.value() + ControllerPtr->Axis4.value()) / 127, velocityUnits::pct);
      RB.spin(forward, 100 * (ControllerPtr->Axis1.value() + ControllerPtr->Axis4.value()) / 127, velocityUnits::pct);
      M.spin(forward, (ControllerPtr->Axis1.value() * 360 / 127) * 100, velocityUnits::pct);
    }*/
    break;
  };
}
/*
void HDrive::drive(double inches, double velocity, double degrees)
{
  printf("Driving %f inches at a speed of %f at %f degrees", inches, velocity, degrees);
  F.startRotateFor(forward, inchesToRotations(inches) * sin(degrees), rotationUnits::rev, velocity * sin(degrees), velocityUnits::rpm);
  R.startRotateFor(forward, inchesToRotations(inches) * cos(degrees), rotationUnits::rev, velocity * cos(degrees), velocityUnits::rpm);
  L.startRotateFor(forward, inchesToRotations(inches) * cos(degrees), rotationUnits::rev, velocity * cos(degrees), velocityUnits::rpm);
  B.rotateFor(forward, inchesToRotations(inches) * sin(degrees), rotationUnits::rev, velocity * sin(degrees), velocityUnits::rpm);
}

void HDrive::driveTime(int time, double velocity, double degrees)
{
  printf("Driving for %d milliseconds at a speed of %f", time, velocity);
  //Currently waits for completion
  F.spin(forward, velocity, velocityUnits::rpm);
  R.spin(forward, velocity, velocityUnits::rpm);
  L.spin(forward, velocity, velocityUnits::rpm);
  B.spin(forward, velocity, velocityUnits::rpm);
  wait(time, msec);
  F.stop();
  R.stop();
  L.stop();
  B.stop();
}

void HDrive::turn(double degrees, turnType direction, double velocity)
{
  calcTurnCircumference();
  switch (direction)
  {
    case turnType::right:
      printf("Turning right %f\370 at a speed of %f", degrees, velocity);
      F.startRotateFor(forward, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      R.startRotateFor(reverse, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      L.startRotateFor(forward, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      B.rotateFor(reverse, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
    break;
    case turnType::left:
      printf("Turning left %f\370 at a speed of %f", degrees, velocity);
      F.startRotateFor(reverse, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      R.startRotateFor(forward, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      L.startRotateFor(reverse, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      B.rotateFor(forward, inchesToRotations((turnCircumference * degrees) / 360), rotationUnits::rev, velocity, velocityUnits::rpm);
    break;
  }
}*/