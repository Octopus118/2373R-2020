#pragma once
#include "vex.h"

class Robot
{
  public:
  const double PI = atan(1)*4;
  controller* ControllerPtr;
  
  template<typename arg, typename... args>
  void controllerPrint(arg mainArg, args... otherArgs)
  {
    ControllerPtr->Screen.clearLine(3);
    ControllerPtr->Screen.print(mainArg, otherArgs...);
  }
};

class Drive : public Robot
{
  public:
  enum driveType {Tank, SplitArcade, Arcade};
  double length = 0, width=0, wheelDiameter=4; // in inches
  protected:
  double turnCircumference;
  void calcTurnCircumference(){turnCircumference = PI * sqrt(pow(length, 2) + pow(width, 2));}
  double inchesToRotations(double inches){return inches / (PI * wheelDiameter);}
  double ellipsePerimeter(double a, double b){return 2 * PI * sqrt( (pow(a,2) + pow(b,2) / 2 ));}
};

class TankDrive : public Drive
{
  public:
  motor LF = NULL, RF = NULL, LM = NULL, RM = NULL, LB = NULL, RB = NULL;
  void drive(double inches, double velocity = 150);
  void driveTime(int time, directionType direction = forward, double velocity = 150);
  void turn(double degrees, turnType direction, double velocity = 50);
  void turnTo(double x, double y, double velocity = 150);
  void driveBase(driveType type);
};

class XDrive : public Drive
{
  public:
  motor F = NULL, L = NULL, R = NULL, B = NULL;
  void drive(double inches, double velocity = 150, double degrees = 0);
  void driveTime(int time, double velocity = 150, double degrees = 0);
  void turn(double degrees, turnType direction, double velocity = 50);
  void driveBase(driveType type, bool relative = false);
};

class MecanumDrive : public Drive
{
  public:
  motor LF = NULL, RF = NULL, LB = NULL, RB = NULL;
  bool reversed = false;
  void drive(double inches, double velocity = 150, double degrees = 0);
  void driveTime(int time, double velocity = 150, double degrees = 0);
  void turn(double degrees, turnType direction, double velocity = 50);
  void driveBase();
};

class HDrive : public Drive
{
  public:
  motor LF = NULL, RF = NULL, M = NULL, LB = NULL, RB = NULL;
  void drive(double inches, double velocity = 150, double degrees = 0);
  void driveTime(int time, double velocity = 150, double degrees = 0);
  void turn(double degrees, turnType direction, double velocity = 50);
  void driveBase(driveType type);
};

class Actuator : Robot
{
  public:
  motor m1 = NULL, m2 = NULL, m3 = NULL, m4 = NULL;
  void spinMechanism(controller::button forward, controller::button reverse, double velocity = 100);
  void calibrate() {m1.resetPosition(); m2.resetPosition(); m3.resetPosition(); m4.resetPosition();}
  void startSpin(double velocity = 100);
  void stop(brakeType brake = brakeType::hold);
};

class Tray : public Actuator
{
  bool trayUp = false;
  public:
  void toggleMechanism(controller::button button, double velocity = 75);
};

class Arm : public Actuator
{
  public:
  void beginningRaise(){m1.rotateFor(5, rotationUnits::deg);}
};