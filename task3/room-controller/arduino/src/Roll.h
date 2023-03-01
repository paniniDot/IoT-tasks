#ifndef __ROLL__
#define __ROLL__

#include "Servo.h"
#include "Arduino.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"

class Roll : public Subject<int>, public Observer<int>
{
private:
  int rollState;
  Servo *servo;
  void notify();

public:
  Roll(int pin);
  void update(Event<int> *e);
};

#endif