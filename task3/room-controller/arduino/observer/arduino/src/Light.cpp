#include "Light.h"

Light::Light(int pin)
{
  this->ledA = new Led(pin);
  this->lightState = 0;
}

void Light::update(Event<int> *e)
{
  EventSourceType src = e->getSrcType();
  if (src == EventSourceType::LIGHT)
  {
    this->lightState = *e->getEventArgs();
    if (this->lightState == 1)
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
  Event<int> *e = new Event<int>(EventSourceType::LIGHT, new int(this->lightState));
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}