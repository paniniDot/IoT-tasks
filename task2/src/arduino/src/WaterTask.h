#ifndef __WATERTASK__
#define __WATERTASK__

#include "task/Utils.h"
#include "task/Task.h"

#include "sensor/ServoTimer2.h"
#include "sensor/Led.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"
#include "Arduino.h"

class WaterTask : public Task, public Observer<double>, public Subject<WaterState>
{

private:
  WaterState waterState;
  double currentWaterLevel;
  Led *ledB;

  void normalStateHandler();
  void preAlarmStateHandler();
  void alarmStateHandler();
  void updateState();
  void notify();

public:
  WaterTask(Led *ledB);
  void init(int period);
  void tick();
  void update(Event<double> *e);
};

#endif
