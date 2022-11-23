#include "Scheduler.h"
#include "Sonar.h"
#include "SonarTask.h"

#define SCHED_PERIOD 100 //da aggiornare

Scheduler* sched;

void setup() {
    sched->init(SCHED_PERIOD);
    Task* t0 = new SonarTask(new Sonar(7, 8));
    t0->init(SCHED_PERIOD);
    sched->addTask(t0);
}

void loop() {
    sched->schedule();
}