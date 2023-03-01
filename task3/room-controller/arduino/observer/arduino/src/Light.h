#ifndef __LIGHT__
#define __LIGHT__

#include "sensor/Led.h"
#include "Arduino.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"

class Light : public Subject<bool>, public Observer<bool>
{
private:
  bool lightState;
  Led *ledA;
  void notify();

public:
  Light(int pin);
  void update(Event<bool> *e);
};

#endif