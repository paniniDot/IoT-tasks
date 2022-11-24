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

void BridgeTask::init() {
  this->waterState = NORMAL;
  Serial.println(this->waterState);
  peopleState = LIGHT_OFF;
}

void BridgeTask::tick() {
  /*Serial.println(pot->measure());
  Serial.println(pho->measure());
  Serial.println(pir->getMotion());
  Serial.println(sonar->measure());*/
  delay(100);
  Serial.println("waterState");
  Serial.println(waterState);
  Serial.println(peopleState);
  delay(100);
  switch (waterState) {
    case NORMAL:
      Serial.println("waterState");
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
  servo->write(0);
  updateState();
}

void BridgeTask::preAlarmStateHandler() {
  updateState();
}

void BridgeTask::alarmStateHandler() {
  servo->write(180);
  updateState();
}

void BridgeTask::lightOn() {
  updateState();
}

void BridgeTask::lightOff() {
  updateState();
}

double BridgeTask::measureWaterLevel() {

  return sonar->measure();
}

int BridgeTask::CheckPeopleLevel() {

  return pir->getMotion();
}

double BridgeTask::CheckLightLevel() {

  return pho->measure();
}

void BridgeTask::updateState() {
  waterState = Utils::getWaterState(BridgeTask::measureWaterLevel());
  peopleState = Utils::getPeopleState(BridgeTask::CheckPeopleLevel(), BridgeTask::CheckLightLevel());
}