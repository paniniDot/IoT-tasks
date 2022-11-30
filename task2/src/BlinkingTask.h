#ifndef __BLINKINGTASK__
#define __BLINKINGTASK__

#include "task/Task.h"
#include "sensor/Led.h"
#include "observer/Observer.h"
#include "sensor/Utils.h"
#include "observer/Event.h"

class BlinkingTask : public Task, public Observer<WaterState>
{
private:
  Led *led;
  enum
  {
    ON,
    OFF
  } state;
  WaterState waterState;

public:
  BlinkingTask(Led *led);
  void init(int period);
  void tick();
  void update(Event<WaterState> *e);
};

#endif