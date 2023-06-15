#include "Roll.h"

Roll::Roll(int pin) : JSONSensor<int>("roll")
{
  this->servo = new ServoTimer2();
  this->servo->attach(pin);
  this->rollState = 0;
}

void Roll::update(Event<int> *e)
{
  EventSourceType src = e->getSrcType();
  if (src == EventSourceType::SERVO)
  {
    this->rollState = *e->getEventArgs();
    this->servo->write(map(this->rollState, 0, 100, 0, 1023));
  }
  else if (src == EventSourceType::BLUETOOTH)
  {
    this->notify();
  }
}

void Roll::notify()
{
  Event<int> *e = new Event<int>(EventSourceType::SERVO, new int(this->rollState));
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}

void Roll::update(Event<Msg> *e)
{
  this->handleMessage(e->getEventArgs());
  this->updateRollState();
}

void Roll::handleMessage(Msg* msg)
{
  String sensorName = msg->getSensorName();
  long timestamp = msg->getTimestamp();
  bool measure = msg->getMeasure();

  if (strcmp(sensorName.c_str(), "pir_sensor") == 0)
  {
    if(measure &&isDay(getCurrentHour(timestamp)))
    {
      this->rollState = 0;
    } else {
      this->rollState = 100;
    }
  } 
}

void Roll::updateRollState()
{
  this->servo->write(map(this->rollState, 0, 100, 0, 1023));
  this->notify(); // serve per il bluetooth?
}

int Roll::getCurrentHour(long timestamp)
{
  setTime(timestamp); // Set the time using the timestamp
  return hour(); // Return the current hour
}

bool Roll::isDay(int hour)
{
  return hour >= 8 && hour < 19;
}