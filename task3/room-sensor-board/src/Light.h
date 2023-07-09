#ifndef __LIGHT__
#define __LIGHT__
#include "Arduino.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

class Light
{

private:
  int pin;
  WiFiUDP ntpUDP;
  NTPClient timeClient;

public:
  Light(int pin);
  void gradualBrightness();
};

#endif