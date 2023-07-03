#include "Bluetooth.h"
#include <ArduinoJson.h>
Bluetooth::Bluetooth(int rx, int tx) {
  this->bt = new SoftwareSerial(rx, tx);
  this->rollmode = 0;
  this->lightmode = 0;
  bt->begin(9600);
}
void Bluetooth::update(Event<int> *e) {
  EventSourceType src = e->getSrcType();
  if (src == EventSourceType::LIGHT) {
    StaticJsonDocument<128> lightStateDoc;
    lightStateDoc["lightstate"] = *e->getEventArgs();
    String lightStateJson;
    serializeJson(lightStateDoc, lightStateJson);
    this->bt->println(lightStateJson);
  } else if (src == EventSourceType::SERVO) {
    StaticJsonDocument<128> rollStateDoc;
    rollStateDoc["roll"] = *e->getEventArgs();
    String rollStateJson;
    serializeJson(rollStateDoc, rollStateJson);
    this->bt->println(rollStateJson);
  }
}

void Bluetooth::notify() {
  if (this->bt->available()) {
    String msg = this->bt->readStringUntil('\n');
    StaticJsonDocument<128> doc;
    deserializeJson(doc, msg);
    if (doc.containsKey("connesso")) {
      Event<int> *e = new Event<int>(EventSourceType::BLUETOOTH, new int(0));
      for (int i = 0; i < this->getNObservers(); i++) {
        this->getObservers()[i]->update(e);
      }
      delete e;
      StaticJsonDocument<64> configDoc;
      configDoc["lightcheckbox"] = this->lightmode;
      String configJson;
      serializeJson(configDoc, configJson);
      this->bt->println(configJson);
      StaticJsonDocument<64> configDoc1;
      configDoc1["rollcheckbox"] = this->rollmode;
      String configJson1;
      serializeJson(configDoc1, configJson1);
      this->bt->println(configJson1);      
    } else if (doc.containsKey("lightcheckbox")) {
      this->lightmode =  doc["lightcheckbox"];
    } else if (doc.containsKey("rollcheckbox")) {
      this->rollmode = doc["rollcheckbox"];
    } else if (doc.containsKey("light")) {
      Event<int> *e = new Event<int>(EventSourceType::LIGHT, new int(doc["light"]));
      for (int i = 0; i < this->getNObservers(); i++) {
        this->getObservers()[i]->update(e);
      }
      delete e;
    } else if (doc.containsKey("roll")) {
      Event<int> *e = new Event<int>(EventSourceType::SERVO, new int(doc["roll"]));
      for (int i = 0; i < this->getNObservers(); i++) {
        this->getObservers()[i]->update(e);
      }
      delete e;
    }
  }
}
