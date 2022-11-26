#ifndef __LIGHTTASK__
#define __LIGHTTASK__

#include "Utils.h"
#include "Task.h"
#include "PhotoResistor.h"
#include "Pir.h"
#include "Led.h"

class LightTask : public Task {

private:
  PhotoResistor* pho;
  Pir* pir;
  PeopleState peopleState;
  Led* ledA;

  void lightOn();
  void lightOff();
  bool CheckPeopleLevel();
  double CheckLightLevel();
  void updateState();

public:
  LightTask(PhotoResistor* pho, Pir* pir, Led* ledA);
  void init(int period);
  void tick();
};

#endif
