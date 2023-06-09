#include "Light.h"

Light::Light(int pin)
{
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->lightState = 0;
  this->pir_state = false;
  this->photoresistor_state = 0;
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

void Light::update(Event<Msg> *e) 
{
  handleMessage(e->getEventArgs());
  updateLightState();
}

void Light::handleMessage(Msg* msg)
{
  String sensorName;
  long timestamp;
  String measure;
  msg->ParseJson(sensorName, timestamp, measure);

  if (strcmp(sensorName.c_str(), "pir") == 0)
  {
    this->pir_state = true;
  } else if (strcmp(sensorName.c_str(), "photoresistor") == 0)
  {
    this->photoresistor_state = measure.toInt();
  }

  delete msg;
}

void Light::updateLightState() 
{
  this->lightState = (pir_state && photoresistor_state < 100) ? 1 : 0;
  digitalWrite(this->pin, (this->lightState == 1) ? HIGH : LOW);
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