#ifndef __LIGHT__
#define __LIGHT__

#include "Arduino.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"
#include "MsgService.h"

class Light : public Subject<int>, public Observer<int>, public Observer<Msg>
{
private:
  int lightState;
  int pin;
  bool pir_state;
  int photoresistor_state;
  void notify();
  void handleMessage(Msg* msg);
  void updateLightState();

public:
  Light(int pin);
  void update(Event<int> *e);
  void update(Event<Msg> *e);
};

#endif