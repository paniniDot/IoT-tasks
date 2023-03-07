#ifndef __PIR__
#define __PIR__
#include "Arduino.h"
#include "JSONSensor.h"
class Pir : public JSONSensor<bool>
{
private:
  int pin;
  bool getMotion();

public:
  Pir(int pin);
  String toJson() {
    return this->getJson(this->getMotion());
  }

};

#endif