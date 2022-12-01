#ifndef __BUTTON__
#define __BUTTON__
#include "Arduino.h"
class Button
{

private:
  long prevts;
  bool manual;

public:
  Button();
  bool press();
};

#endif