#ifndef __LED__
#define __LED__

class Led
{

private:
  int pin;
  bool on;

public:
  Led(int pin);
  void switchOn();
  void switchOff();
  bool isOn();
};

#endif