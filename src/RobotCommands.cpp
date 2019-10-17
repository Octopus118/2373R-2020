#include "RobotCommands.h"
#include "vex.h"

  void RobotCommands::turn(double degrees, double velocity, bool turnRight)
  {
    double rotations = (2 * pi * turnRadius * degrees) / (pi * wheelDiameter * 360);
    if (turnRight)
    {
      LF.startRotateFor(directionType::fwd, rotations, rotationUnits::rev, velocity, velocityUnits::rpm);
      LB.startRotateFor(directionType::fwd, rotations, rotationUnits::rev, velocity, velocityUnits::rpm);
      RF.startRotateFor(directionType::rev, rotations, rotationUnits::rev, velocity, velocityUnits::rpm);
      RB.rotateFor(directionType::rev, rotations, rotationUnits::rev, velocity, velocityUnits::rpm);
    }
    else
    {
      LF.startRotateFor(directionType::rev, rotations, rotationUnits::rev, velocity, velocityUnits::rpm);
      LB.startRotateFor(directionType::rev, rotations, rotationUnits::rev, velocity, velocityUnits::rpm);
      RF.startRotateFor(directionType::fwd, rotations, rotationUnits::rev, velocity, velocityUnits::rpm);
      RB.rotateFor(directionType::fwd, rotations, rotationUnits::rev, velocity, velocityUnits::rpm);
    }
    stop(brakeType::brake);
  }
  
  void RobotCommands::drive (double velocity, double inches)
  {
    vex::directionType direction;
    double rotationDegrees = inches*360/(wheelCircumferenceInches);
    if(velocity>=0)
    {
      direction = forward;
    }
    else
    {
      direction = reverse;
      velocity = -velocity;
    }
    LF.startRotateFor(direction, rotationDegrees, rotationUnits::deg, velocity, velocityUnits::dps);
    LB.startRotateFor(direction, rotationDegrees, rotationUnits::deg, velocity, velocityUnits::pct);
    RF.startRotateFor(direction, rotationDegrees, rotationUnits::deg, velocity, velocityUnits::pct);
    RB.rotateFor(direction, rotationDegrees, rotationUnits::deg, velocity, velocityUnits::pct);
  }

  void RobotCommands::driveV2 (double inches, double rpm)
  {
    vex::directionType direction;
    if(rpm>=0)
    {
      direction = forward;
    }
    else
    {
      direction = reverse;
      rpm = -rpm;
    }
    //in -> m
    double meters = inches * 0.0254;
    //rpm -> m/s
    double mps = wheelCircumferenceMeters*rpm/60;
    Brain.Screen.print(wheelCircumferenceMeters);
    //calculates time taken
    double seconds = meters/mps;
    //calculates accereration
    double acceleration = mps / seconds;
    //declare variable for the current velocity
    double currentMps;
    double currentRpm;

    LF.spin(direction);
    LB.spin(direction);
    RF.spin(direction);
    RB.spin(direction);
    Brain.resetTimer();
    //while the time is less that 1/6 of the total time, accelerate
    while(Brain.timer(timeUnits::msec) / 1000 <= seconds / 6)
    {
      currentMps = acceleration * Brain.timer(timeUnits::msec) / 1000;
      currentRpm = currentMps * 60 / wheelCircumferenceMeters;
      LF.setVelocity(currentRpm, velocityUnits::rpm);
      LB.setVelocity(currentRpm, velocityUnits::rpm);
      RF.setVelocity(currentRpm, velocityUnits::rpm);
      RB.setVelocity(currentRpm, velocityUnits::rpm);
    }
    //while the time is less that 5/6 of the total time, stay at a constant velocity
    while(Brain.timer(timeUnits::msec) / 1000 <= 5 * seconds / 6)
    {
      LF.setVelocity(rpm, velocityUnits::rpm);
      LB.setVelocity(rpm, velocityUnits::rpm);
      RF.setVelocity(rpm, velocityUnits::rpm);
      RB.setVelocity(rpm, velocityUnits::rpm);
    }
    //before the time is up, decelerate
    while (Brain.timer(timeUnits::msec) / 1000 <= seconds)
    {
      currentMps = (-acceleration * Brain.timer(timeUnits::msec) / 1000) + mps;
      currentRpm = currentMps * 60 / wheelCircumferenceMeters;
      LF.setVelocity(currentRpm, velocityUnits::rpm);
      LB.setVelocity(currentRpm, velocityUnits::rpm);
      RF.setVelocity(currentRpm, velocityUnits::rpm);
      RB.setVelocity(currentRpm, velocityUnits::rpm);
    }
    stop(brakeType::brake);
  }

  void RobotCommands::stop (vex::brakeType brake)
  {
    LF.stop(brake);
    LB.stop(brake);
    RF.stop(brake);
    RB.stop(brake);
  }

  void RobotCommands::tiltTray (bool up)
  {
    if (up)
    {
      stop(brake);
      TILT.rotateFor(forward, 1.75, rotationUnits::rev, 50, velocityUnits::rpm);
      TILT.stop(brakeType::hold);
    }
    else
    {
      TILT.startRotateTo(0, rotationUnits::deg);
    }
  }

  void RobotCommands::print2373R()
  {
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.newLine();
      Brain.Screen.newLine();
      Brain.Screen.print("    ____    ____    _____   ____     ______  ");
      Brain.Screen.setPenColor(vex::color::red);
      Brain.Screen.print("^");
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.newLine();
      Brain.Screen.print("   |__  )  |__  }  |___  ) |__  }   |____  }");
      Brain.Screen.setPenColor(vex::color::red);
      Brain.Screen.print("//");
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.newLine();
      Brain.Screen.print("     / /     _) |     / /    _) |    ____) |");
      Brain.Screen.setPenColor(vex::color::red);
      Brain.Screen.print("/ ");
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.newLine();
      Brain.Screen.print("    / /     |_ <     / /    |_ <    /     _/  ");
      Brain.Screen.newLine();
      Brain.Screen.print("   / /__    __) |   / /     __) |   | |}  }   ");
      Brain.Screen.newLine();
      Brain.Screen.print("   |____|  |____/  /_/     |____/  ");
      Brain.Screen.setPenColor(vex::color::red);
      Brain.Screen.print("/");
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.print("|_|");
      Brain.Screen.setPenColor(vex::color::red);
      Brain.Screen.print("/");
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.print("}__}  ");
      Brain.Screen.setPenColor(vex::color::red);
      Brain.Screen.newLine();
      Brain.Screen.print("                                      /       ");
    }