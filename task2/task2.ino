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
#include "SonarTask.h"
#include "ServoMotorTask.h"
#include "LcdScreenTask.h"
#include <EnableInterrupt.h>
#include "BlinkingTask.h"

#include "MemoryFree.h"

#define SCHED_PERIOD 1000 // da aggiornare

Scheduler sched;
long prevts = 0;

void setup()
{
  Serial.begin(9600);
  enableInterrupt(4, interruptCheck, RISING);
  sched.init(SCHED_PERIOD);
  ServoTimer2 *servo = new ServoTimer2();
  servo->attach(5);
  WaterTask *t0 = new WaterTask(new Potentiometer(A3), new Led(9));
  Task *t1 = new LightTask(new PhotoResistor(A2), new Pir(11), new Led(10));
  SonarTask *t2 = new SonarTask(new Sonar(7, 8));
  ServoMotorTask *t3 = new ServoMotorTask(servo);
  LcdScreenTask *t4 = new LcdScreenTask(new LiquidCrystal_I2C(0x3F, 16, 2));
  BlinkingTask *t5 = new BlinkingTask(new Led(6));
  t0->init(SCHED_PERIOD);
  t1->init(SCHED_PERIOD);
  t2->init(SCHED_PERIOD);
  t3->init(SCHED_PERIOD);
  t4->init(SCHED_PERIOD);
  t5->init(SCHED_PERIOD);
  sched.addTask(t0);
  sched.addTask(t1);
  sched.addTask(t2);
  sched.addTask(t3);
  sched.addTask(t4);
  sched.addTask(t5);
  t0->attach(t4);
  t0->attach(t5);
  t2->attach(t0);
  t2->attach(t3);
  t2->attach(t4);
  t3->attach(t4);
}
void interruptCheck()
{
  long ts = micros();
  if (ts - prevts > 1000000)
  {
    Serial.print("button = ");
    Serial.println(manual);
    if (manual == false)
    {
      manual = true;
    }
    else
    {
      manual = false;
    }
    prevts = ts;
  }
}

void loop()
{
  Serial.print("Free memory = ");
  Serial.println(freeMemory());

  // noInterrupts();
  sched.schedule();
  // interrupts();
}
