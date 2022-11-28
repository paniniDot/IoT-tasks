#include "LcdScreenTask.h"
#include "LiquidCrystal_I2C.h"

LcdScreenTask::LcdScreenTask(LiquidCrystal_I2C* screen) {
    this->lcdScreen = screen;
    this->servoMeasure = 0.0;
    this->sonarMeasure = 0.0;
    this->lcdScreen->begin();
    this->lcdScreen->backlight();
}

LcdScreenTask::init(int period) {
    Task::init(period);
}

LcdScreenTask::tick() {
    lcd->setCursor(0,0);
    lcd->print(this->servoMeasure);
    lcd->setCursor(0,1);
    lcd->print(this->sonarMeasure);
}

LcdScreenTask::update(Event<LcdEventArg> *e) {
    if (e->getEventArgs()->getSrcType().name() == "servo") {
        this->servoMeasure = e->getEventArgs()->getValue();
    } else {
        this->sonarMeasure = e->getEventArgs()->getValue();
    }
}