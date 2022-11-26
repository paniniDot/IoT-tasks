#ifndef __SONARTASK__
#define __SONARTASK__

#include "Utils.h"
#include "Task.h"
#include "Sonar.h"
#include "Potentiometer.h"
#include "ServoTimer2.h"

class SonarTask : public Task {

private:
  Sonar* sonar;
  WaterState waterState;
  double measureWaterLevel();
  void updateState();

public:
  SonarTask(Sonar* sonar);
  void init(int period);
  void tick();
};

#endif