#include "Scheduler.h"
#include "Sonar.h"
#include "Potentiometer.h"
#include "PhotoResistor.h"
#include "WaterTask.h"
#include "LightTask.h"
#include "Pir.h"
#include "Arduino.h"
#include "ServoTimer2.h"
#include "Button.h"
#include "Led.h"
#include <EnableInterrupt.h>

#define SCHED_PERIOD 1000  //da aggiornare

Scheduler sched;
long prevts = 0;

void setup() {
  Serial.begin(9600);
  enableInterrupt(2, interruptCheck, RISING);
  sched.init(SCHED_PERIOD);
  ServoTimer2* servo = new ServoTimer2();
  servo->attach(6);
  Task* t0 = new WaterTask(new Sonar(7, 8), new Potentiometer(A0), servo);
  Task* t1 = new LightTask(new PhotoResistor(A1), new Pir(9), new Led(3), new Led(4));
  //Task* t2 = new WaterTask(new Sonar(7, 8));
  t0->init(SCHED_PERIOD);
  t1->init(SCHED_PERIOD);
  //t2->init(SCHED_PERIOD);
  sched.addTask(t0);
  sched.addTask(t1);
  //sched.addTask(t2);
}
void interruptCheck() {
  long ts = micros();
  if (ts - prevts > 100000) {
    Serial.print("button = ");
    Serial.println(manual);
    if (manual == false) {
      manual = true;
    } else {
      manual = false;
    }
    prevts = ts;
  }
}

void loop() {
  //noInterrupts();
  sched.schedule();
  //interrupts();
}