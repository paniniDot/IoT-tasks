#include "Bluetooth.h"
#include <ArduinoJson.h>
Bluetooth::Bluetooth(int rx, int tx) {
  this->bt = new SoftwareSerial(rx, tx);
  bt->begin(9600);
}
void Bluetooth::update(Event<Msg> *e) {
  String sensorName = e->getEventArgs()->getSensorName();
  int measure = e->getEventArgs()->getMeasure();
  doc.clear();
  doc["name"] = sensorName;
  doc["measure"] = measure;
  String docJson;
  serializeJson(doc, docJson);
  this->bt->println(docJson);
}

void Bluetooth::notify() {
  if (this->bt->available()) {
    String msg = this->bt->readStringUntil('\n');
    Event<Msg> *e = new Event<Msg>(EventSourceType::BLUETOOTH, new Msg(msg));
    for (int i = 0; i < this->getNObservers(); i++) {
      this->getObservers()[i]->update(e);
    }
    delete e;
  }
}
