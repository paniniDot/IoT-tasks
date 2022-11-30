#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__
#include "Arduino.h"
class Potentiometer
{

private:
  int pin;

public:
  Potentiometer(int pin);
  double measure();
};

#endif