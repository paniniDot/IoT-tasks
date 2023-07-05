#include "Roll.h"

Roll::Roll(int pin)
  : JSONSensor("roll") {
  this->servo = new ServoTimer2();
  this->servo->attach(pin);
  this->rollState = 0;
  this->pir_state = 0;
  this->isDay = 0;
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

  if (sensorName.equals("pir_sensor")) {
    setTime(timestamp);
    this->isDay = (hour() >= 8 && hour() < 19) ? 1 : 0;
  } else if (sensorName.equals("manual_roll")) {
    this->manual_state = measure;
  } else if (sensorName.equals("roll")) {
    this->rollState = measure;
  }
}

void Roll::updateRollState() {
  if (!this->manual_state) {
    this->rollState = (this->pir_state && this->isDay) ? 0 : 100;
  }
  this->servo->write(map(this->rollState, 0, 100, 0, 1023));
}

void Roll::notify() {
  String msg = this->getJson(this->rollState);
  Event<Msg> *e = new Event<Msg>(EventSourceType::SERVO, new Msg(msg));
  for (int i = 0; i < this->getNObservers(); i++) {
    this->getObservers()[i]->update(e);
  }
  delete e;
}