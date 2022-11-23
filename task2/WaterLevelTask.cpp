#include "WaterLevelTask.h"

WaterLevelTask::WaterLevelTask(Sonar sonar, Servo servo, Potentiometer pot, Light ledB, Light ledC, Button btn, LiquidCrystal lcdScreen) {
    this->sonar = sonar;
    this->servo = servo;
    this->pot = pot;
    this->ledB = ledB;
    this->ledC = ledC;
    this->btn = btn;
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

void normalStateHandler() {
    ledB->switchOn();
    ledC->switchOff();
    servo->write(0);
    updateState();
}

void preAlarmStateHandler() {
    updateState();
}

void alarmStateHandler() {
    updateState();
}

double measureWaterLevel() {
    return sonar->measure();
}

void updateState() {
    double waterLevel = measureWaterLevel();
    if(waterLevel < ??) {
        state = NORMAL;
    } else if (waterLevel >= ?? && waterLevel < ??) {
        state = PRE_ALARM;
    } else {
        state = ALARM;
    }
}