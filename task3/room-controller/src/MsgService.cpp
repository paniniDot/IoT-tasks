#include "Arduino.h"
#include "MsgService.h"

MsgService::MsgService(int rx, int tx) {
  Serial.begin(9600);
  while (!Serial) {};
  this->bt = new SoftwareSerial(rx, tx);
  bt->begin(9600);
  this->roll_state = "";
  this->light_State = "";
}

void MsgService::notify() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    Event<Msg> *e = new Event<Msg>(EventSourceType::MSG_SERVICE, new Msg(msg));
    for (int i = 0; i < this->getNObservers(); i++) {
      this->getObservers()[i]->update(e);
    }
    delete e;
  }
  if (this->bt->available()) {
    String msg = this->bt->readStringUntil('\n');
    Event<Msg> *e = new Event<Msg>(EventSourceType::BLUETOOTH, new Msg(msg));
    for (int i = 0; i < this->getNObservers(); i++) {
      this->getObservers()[i]->update(e);
    }
    delete e;
  }
}

void MsgService::update(Event<Msg> *e) {
  EventSourceType src = e->getSrcType();
  if (src == EventSourceType::SERVO) {
    this->roll_state = e->getEventArgs()->getContent();
  } else if (src == EventSourceType::LIGHT) {
    this->light_State = e->getEventArgs()->getContent();
  }
}

void MsgService::print() {
  Serial.println(this->roll_state);
  Serial.println(this->light_State);
  this->bt->println(this->roll_state);
  this->bt->println(this->light_State);
}
