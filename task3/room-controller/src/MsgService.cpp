#include "Arduino.h"
#include "MsgService.h"

MsgService::MsgService(int rx, int tx) {
  Serial.begin(9600);
  while (!Serial) {};
  this->bt = new SoftwareSerial(rx, tx);
  bt->begin(9600);
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
  String msg=e->getEventArgs()->getContent();
  delay(100);
  Serial.println(msg);
  delay(100);
  this->bt->println(msg);
  delay(100);
}
