#ifndef __SONARTASK__
#define __SONARTASK__

#include "Utils.h"
#include "GlobalVar.h"
#include "Task.h"
#include "Sonar.h"

class SonarTask : public Task
{

private:
  Sonar *sonar;
  double measureWaterLevel();
  void updateState();

public:
  SonarTask(Sonar *sonar);
  void init(int period);
  void tick();
};

#endif