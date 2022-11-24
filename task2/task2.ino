#include "Scheduler.h"
#include "WaterLevelUtils.h"
#include "Task.h"
#include "Sonar.h"
//#include <Servo.h>
#include "Potentiometer.h"
#include "Light.h"
#include "Button.h"
#include <LiquidCrystal.h>
#include "WaterLevelTask.h"

#define SCHED_PERIOD 1000 //da aggiornare

Scheduler sched;

void setup() {
    Serial.begin(9600);
    sched.init(SCHED_PERIOD);
    Task* t0 = new WaterLevelTask(new Sonar(7, 8),new Potentiometer(1));
    t0->init(SCHED_PERIOD);
    sched.addTask(t0);
}

void loop() {
    sched.schedule();
}