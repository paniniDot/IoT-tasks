#include "LightTask.h"
#include "Arduino.h"

LightTask::LightTask(PhotoResistor* pho, Pir* pir, Led* led1, Led* led2) {
  this->pho = pho;
  this->pir = pir;
  this->led1 = led1;
  this->led2 = led2;

}

void LightTask::init(int period) {
  Task::init(period);
  peopleState = LIGHT_OFF;
}

void LightTask::tick() {
  /*Serial.println(pot->measure());*/
  switch (peopleState) {
    case LIGHT_OFF:
      lightOff();
      break;
    case LIGHT_ON:
      lightOn();
      break;
  }
}

void LightTask::lightOn() {
  updateState();
}

void LightTask::lightOff() {
  updateState();
}

bool LightTask::CheckPeopleLevel() {
  Serial.print("Pir = ");
  Serial.println(pir->getMotion());
  return pir->getMotion();
}

double LightTask::CheckLightLevel() {
  Serial.print("Pho = ");
  Serial.println(pho->measure());
  return pho->measure();
}

void LightTask::updateState() {
  peopleState = Utils::getPeopleState(LightTask::CheckPeopleLevel(), LightTask::CheckLightLevel());
}
