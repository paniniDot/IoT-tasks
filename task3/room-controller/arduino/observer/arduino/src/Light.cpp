#include "Light.h"

Light::Light(int pin)
{
  this->ledA = new Led(pin);
  this->lightState = false;
}

void Light::update(Event<bool> *e)
{
  EventSourceType src = e->getSrcType();
  if (src == EventSourceType::LIGHT)
  {
    this->lightState = *e->getEventArgs();
    if (this->lightState)
    {
      this->ledA->switchOn();
    }
    else
    {
      this->ledA->switchOff();
    }
  }
  else if (src == EventSourceType::BLUETOOTH)
  {
    this->notify();
  }
}

void Light::notify()
{
  Event<bool> *e = new Event<bool>(EventSourceType::LIGHT, new bool(this->lightState));
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}