#include "Robot.h"

void TankDrive::driveBase(driveType type)
{
  switch (type)
  {
    case Tank:
    LF.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    RF.spin(forward, ControllerPtr->Axis2.value(), velocityUnits::pct);
    LB.spin(forward, ControllerPtr->Axis3.value(), velocityUnits::pct);
    RB.spin(forward, ControllerPtr->Axis2.value(), velocityUnits::pct);
    break;

    case Arcade:
    LF.spin(forward, ControllerPtr->Axis3.value() + ControllerPtr->Axis4.value(), velocityUnits::pct);
    RF.spin(forward, ControllerPtr->Axis3.value() - ControllerPtr->Axis4.value(), velocityUnits::pct);
    LB.spin(forward, ControllerPtr->Axis3.value() + ControllerPtr->Axis4.value(), velocityUnits::pct);
    RB.spin(forward, ControllerPtr->Axis3.value() - ControllerPtr->Axis4.value(), velocityUnits::pct);
    break;
    
    case SplitArcade:
    LF.spin(forward, ControllerPtr->Axis3.value() + Controller1.Axis1.value(), velocityUnits::pct);
    RF.spin(forward, ControllerPtr->Axis3.value() - Controller1.Axis1.value(), velocityUnits::pct);
    LB.spin(forward, ControllerPtr->Axis3.value() + Controller1.Axis1.value(), velocityUnits::pct);
    RB.spin(forward, ControllerPtr->Axis3.value() - Controller1.Axis1.value(), velocityUnits::pct);
    break;

    default:break;
  };
}

void TankDrive::drive(double inches, double velocity)
{
  controllerPrint("Driving %.1f inches at a speed of %f", inches, velocity);
  LF.startRotateFor(forward, inchesToRotations(inches), rotationUnits::rev, velocity, velocityUnits::rpm);
  RF.startRotateFor(forward, inchesToRotations(inches), rotationUnits::rev, velocity, velocityUnits::rpm);
  LB.startRotateFor(forward, inchesToRotations(inches), rotationUnits::rev, velocity, velocityUnits::rpm);
  RB.rotateFor(forward, inchesToRotations(inches), rotationUnits::rev, velocity, velocityUnits::rpm);
}

void TankDrive::driveTime(int time, directionType direction, double velocity)
{
  controllerPrint("Driving for %d milliseconds at a speed of %.0f", time, velocity);
  LF.spin(direction, velocity, velocityUnits::rpm);
  RF.spin(direction, velocity, velocityUnits::rpm);
  LB.spin(direction, velocity, velocityUnits::rpm);
  RB.spin(direction, velocity, velocityUnits::rpm);
  wait(time, msec);
  LF.stop();
  RF.stop();
  LB.stop();
  RB.stop();
}

void TankDrive::turn(double degrees, turnType direction, double velocity)
{
  calcTurnCircumference();
  switch (direction)
  {
    case turnType::right:
      controllerPrint("Turning right %.0f\370 at a speed of %.0f", degrees, velocity);
      LF.startRotateFor(forward, inchesToRotations((degrees/360) * turnCircumference), rotationUnits::rev, velocity, velocityUnits::rpm);
      RF.startRotateFor(reverse, inchesToRotations((degrees/360) * turnCircumference), rotationUnits::rev, velocity, velocityUnits::rpm);
      //LM.startRotateFor(forward, inchesToRotations((degrees/360) * turnCircumference), rotationUnits::rev, velocity, velocityUnits::rpm);
      //RM.startRotateFor(reverse, inchesToRotations((degrees/360) * turnCircumference), rotationUnits::rev, velocity, velocityUnits::rpm);
      LB.startRotateFor(forward, inchesToRotations((degrees/360) * turnCircumference), rotationUnits::rev, velocity, velocityUnits::rpm);
      RB.rotateFor(reverse, inchesToRotations((degrees/360) * turnCircumference), rotationUnits::rev, velocity, velocityUnits::rpm);
    break;
    case turnType::left:
      controllerPrint("Turning left %f\370 at a speed of %f", degrees, velocity);
      LF.startRotateFor(reverse, (turnCircumference * degrees) / (PI * wheelDiameter * 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      RF.startRotateFor(forward, (turnCircumference * degrees) / (PI * wheelDiameter * 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      //LM.startRotateFor(reverse, (turnCircumference * degrees) / (PI * wheelDiameter * 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      //RM.startRotateFor(forward, (turnCircumference * degrees) / (PI * wheelDiameter * 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      LB.startRotateFor(reverse, (turnCircumference * degrees) / (PI * wheelDiameter * 360), rotationUnits::rev, velocity, velocityUnits::rpm);
      RB.rotateFor(forward, (turnCircumference * degrees) / (PI * wheelDiameter * 360), rotationUnits::rev, velocity, velocityUnits::rpm);
    break;
  }
}


void TankDrive::turnTo(double x, double y, double velocity)
{
  directionType direction = forward;
  if(y<0){direction = reverse;}
  //double center = ellipsePerimeter(x, y) / 4;
  double inner = ellipsePerimeter(x - (width / 2), y - (width / 2)) / 4;
  double outer = ellipsePerimeter(x + (width / 2), y + (width / 2)) / 4;
  
  //First Quadrant
  if(x>0)
  {
    LF.startRotateFor(direction, outer * wheelDiameter * PI, rotationUnits::rev, velocity, velocityUnits::rpm);
    LM.startRotateFor(direction, outer * wheelDiameter * PI, rotationUnits::rev, velocity, velocityUnits::rpm);
    //LB.startRotateFor(direction, outer * wheelDiameter * PI, rotationUnits::rev, velocity, velocityUnits::rpm);
    //RF.startRotateFor(direction, inner * wheelDiameter * PI, rotationUnits::rev, inner * velocity / outer, velocityUnits::rpm);
    RM.startRotateFor(direction, inner * wheelDiameter * PI, rotationUnits::rev, inner * velocity / outer, velocityUnits::rpm);
    RB.rotateFor(direction, inner * wheelDiameter * PI, rotationUnits::rev, inner * velocity / outer, velocityUnits::rpm);
  }
  //Second Quadrant
  else if (x<0)
  {
    LF.startRotateFor(direction, inner * wheelDiameter * PI, rotationUnits::rev, inner * velocity / outer, velocityUnits::rpm);
    LM.startRotateFor(direction, inner * wheelDiameter * PI, rotationUnits::rev, inner * velocity / outer, velocityUnits::rpm);
    //LB.startRotateFor(direction, inner * wheelDiameter * PI, rotationUnits::rev, inner * velocity / outer, velocityUnits::rpm);
    //RF.startRotateFor(direction, outer * wheelDiameter * PI, rotationUnits::rev, velocity, velocityUnits::rpm);
    RM.startRotateFor(direction, outer * wheelDiameter * PI, rotationUnits::rev, velocity, velocityUnits::rpm);
    RB.rotateFor(direction, outer * wheelDiameter * PI, rotationUnits::rev, velocity, velocityUnits::rpm);
  }
  else
  {
    drive(y, velocity);
  }
}