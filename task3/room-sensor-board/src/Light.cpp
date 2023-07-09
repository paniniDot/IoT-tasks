#include "Light.h"

Light::Light(int pin) : pin(pin)
{
  pinMode(pin, OUTPUT);
}

void Light::gradualBrightness()
{
  int currentSecond = second();
  int brightness = 0;
  int startSecond = 0;
  int peakSecond = 30;
  int endSecond = 60;

  if (currentSecond >= startSecond && currentSecond <= peakSecond)
  {
    brightness = map(currentSecond, startSecond, peakSecond, 0, 255);
  }
  else if (currentSecond > peakSecond && currentSecond <= endSecond)
  {
    brightness = map(currentSecond, peakSecond, endSecond, 255, 0);
  }

  analogWrite(pin, brightness);
}
