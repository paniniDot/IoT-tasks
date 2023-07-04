#ifndef __JSONSENSOR_H__
#define __JSONSENSOR_H__

#include "ArduinoJson.h"
#include "Arduino.h"

class JSONSensor {
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
};

#endif
