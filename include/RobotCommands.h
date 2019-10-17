#ifndef RC_INT
#define RC_INT

#include "vex.h"
class RobotCommands
{
  public:
  const float wheelDiameter = 4.0;
  const double pi = atan(1)*4;
  const double wheelCircumferenceInches = pi * wheelDiameter;
  const double wheelCircumferenceMeters = wheelCircumferenceInches * 0.0254;
  const float robotWidth = 9.0;
  const float robotLength = 9.5;
  const double turnRadius = sqrt((robotLength/2 * robotLength/2) + (robotWidth/2 * robotWidth/2));

  void turn(double degrees, double velocity, bool turnRight);
  void drive (double velocity, double inches);
  void driveV2 (double inches, double rpm);
  void stop (vex::brakeType brake);
  void tiltTray (bool up);
  void print2373R();
};

#endif