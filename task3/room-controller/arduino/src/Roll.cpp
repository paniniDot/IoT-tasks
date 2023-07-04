#include "Roll.h"

Roll::Roll(int pin)
  : JSONSensor("roll") {
  this->servo = new ServoTimer2();
  this->servo->attach(pin);
  this->rollState = 0;
  this->manual_state = 0;
}

void Roll::update(Event<Msg> *e) {
  this->handleMessage(e->getEventArgs());
  this->updateRollState();
  EventSourceType src = e->getSrcType();
  if (src != EventSourceType::BLUETOOTH || src != EventSourceType::MSG_SERVICE) {
    this->notify();
  }
}

void Roll::handleMessage(Msg *msg) {
  String sensorName = msg->getSensorName();
  long timestamp = msg->getTimestamp();
  int measure = msg->getMeasure();

  if (strcmp(sensorName.c_str(), "pir_sensor") == 0) {
    if (measure && isDay(getCurrentHour(timestamp))) {
      this->rollState = 0;
    } else {
      this->rollState = 100;
    }
  } else if (strcmp(sensorName.c_str(), "manual_roll") == 0) {
    this->manual_state = measure;
  }  else if (strcmp(sensorName.c_str(), "roll") == 0) {
    this->rollState = measure;
  }
}

void Roll::updateRollState() {
  this->servo->write(map(this->rollState, 0, 100, 0, 1023));
}

int Roll::getCurrentHour(long timestamp) {
  setTime(timestamp);  // Set the time using the timestamp
  return hour();       // Return the current hour
}

int Roll::isDay(int hour) {
  return hour >= 8 && hour < 19;
}

void Roll::notify() {
  String msg = this->getJson(this->rollState);
  Event<Msg> *e = new Event<Msg>(EventSourceType::SERVO, new Msg(msg));
  for (int i = 0; i < this->getNObservers(); i++) {
    this->getObservers()[i]->update(e);
  }
  delete e;
}