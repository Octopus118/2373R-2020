#include "Robot.h"

void Actuator::spinMechanism(vex::controller::button forwardButton, vex::controller::button reverseButton, double velocity)
{
  if (forwardButton.pressing())
  {
    m1.spin(forward,velocity,velocityUnits::rpm);
    m2.spin(forward,velocity,velocityUnits::rpm);
    m3.spin(forward,velocity,velocityUnits::rpm);
    m4.spin(forward,velocity,velocityUnits::rpm);
  }
  else if (reverseButton.pressing())
  {
    m1.spin(reverse,velocity,velocityUnits::rpm);
    m2.spin(reverse,velocity,velocityUnits::rpm);
    m3.spin(reverse,velocity,velocityUnits::rpm);
    m4.spin(reverse,velocity,velocityUnits::rpm);
  }
  else
  {
    m1.stop(brakeType::hold);
    m2.stop(brakeType::hold);
    m3.stop(brakeType::hold);
    m4.stop(brakeType::hold);
  }
}

void Actuator::startSpin(double velocity)
{
  m1.spin(forward,velocity,velocityUnits::rpm);
  m2.spin(forward,velocity,velocityUnits::rpm);
  m3.spin(forward,velocity,velocityUnits::rpm);
  m4.spin(forward,velocity,velocityUnits::rpm);
}

void Actuator::stop(brakeType brake)
{
  m1.stop(brake);
  m2.stop(brake);
  m3.stop(brake);
  m4.stop(brake);
}

void Tray::toggleMechanism(controller::button button, double velocity)
{
  if(button.pressing())
  {
    if(trayUp)
    {
      m1.rotateTo(0, rotationUnits::deg, velocity, rpm);
    }
    else
    {
      /*int finalPosition = 254;
      double acceleration = velocity / 1; //d/s^2, velocity/time
      m1.startRotateTo(finalPosition, rotationUnits::deg, velocity, rpm);
      while(m1.position(deg) < finalPosition)
      {
        m1.setVelocity(sqrt((velocity * velocity) + (2 * acceleration * m1.position(deg))), rpm);
      }*/
      I1.spin(reverse, velocity, rpm);
      I2.spin(reverse, velocity, rpm);
      m1.rotateTo(254, rotationUnits::deg, velocity, rpm);
      I1.stop(coast);
      I2.stop(coast);
    }
    trayUp = !trayUp;
  }
}