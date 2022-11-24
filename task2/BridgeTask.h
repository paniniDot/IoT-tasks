#ifndef __BRIDGETASK__
#define __BRIDGETASK__

#include "Utils.h"
#include "Task.h"
#include "Sonar.h"
#include "Potentiometer.h"
#include "PhotoResistor.h"
#include "Pir.h"
#include "ServoTimer2.h"
/*#include "Light.h"
#include "Button.h"
#include <LiquidCrystal.h>*/

class BridgeTask : public Task {

private:
  Sonar* sonar;
  Potentiometer* pot;
  PhotoResistor* pho;
  Pir* pir;
  ServoTimer2* servo;
  /*Light* ledB;
            Light* ledC;
            Button* btn;
            LiquidCrystal* screen;*/
  WaterState waterState;
  PeopleState peopleState;

  void normalStateHandler();
  void preAlarmStateHandler();
  void lightOn();
  void lightOff();
  void alarmStateHandler();
  double measureWaterLevel();
  int CheckPeopleLevel();
  double CheckLightLevel();
  void updateState();

public:
  BridgeTask(Sonar* sonar, Potentiometer* pot, PhotoResistor* pho, Pir* pir, ServoTimer2* servo /*, Light* ledB, Light* ledC, Button btn,  LiquidCrystal* lcdScreen*/);
  void init(int period);
  void tick();
};

#endif
