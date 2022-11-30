#ifndef __BLINKINGTASK__
#define __BLINKINGTASK__

#include "Task.h"
#include "Led.h"
#include "Observer.h"
#include "Utils.h"
#include "Event.h"

class BlinkingTask : public Task, public Observer<WaterState>
{
private:  
  Led *led;
  enum { ON, OFF } state;
  WaterState waterState;

public:
  BlinkingTask(Led *led);
  void init(int period);
  void tick();
  void update(Event<WaterState> *e);
};

#endif