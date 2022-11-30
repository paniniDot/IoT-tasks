#include "LcdScreenTask.h"
#include "LiquidCrystal_I2C.h"

LcdScreenTask::LcdScreenTask(LiquidCrystal_I2C* screen) {
    this->lcd = screen;
    this->servoMeasure = 0.0;
    this->sonarMeasure = 0.0;
    this->lcd->begin();
    this->lcd->backlight();
}

void LcdScreenTask::init(int period) {
    Task::init(period);
}

void LcdScreenTask::tick() {
    this->lcd->clear();
    this->lcd->print("Servo: ");
    this->lcd->print(String(this->servoMeasure));
    this->lcd->setCursor(0,1);
    this->lcd->print("Sonar: ");
    this->lcd->print(String(this->sonarMeasure));
}

void LcdScreenTask::update(Event<double> *e) {
    EventSourceType src = e->getSrcType();
    double value = *e->getEventArgs();
    if (src == EventSourceType::SERVO) {
        this->servoMeasure = value;
    } else if (src == EventSourceType::SONAR) {
        this->sonarMeasure = value;
    }
}