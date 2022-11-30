#ifndef __LIGHTTASK__
#define __LIGHTTASK__

#include "Utils.h"
#include "Task.h"
#include "PhotoResistor.h"
#include "Pir.h"
#include "Led.h"
#include "Observer.h"
#include "Event.h"

class LightTask : public Task, public Observer<WaterState>
{

private:
  PhotoResistor *pho;
  Pir *pir;
  PeopleState peopleState;
  Led *ledA;
  long prevs_time;
  WaterState waterState;
  void lightOn();
  void lightOff();
  bool CheckPeopleLevel();
  double CheckLightLevel();
  void updateState();

public:
  LightTask(PhotoResistor *pho, Pir *pir, Led *ledA);
  void init(int period);
  void tick();
  void update(Event<WaterState> *e);
};

#endif