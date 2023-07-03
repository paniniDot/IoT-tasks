#include "Light.h"

Light::Light(int pin)
  : JSONSensor<bool>("light") {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->lightState = 0;
  this->pir_state = false;
  this->photoresistor_state = false;
  this->manual_state = false;
}

void Light::update(Event<int> *e) {
  EventSourceType src = e->getSrcType();
  if (src == EventSourceType::LIGHT) {
    this->lightState = *e->getEventArgs();
    if (this->lightState == 1) {
      digitalWrite(this->pin, HIGH);
    } else {
      digitalWrite(this->pin, LOW);
    }
  } else if (src == EventSourceType::BLUETOOTH) {
    this->notify();
  }
}

void Light::update(Event<Msg> *e) {
  this->handleMessage(e->getEventArgs());
  this->updateLightState();
}

void Light::handleMessage(Msg *msg) {
  String sensorName = msg->getSensorName();
  long timestamp = msg->getTimestamp();
  bool measure = msg->getMeasure();
  if (strcmp(sensorName.c_str(), "manual_light") == 0) {
    this->manual_state = measure;
  } else if (strcmp(sensorName.c_str(), "pir_sensor") == 0) {
    this->pir_state = measure;
  } else if (strcmp(sensorName.c_str(), "photo_resistor") == 0) {
    this->photoresistor_state = measure;
  } else if (strcmp(sensorName.c_str(), "light") == 0) {
    this->lightState = measure;
  }
}

void Light::updateLightState() {
  if (!manual_state) {
    this->lightState = (pir_state && photoresistor_state) ? 1 : 0;
  }
  digitalWrite(this->pin, this->lightState ? HIGH : LOW);
  this->notify();  // serve per il bluetooth?
}

void Light::notify() {
  Event<Msg> *e = new Event<Msg>(EventSourceType::LIGHT, new Msg(this->toJson()));
  for (int i = 0; i < this->getNObservers(); i++) {
    this->getObservers()[i]->update(e);
  }
  delete e;
}