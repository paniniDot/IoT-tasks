#ifndef __PIR__
#define __PIR__
#include "Arduino.h"
#include "JSONSensor.h"
class Pir : public JSONSensor<int>
{
private:
  int pin;
  int getMotion();

public:
  Pir(int pin);
  String toJson() {
    return this->getJson(this->getMotion());
  }

};

#endif