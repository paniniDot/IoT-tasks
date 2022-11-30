#include "LcdScreenTask.h"
#define MIN_ANGLE 750
#define MAX_ANGLE 2250

LcdScreenTask::LcdScreenTask(LiquidCrystal_I2C *screen)
{
    this->lcd = screen;
}

void LcdScreenTask::init(int period)
{
    Task::init(period);
    this->servoMeasure = 0.0;
    this->sonarMeasure = 0.0;
    this->waterState = WaterState::NORMAL;
    this->lcd->begin();
}

void LcdScreenTask::tick()
{
    this->lcd->clear();
    int angle = map(this->servoMeasure, MIN_ANGLE, MAX_ANGLE, 0, 180);
    switch (this->waterState)
    {
    case WaterState::ALARM:
        Serial.println("ALARM");
        this->lcd->setCursor(0, 0);
        this->lcd->print("Servo: ");
        this->lcd->print(angle);
        this->lcd->backlight();
        break;
    case WaterState::PRE_ALARM:
        Serial.println("PRE_ALARM");
        this->lcd->setCursor(0, 0);
        this->lcd->print("Servo: ");
        this->lcd->print(angle);
        this->lcd->setCursor(0, 1);
        this->lcd->print("Sonar: ");
        this->lcd->print(this->sonarMeasure);
        this->lcd->backlight();
        break;
    case WaterState::NORMAL:
        Serial.println("NORMAL");
        this->lcd->noBacklight();
        break;
    }
    Serial.println(angle);
    Serial.println(this->sonarMeasure);
}

// Update called from SonarTask and ServoTask
void LcdScreenTask::update(Event<double> *e)
{
    EventSourceType src = e->getSrcType();
    double value = *e->getEventArgs();
    if (src == EventSourceType::SERVO)
    {
        this->servoMeasure = value;
    }
    else if (src == EventSourceType::SONAR)
    {
        this->sonarMeasure = value;
    }
}

// Update called from WaterTask
void LcdScreenTask::update(Event<WaterState> *e)
{
    this->waterState = *e->getEventArgs();
}
