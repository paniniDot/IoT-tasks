#ifndef __WATERTASK__
#define __WATERTASK__

#include "Utils.h"
#include "Task.h"
#include "Potentiometer.h"
#include "ServoTimer2.h"
#include "Led.h"
#include "Observer.h"
#include "Subject.h"
#include "Event.h"
#include "EventSourceType.h"

class WaterTask : public Task, public Observer<double>, public Subject<WaterState>
{

private:
  Potentiometer *pot;
  WaterState waterState;
  double currentWaterLevel;
  Led* ledB;

  void normalStateHandler();
  void preAlarmStateHandler();
  void alarmStateHandler();
  void updateState();
  void notify();

public:
  WaterTask(Potentiometer *pot, Led* ledB);
  void init(int period);
  void tick();
  void update(Event<double> *e);
};

#endif
