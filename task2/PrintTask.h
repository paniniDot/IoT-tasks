#ifndef __PRINTTASK__
#define __PRINTTASK__

#include "Task.h"
#include "Utils.h"
#include "GlobalVar.h"
#include "LiquidCrystal_I2C.h"

class PrintTask : public Task
{

public:
  PrintTask();
  void init(int period);
  void tick();
};

#endif