#include "WaterTask.h"
#include "Arduino.h"

WaterTask::WaterTask(Sonar* sonar, Potentiometer* pot, ServoTimer2* servo ) {
  this->sonar = sonar;
  this->pot = pot;
  this->servo = servo;
}

void WaterTask::init(int period) {
  Task::init(period);
  waterState = NORMAL;
}

void WaterTask::tick() {
  /*Serial.println(pot->measure());*/
  measureWaterLevel();
  switch (waterState) {
    case NORMAL:
      normalStateHandler();
      break;
    case PRE_ALARM:
      preAlarmStateHandler();
      break;
    case ALARM:
      alarmStateHandler();
      break;
  }
}

void WaterTask::normalStateHandler() {
  servo->write(750);
  updateState();
}

void WaterTask::preAlarmStateHandler() {
  servo->write(750);
  updateState();
}

void WaterTask::alarmStateHandler() {
  servo->write(map(sonar->measure(), 30, 70, 750, 2250));
  updateState();
}

double WaterTask::measureWaterLevel() {
  Serial.print("Sonar = ");
  Serial.println(sonar->measure());
  return sonar->measure();
}

void WaterTask::updateState() {
  waterState = Utils::getWaterState(WaterTask::measureWaterLevel());
}
