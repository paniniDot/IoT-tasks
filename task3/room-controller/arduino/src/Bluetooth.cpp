#include "Bluetooth.h"

Bluetooth::Bluetooth(int rx, int tx) {
  this->bt = new SoftwareSerial(rx, tx);
  this->rollmode = 0;
  this->lightmode = 0;
  bt->begin(9600);
  Serial.println("ready to go.");
}
void Bluetooth::update(Event<int> *e) {
  EventSourceType src = e->getSrcType();
  if (src == EventSourceType::LIGHT) {
    this->bt->print("lightstate: ");
    this->bt->println(*e->getEventArgs());
  } else if (src == EventSourceType::SERVO) {
    this->bt->print("roll: ");
    this->bt->println(*e->getEventArgs());
  }
}

void Bluetooth::notify() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    Serial.println(msg);
  }
  if (this->bt->available()) {
    String msg = this->bt->readStringUntil('\n');
    Serial.println(msg);
    if (msg.startsWith("connesso")) {
      Event<int> *e = new Event<int>(EventSourceType::BLUETOOTH, new int(0));
      for (int i = 0; i < this->getNObservers(); i++) {
        this->getObservers()[i]->update(e);
      }
      delete e;
      this->bt->print("lightcheckbox: ");
      this->bt->println(this->lightmode);
      delay(100);
      this->bt->print("rollcheckbox: ");
      this->bt->println(this->rollmode);
    } else if (msg.startsWith("lightcheckbox")) {
      this->lightmode = msg.substring(strlen("lightcheckbox: ")).equals("true");
    } else if (msg.startsWith("rollcheckbox")) {
      this->rollmode = msg.substring(strlen("rollcheckbox: ")).equals("true");
    } else if (msg.startsWith("light")) {
      Event<int> *e = new Event<int>(EventSourceType::LIGHT, new int(msg.substring(strlen("light: ")).equals("true")));
      for (int i = 0; i < this->getNObservers(); i++) {
        this->getObservers()[i]->update(e);
      }
      delete e;
    } else if (msg.startsWith("roll")) {
      Event<int> *e = new Event<int>(EventSourceType::SERVO, new int(msg.substring(strlen("roll: ")).toInt()));
      for (int i = 0; i < this->getNObservers(); i++) {
        this->getObservers()[i]->update(e);
      }
      delete e;
    }
  }
}