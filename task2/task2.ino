#include "Scheduler.h"
#include "Sonar.h"
#include "Potentiometer.h"
#include "PhotoResistor.h"
#include "WaterLevelTask.h"
#include "Pir.h"

#define SCHED_PERIOD 1000 //da aggiornare

Scheduler sched;

void setup() {
    Serial.begin(9600);
    sched.init(SCHED_PERIOD);
    Task* t0 = new WaterLevelTask(new Sonar(7, 8),new Potentiometer(A0),new PhotoResistor(A1),new Pir(9));
    t0->init(SCHED_PERIOD);
    sched.addTask(t0);
}

void loop() {
    sched.schedule();
}