#ifndef __JSONSENSOR_H__
#define __JSONSENSOR_H__

#include "ArduinoJson.h"
#include "Arduino.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "Msg.h"

class JSONSensor : public Observer<Msg>, public Subject<Msg> {
private:
  String name;
  StaticJsonDocument<32> doc;

protected:
  String getJson(int measure) {
    doc.clear();
    doc["name"] = name;
    doc["measure"] = measure;
    String json;
    serializeJson(doc, json);
    return json;
  }

public:
  JSONSensor(const char* name)
    : name(name) {}
  virtual void notify() = 0;
  virtual void update(Event<Msg> *e) = 0;
};

#endif
