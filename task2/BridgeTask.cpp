#include "BridgeTask.h"
#include "Arduino.h"

BridgeTask::BridgeTask(Sonar* sonar, Potentiometer* pot, PhotoResistor* pho, Pir* pir, ServoTimer2* servo /*,Light* ledB, Light* ledC, Button btn,  LiquidCrystal* lcdScreen*/) {
  this->sonar = sonar;
  this->pot = pot;
  this->pho = pho;
  this->pir = pir;
  this->servo = servo;
  /*this->ledB = ledB;
    this->ledC = ledC;
    this->btn = btn;
    this->screen = screen;*/
}

void BridgeTask::init(int period) {
  Task::init(period);
  waterState = NORMAL;
  peopleState = LIGHT_OFF;
}

void BridgeTask::tick() {
  /*Serial.println(pot->measure());
  Serial.println(pho->measure());
  Serial.println(pir->getMotion());
  Serial.println(sonar->measure());*/
  switch (waterState) {
    case NORMAL:
      delay(100);
      normalStateHandler();
      break;
    case PRE_ALARM:
      preAlarmStateHandler();
      break;
    case ALARM:
      alarmStateHandler();
      break;
  }
  switch (peopleState) {
    case LIGHT_OFF:
      lightOff();
      break;
    case LIGHT_ON:
      lightOn();
      break;
  }
}

void BridgeTask::normalStateHandler() {
  Serial.println("Normal stato");
  servo->write(750);
  updateState();
}

void BridgeTask::preAlarmStateHandler() {
  Serial.println("pre alarm stato");
  servo->write(750);
  updateState();
}

void BridgeTask::alarmStateHandler() {
  Serial.println("alarm stato");
  servo->write(2250);
  updateState();
}

void BridgeTask::lightOn() {
  updateState();
}

void BridgeTask::lightOff() {
  updateState();
}

double BridgeTask::measureWaterLevel() {
  Serial.print("Sonar = ");
  Serial.println(sonar->measure());
  return sonar->measure();
}

int BridgeTask::CheckPeopleLevel() {
  Serial.print("Pir = ");
  Serial.println(pir->getMotion());
  return pir->getMotion();
}

double BridgeTask::CheckLightLevel() {
  Serial.print("Pho = ");
  Serial.println(pho->measure());
  return pho->measure();
}

void BridgeTask::updateState() {
  waterState = Utils::getWaterState(BridgeTask::measureWaterLevel());
  peopleState = Utils::getPeopleState(BridgeTask::CheckPeopleLevel(), BridgeTask::CheckLightLevel());
}
