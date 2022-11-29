#include "HardwareSerial.h"
#include "PrintTask.h"
LiquidCrystal_I2C lcd(0x3F, 16, 2);
PrintTask::PrintTask()
{
}

void PrintTask::init(int period)
{
  Task::init(period);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print("Hello, world!");
}

void PrintTask::tick()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(sonarMeasure);
  lcd.setCursor(0, 1);
  lcd.print(map(map(sonarMeasure, WL_MAX, WL2, 750, 2250),750,2250,0,180));
}