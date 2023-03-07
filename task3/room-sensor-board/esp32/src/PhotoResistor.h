#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__
#include "Arduino.h"
#include "JSONSensor.h"

class PhotoResistor : public JSONSensor<bool>
{

private:
  int pin;
  bool isDark();

public:
  PhotoResistor(int pin);
  String toJson() {
    return this->getJson(this->isDark());
  }  
};

#endif