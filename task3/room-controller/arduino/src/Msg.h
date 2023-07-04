#ifndef __MSG__
#define __MSG__

#include "Arduino.h"
#include "ArduinoJson.h"

class Msg {
private:
  String content;
  StaticJsonDocument<128> doc;

public:
  Msg(String content) {
    this->content = content;
    deserializeJson(doc, content);
  }

  String getContent() {
    return content;
  }

  String getSensorName() {
    return this->doc["name"].as<String>();
  }

  long getTimestamp() {
    return this->doc["timestamp"].as<long>();
  }

  int getMeasure() {
    return this->doc["measure"].as<int>();
  }
};

#endif