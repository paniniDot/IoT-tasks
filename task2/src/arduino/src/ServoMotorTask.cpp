#include "ServoMotorTask.h"

#define MIN_ANGLE 750
#define MAX_ANGLE 2250

ServoMotorTask::ServoMotorTask(ServoTimer2 *servo, Potentiometer *pot)
{
  this->servo = servo;
  this->pot = pot;
  this->currentAngle = MIN_ANGLE;
  this->currentAngleGui = MIN_ANGLE;
  this->manual = false;
  this->guicontrol = false;
}

void ServoMotorTask::init(int period)
{
  Task::init(period);
}

void ServoMotorTask::tick()
{
  if (this->guicontrol)
  {
    this->servo->write(map(this->currentAngleGui, 0, 180, MIN_ANGLE, MAX_ANGLE));
  }
  else
  {
    if (!this->manual)
    {
      this->servo->write(map(this->currentAngle, WL2, WL_MAX, MIN_ANGLE, MAX_ANGLE));
    }
    else
    {
      this->servo->write(map(this->pot->measure(), 0, 1023, MIN_ANGLE, MAX_ANGLE));
    }
  }
  this->notify();
}

void ServoMotorTask::update(Event<double> *e)
{
  if (e->getSrcType() == EventSourceType::CHECKBOX)
  {
    this->guicontrol = !this->guicontrol;
  }
  else if (e->getSrcType() == EventSourceType::SLIDER)
  {
    this->currentAngleGui = *e->getEventArgs();
  }
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
