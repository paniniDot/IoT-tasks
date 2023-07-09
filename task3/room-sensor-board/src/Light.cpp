#include "Light.h"

Light::Light(int pin) : pin(pin), timeClient(ntpUDP, "pool.ntp.org", 7200)
{
  pinMode(pin, OUTPUT);
}

void Light::gradualBrightness()
{
  timeClient.update();
  int currentSecond = timeClient.getSeconds();
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
