#ifndef __ROLL__
#define __ROLL__

#include "ServoTimer2.h"
#include "Arduino.h"
#include "JSONSensor.h"
#include "TimeLib.h"

class Roll : public JSONSensor
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