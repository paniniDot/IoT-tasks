#include "Bluetooth.h"
#include <ArduinoJson.h>
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
    // Crea un oggetto JSON per inviare lo stato della luce
    StaticJsonDocument<128> lightStateDoc;
    lightStateDoc["lightstate"] = *e->getEventArgs();
    String lightStateJson;
    serializeJson(lightStateDoc, lightStateJson);
    
    // Invia il messaggio via Bluetooth
    this->bt->println(lightStateJson);
  } else if (src == EventSourceType::SERVO) {
    // Crea un oggetto JSON per inviare lo stato del roll
    StaticJsonDocument<128> rollStateDoc;
    rollStateDoc["roll"] = *e->getEventArgs();
    String rollStateJson;
    serializeJson(rollStateDoc, rollStateJson);
    
    // Invia il messaggio via Bluetooth
    this->bt->println(rollStateJson);
  }
}



void Bluetooth::notify() {
  if (this->bt->available()) {
    String msg = this->bt->readStringUntil('\n');
    if (msg.startsWith("connesso")) {
      Event<int> *e = new Event<int>(EventSourceType::BLUETOOTH, new int(0));
      for (int i = 0; i < this->getNObservers(); i++) {
        this->getObservers()[i]->update(e);
      }
      delete e;

      // Crea un oggetto JSON per inviare i dati di configurazione
      StaticJsonDocument<128> configDoc;
      configDoc["lightcheckbox"] = this->lightmode;
      configDoc["rollcheckbox"] = this->rollmode;
      String configJson;
      serializeJson(configDoc, configJson);
      this->bt->println(configJson);
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
