#include "Scheduler.h"
#include "Sonar.h"
#include "Potentiometer.h"
#include "PhotoResistor.h"
#include "WaterLevelTask.h"
#include "Pir.h"
#include "Arduino.h"
#include "ServoTimer2.h"

#define SCHED_PERIOD 1000 //da aggiornare

Scheduler sched;

void setup() {
    Serial.begin(9600);
    sched.init(SCHED_PERIOD);
    ServoTimer2* servo = new ServoTimer2();
    servo->attach(6);
    Task* t0 = new WaterLevelTask(new Sonar(7, 8),new Potentiometer(A0),new PhotoResistor(A1),new Pir(9), servo);
    t0->init(SCHED_PERIOD);
    sched.addTask(t0);
}

void loop() {
    sched.schedule();
}