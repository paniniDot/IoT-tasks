#include "Light.h"

Light::Light(int pin)
{
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
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
      digitalWrite(this->pin, HIGH);
    }
    else
    {
      digitalWrite(this->pin, LOW);
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