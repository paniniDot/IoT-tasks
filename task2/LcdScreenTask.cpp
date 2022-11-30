#include "LcdScreenTask.h"
#include "LiquidCrystal_I2C.h"

LcdScreenTask::LcdScreenTask(LiquidCrystal_I2C* screen) {
    this->lcd = screen;
}

void LcdScreenTask::init(int period) {
    Task::init(period);
    this->servoMeasure = 0.0;
    this->sonarMeasure = 0.0;
    this->waterState = WaterState::NORMAL;
    this->lcd->begin();
    //this->lcd->backlight();
}

void LcdScreenTask::tick() {
    this->lcd->clear();
    switch (this->waterState )
    {
    case WaterState::ALARM:
        this->lcd->print("Servo: ");
        this->lcd->print(String(this->servoMeasure));
    case WaterState::PRE_ALARM:
        this->lcd->setCursor(0,1);
        this->lcd->print("Sonar: ");
        this->lcd->print(String(this->sonarMeasure));
        this->lcd->backlight();
        break;
    case WaterState::NORMAL:
        this->lcd->noBacklight();
        break;
    }
}

// Update called from SonarTask and ServoTask
void LcdScreenTask::update(Event<double> *e) {
    EventSourceType src = e->getSrcType();
    double value = *e->getEventArgs();
    if (src == EventSourceType::SERVO) {
        this->servoMeasure = value;
    } else if (src == EventSourceType::SONAR) {
        this->sonarMeasure = value;
    }
}

// Update called from WaterTask
void LcdScreenTask::update(Event<WaterState> *e) {
    this->waterState = *e->getEventArgs();
}
