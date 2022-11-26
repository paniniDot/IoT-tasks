#include "LightTask.h"
#include "Arduino.h"

LightTask::LightTask(PhotoResistor* pho, Pir* pir, Led* ledA) {
  this->pho = pho;
  this->pir = pir;
  this->ledA = ledA;
}

void LightTask::init(int period) {
  Task::init(period);
  this->prevs_time = 0;
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
  ledA->switchOn();
  if(CheckPeopleLevel()==true){
    long ts = micros();
  this->prevs_time = ts;
  }
  
  updateState();
}

void LightTask::lightOff() {
  ledA->switchOff();
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
  long ts = micros();
  Serial.print("Time elapsed: ");
  Serial.println(ts - this->prevs_time);
  peopleState = Utils::getPeopleState(LightTask::CheckPeopleLevel(), LightTask::CheckLightLevel(), ts - this->prevs_time );
}