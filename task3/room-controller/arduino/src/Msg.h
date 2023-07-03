#ifndef __MSG__
#define __MSG__

#include "Arduino.h"
#include "ArduinoJson.h"

class Msg {
  String content;
  DynamicJsonDocument doc;

public:
  Msg(String content) : content(content), doc(128) {
    deserializeJson(doc, this->content);
  }
  
  String getContent(){
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