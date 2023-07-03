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

class Light : public JSONSensor<bool>, public Observer<int>, public Observer<Msg>, public Subject<Msg>
{
private:
  int lightState;
  int pin;
  bool pir_state;
  bool photoresistor_state;
  bool manual_state;
  void notify();
  void handleMessage(Msg* msg);
  void updateLightState();

public:
  Light(int pin);
  void update(Event<int> *e);
  void update(Event<Msg> *e);
  String toJson() {
    return this->getJson(this->lightState);
  }
};

#endif