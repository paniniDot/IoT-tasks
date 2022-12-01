#ifndef __PIR__
#define __PIR__
#include "Arduino.h"
class Pir
{

private:
  int pin;

public:
  Pir(int pin);
  bool getMotion();
};

#endif