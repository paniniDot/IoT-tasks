#include "WaterLevelTask.h"
#include "Arduino.h"

WaterLevelTask::WaterLevelTask(Sonar* sonar, Potentiometer* pot,PhotoResistor* pho,Pir* pir /*, Servo* servo, Light* ledB, Light* ledC, Button btn,  LiquidCrystal* lcdScreen*/) {
    this->sonar = sonar;
    this->pot = pot;
    this->pho = pho;
    this->pir = pir;
    /*this->servo = servo;
    this->ledB = ledB;
    this->ledC = ledC;
    this->btn = btn;
    this->screen = screen;*/
}

void WaterLevelTask::init() {
    state = NORMAL;
}

void WaterLevelTask::tick() {

  Serial.println(sonar->measure());
  Serial.println(pho->measure());
  Serial.println(pot->measure());
  Serial.println(pir->getMotion());
    switch(state) {
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

void WaterLevelTask::normalStateHandler() {
    /*ledB->switchOn();
    ledC->switchOff();
    servo->write(0);*/
    updateState();
}

void WaterLevelTask::preAlarmStateHandler() {
    updateState();
}

void WaterLevelTask::alarmStateHandler() {
    updateState();
}

double WaterLevelTask::measureWaterLevel() {
    return sonar->measure();
}

void WaterLevelTask::updateState() {
    state = WaterLevelUtils::getState(WaterLevelTask::measureWaterLevel());
}