#ifndef __SONARTASK__
#define __SONARTASK__

#include "Utils.h"
#include "GlobalVar.h"
#include "Task.h"
#include "Sonar.h"
#include "Subject.h"

class SonarTask : public Task, public Subject<double> {

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