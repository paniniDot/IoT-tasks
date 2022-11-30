#ifndef __SONARTASK__
#define __SONARTASK__

#include "task/Utils.h"
#include "task/Task.h"
#include "sensor/Sonar.h"
#include "observer/Subject.h"
#include "Arduino.h"
#include "observer/Event.h"

class SonarTask : public Task, public Subject<double>
{

private:
  Sonar *sonar;
  double measureWaterLevel();
  void notify();

public:
  SonarTask(Sonar *sonar);
  void init(int period);
  void tick();
};

#endif
