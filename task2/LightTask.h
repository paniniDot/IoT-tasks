#ifndef __LIGHTTASK__
#define __LIGHTTASK__

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

class LightTask : public Task {

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
  PeopleState peopleState;

  void lightOn();
  void lightOff();
  bool CheckPeopleLevel();
  double CheckLightLevel();
  void updateState();

public:
  LightTask(Sonar* sonar, Potentiometer* pot, PhotoResistor* pho, Pir* pir, ServoTimer2* servo /*, Light* ledB, Light* ledC, Button btn,  LiquidCrystal* lcdScreen*/);
  void init(int period);
  void tick();
};

#endif
