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
  int rollState;
  ServoTimer2 *servo;
  void handleMessage(Msg* msg);
  void updateRollState();
  int getCurrentHour(long timestamp);
  int isDay(int hour);
  int manual_state;

public:
  Roll(int pin);
  void notify();
  void update(Event<Msg> *e);
};

#endif