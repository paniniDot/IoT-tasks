#ifndef __ROLL__
#define __ROLL__

#include "ServoTimer2.h"
#include "Arduino.h"
#include "JSONSensor.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"
#include "MsgService.h"
#include "Msg.h"
#include "TimeLib.h"

class Roll : JSONSensor, public Observer<Msg>, public Subject<Msg>
{
private:

  ServoTimer2 *servo;
  int rollState;
  int isDay;
  int pir_state;
  int manual_state;
  void handleMessage(Msg* msg);
  void updateRollState();

public:
  Roll(int pin);
  void notify();
  void update(Event<Msg> *e);
};

#endif