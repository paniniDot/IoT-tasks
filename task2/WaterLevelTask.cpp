#include "WaterLevelTask.h"

WaterLevelTask::WaterLevelTask(Sonar* sonar, /* Servo* servo, */ Potentiometer* pot, Light* ledB, Light* ledC, /*Button btn,*/ LiquidCrystal* lcdScreen) {
    this->sonar = sonar;
    //this->servo = servo;
    this->pot = pot;
    this->ledB = ledB;
    this->ledC = ledC;
    /*this->btn = btn;*/
    this->screen = screen;
}

void WaterLevelTask::init() {
    state = NORMAL;
}

void WaterLevelTask::tick() {
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
    ledB->switchOn();
    ledC->switchOff();
    //servo->write(0);
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