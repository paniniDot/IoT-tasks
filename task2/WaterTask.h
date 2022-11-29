#ifndef __WATERTASK__
#define __WATERTASK__

#include "Utils.h"
#include "Task.h"
#include "Potentiometer.h"
#include "ServoTimer2.h"
#include "GlobalVar.h"
#include "Led.h"

class WaterTask : public Task
{

private:
  Potentiometer *pot;
  ServoTimer2 *servo;
  Led *led;

  void normalStateHandler();
  void preAlarmStateHandler();
  void alarmStateHandler();
  void updateState();

public:
  WaterTask(Potentiometer *pot, ServoTimer2 *servo, Led *led);
  void init(int period);
  void tick();
};

#endif
