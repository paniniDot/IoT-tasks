#include "Light.h"

Light::Light(int pin)
{
  this->ledA = new Led(pin);
  this->lightState = LIGHT_OFF;
}

void Light::update(Event<LightState> *e)
{
  this->lightState = *e->getEventArgs();
  if (this->lightState == LIGHT_ON)
  {
    this->ledA->switchOn();
  }
  else
  {
    this->ledA->switchOff();
  }
  this->notify();
}

void Light::notify()
{
  Event<LightState> *e = new Event<LightState>(EventSourceType::LIGHT, new LightState(this->lightState));
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}