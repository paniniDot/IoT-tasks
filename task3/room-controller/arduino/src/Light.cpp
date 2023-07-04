#include "Light.h"

Light::Light(int pin)
  : JSONSensor<int>("light") {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->lightState = 0;
  this->pir_state = 0;
  this->photoresistor_state = 0;
  this->manual_state = 0;
}

void Light::update(Event<Msg> *e) {
  this->handleMessage(e->getEventArgs());
  this->updateLightState();
  EventSourceType src = e->getSrcType();
  this->notify();
}

void Light::handleMessage(Msg *msg) {
  String sensorName = msg->getSensorName();
  int measure = msg->getMeasure();
  if (sensorName == "manual_light") {
    this->manual_state = measure;
  } else if (sensorName == "pir_sensor") {
    this->pir_state = measure;
  } else if (sensorName == "photo_resistor") {
    this->photoresistor_state = measure;
  } else if (sensorName == "light") {
    this->lightState = measure;
  }
}

void Light::updateLightState() {
  if (!manual_state) {
    this->lightState = (pir_state && photoresistor_state) ? 1 : 0;
  }
  digitalWrite(this->pin, this->lightState ? HIGH : LOW);
}

void Light::notify() {
  Event<Msg> *e = new Event<Msg>(EventSourceType::LIGHT, new Msg(this->getJson(this->lightState)));
  for (int i = 0; i < this->getNObservers(); i++) {
    this->getObservers()[i]->update(e);
  }
  delete e;
  doc.clear();
}