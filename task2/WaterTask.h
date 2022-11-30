#ifndef __WATERTASK__
#define __WATERTASK__

#include "Utils.h"
#include "Task.h"
#include "Potentiometer.h"
#include "ServoTimer2.h"
#include "Led.h"

class WaterTask : public Task, public Observer<double> 
{

private:
  Potentiometer *pot;
  WaterState waterState;
  double currentWaterLevel;
  Led* ledB;
  Led* ledC;

  void normalStateHandler();
  void preAlarmStateHandler();
  void alarmStateHandler();
  void updateState();

public:
  WaterTask(Potentiometer *pot, Led* ledB, Led* ledC);
  void init(int period);
  void tick();
  void update(Event<double> *e);
};

#endif
