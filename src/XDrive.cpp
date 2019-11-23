#include "Robot.h"

void XDrive::driveBase(driveType type, bool relative)
{
  switch (type)
  {
    case Tank:
    R.spin(forward, ControllerPtr->Axis2.value(), velocityUnits::pct);
    L.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    break;

    case Arcade:
    F.spin(forward, ControllerPtr->Axis4.value(), velocityUnits::pct);
    R.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    L.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    B.spin(forward, ControllerPtr->Axis4.value(), velocityUnits::pct);
    break;
    
    case SplitArcade:
    if (relative)
    {
      F.spin(forward, (sin(ControllerPtr->Axis1.value() * 360 / 127) + ControllerPtr->Axis4.value() / 127) * 100, velocityUnits::pct);
      R.spin(forward, (cos(ControllerPtr->Axis3.value() * 360 / 127) + ControllerPtr->Axis4.value() / 127) * 100, velocityUnits::pct);
      L.spin(forward, (cos(ControllerPtr->Axis3.value() * 360 / 127) + ControllerPtr->Axis4.value() / 127) * 100, velocityUnits::pct);
      B.spin(forward, (sin(ControllerPtr->Axis1.value() * 360 / 127) + ControllerPtr->Axis4.value() / 127) * 100, velocityUnits::pct);
    }
    else
    {
      F.spin(forward, 100 * (ControllerPtr->Axis1.value() + ControllerPtr->Axis4.value()) / 127, velocityUnits::pct);
      R.spin(forward, 100 * (ControllerPtr->Axis3.value() + ControllerPtr->Axis4.value()) / 127, velocityUnits::pct);
      L.spin(forward, 100 * (ControllerPtr->Axis3.value() + ControllerPtr->Axis4.value()) / 127, velocityUnits::pct);
      B.spin(forward, 100 * (ControllerPtr->Axis1.value() + ControllerPtr->Axis4.value()) / 127, velocityUnits::pct);
    }
    break;
  };
}

void XDrive::drive(double inches, double velocity, double degrees)
{
  printf("Driving %f inches at a speed of %f at %f degrees", inches, velocity, degrees);
  F.startRotateFor(forward, inchesToRotations(inches) * sin(degrees), rotationUnits::rev, velocity * sin(degrees), velocityUnits::rpm);
  R.startRotateFor(forward, inchesToRotations(inches) * cos(degrees), rotationUnits::rev, velocity * cos(degrees), velocityUnits::rpm);
  L.startRotateFor(forward, inchesToRotations(inches) * cos(degrees), rotationUnits::rev, velocity * cos(degrees), velocityUnits::rpm);
  B.rotateFor(forward, inchesToRotations(inches) * sin(degrees), rotationUnits::rev, velocity * sin(degrees), velocityUnits::rpm);
}

void XDrive::driveTime(int time, double velocity, double degrees)
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

void XDrive::turn(double degrees, turnType direction, double velocity)
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
}