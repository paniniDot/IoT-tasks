#include "Scheduler.h"

#define SCHED_PERIOD 1000 //da aggiornare

Scheduler sched;

void setup() {
    sched.init(SCHED_PERIOD);
    
    //Task* t0 = new ...
    //t0.init(???)
    //sched->addTask(t0);
}

void loop() {
    sched.schedule();
}