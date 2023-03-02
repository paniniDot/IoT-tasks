#include "Roll.h"

Roll::Roll(int pin)
{
  this->servo = new Servo();
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