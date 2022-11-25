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
#include <EnableInterrupt.h>

#define SCHED_PERIOD 1000  //da aggiornare

Scheduler sched;

void setup() {
  Serial.begin(9600);
  Button* btn = new Button(3);
  enableInterrupt(3, interruptCheck, RISING);
  sched.init(SCHED_PERIOD);
  ServoTimer2* servo = new ServoTimer2();
  servo->attach(6);
  Task* t0 = new WaterTask(new Sonar(7, 8), new Potentiometer(A0), servo);
  Task* t1 = new LightTask(new PhotoResistor(A1), new Pir(9));
  t0->init(SCHED_PERIOD);
  t1->init(SCHED_PERIOD);
  sched.addTask(t0);
  sched.addTask(t1);
}
void interruptCheck() {
  Serial.print("button = ");
  Serial.println(manual);
  if(manual == false){
    manual = true;
  } else{
    manual = false;
  }
  delay(100);
}

void loop() {
  sched.schedule();
}