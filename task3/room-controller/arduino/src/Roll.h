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

class Roll : JSONSensor<int>, public Observer<int>, public Observer<Msg>, public Subject<Msg>
{
private:
  int rollState;
  ServoTimer2 *servo;
  void notify();
  void handleMessage(Msg* msg);
  void updateRollState();
  int getCurrentHour(long timestamp);
  bool isDay(int hour);

public:
  Roll(int pin);
  void update(Event<int> *e);
  void update(Event<Msg> *e);
  String toJson() {
    return this->getJson(this->rollState);
  }
};

#endif