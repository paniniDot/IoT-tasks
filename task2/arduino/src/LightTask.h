#ifndef __LIGHTTASK__
#define __LIGHTTASK__

#include "task/Utils.h"
#include "task/Task.h"
#include "sensor/PhotoResistor.h"
#include "sensor/Pir.h"
#include "sensor/Led.h"
#include "observer/Observer.h"
#include "observer/Event.h"
#include "Arduino.h"
#include "observer/EventSourceType.h"
#include "observer/Subject.h"
class LightTask : public Task, public Observer<WaterState>, public Subject<PeopleState>
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
  void notify();

public:
  LightTask(PhotoResistor *pho, Pir *pir, Led *ledA);
  void init(int period);
  void tick();
  void update(Event<WaterState> *e);
};

#endif