#ifndef __LIGHT__
#define __LIGHT__

#include "task/Utils.h"
#include "sensor/Led.h"
#include "observer/Observer.h"
#include "Arduino.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"

class Light : public Subject<LightState>, public Observer<LightState>
{
private:
  LightState lightState;
  Led *ledA;

public:
  Light(Led *led);
  void update(Event<LightState> *e);
  void notify();
};

#endif