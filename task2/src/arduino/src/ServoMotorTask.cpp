#include "ServoMotorTask.h"

#define MIN_ANGLE 750
#define MAX_ANGLE 2250

ServoMotorTask::ServoMotorTask(ServoTimer2 *servo)
{
  this->servo = servo;
  this->currentAngle = MIN_ANGLE;
  this->manual = false;
}

void ServoMotorTask::init(int period)
{
  Task::init(period);
}

void ServoMotorTask::tick()
{
  this->servo->write(map(this->currentAngle, WL2, WL_MAX, MIN_ANGLE, MAX_ANGLE));
  this->notify();
}

void ServoMotorTask::update(Event<double> *e)
{
  this->currentAngle = *e->getEventArgs();
}

void ServoMotorTask::update(Event<bool> *e)
{
  this->manual = *e->getEventArgs();
}

void ServoMotorTask::notify()
{
  Event<double> *e = new Event<double>(EventSourceType::SERVO, new double(this->servo->read()));
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}
