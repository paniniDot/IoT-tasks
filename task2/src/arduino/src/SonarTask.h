#ifndef __SONARTASK__
#define __SONARTASK__

#include "task/Utils.h"
#include "task/Task.h"
#include "sensor/Sonar.h"
#include "observer/Subject.h"
#include "observer/Observer.h"
#include "Arduino.h"
#include "observer/Event.h"

class SonarTask : public Task, public Subject<double>, public Observer<WaterState>
{

private:
  Sonar *sonar;
  double measureWaterLevel();
  WaterState currentWaterState;
  void notify();

public:
  SonarTask(Sonar *sonar);
  void init(int period);
  void tick();
  void update(Event<WaterState> *e);
};

#endif
