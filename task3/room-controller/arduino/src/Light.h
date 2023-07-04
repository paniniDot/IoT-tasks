#ifndef __LIGHT__
#define __LIGHT__

#include "Arduino.h"
#include "JSONSensor.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"
#include "MsgService.h"
#include "Msg.h"

class Light : public JSONSensor, public Observer<Msg>, public Subject<Msg>
{
private:
  int lightState;
  int pin;
  int pir_state;
  int photoresistor_state;
  int manual_state;
  void handleMessage(Msg* msg);
  void updateLightState();

public:
  Light(int pin);
  void notify();
  void update(Event<Msg> *e);
};

#endif