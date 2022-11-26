#ifndef __LED__
#define __LED__

class Led
{

private:
  int pin;

public:
  Led(int pin);
  void switchOn();
  void switchOff();
  void setIntensity(int v);
};

#endif