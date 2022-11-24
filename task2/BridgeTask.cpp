#include "BridgeTask.h"
#include "Arduino.h"

BridgeTask::BridgeTask(Sonar* sonar, Potentiometer* pot,PhotoResistor* pho,Pir* pir, ServoTimer2* servo /*,Light* ledB, Light* ledC, Button btn,  LiquidCrystal* lcdScreen*/) {
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
    waterState = NORMAL;
    peopleState = LIGHT_OFF;
}

void BridgeTask::tick() {
  Serial.println(pot->measure());
    switch(waterState) {
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
    switch(peopleState) {
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
    Serial.println(sonar->measure());
    return sonar->measure();
}

int BridgeTask::CheckPeopleLevel() {
    Serial.println(pir->getMotion());
    return pir->getMotion();
}

double BridgeTask::CheckLightLevel() {
    Serial.println(pho->measure());
    return pho->measure();
}

void BridgeTask::updateState() {
    waterState = Utils::getWaterState(BridgeTask::measureWaterLevel());
    peopleState = Utils::getPeopleState(BridgeTask::CheckPeopleLevel(),BridgeTask::CheckLightLevel());
}