#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__
#include "Arduino.h"
class PhotoResistor
{

private:
  int pin;

public:
  PhotoResistor(int pin);
  double measure();
};

#endif