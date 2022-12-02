#include "src/task/Scheduler.h"
#include "src/sensor/Sonar.h"
#include "src/sensor/Potentiometer.h"
#include "src/sensor/PhotoResistor.h"
#include "src/WaterTask.h"
#include "src/LightTask.h"
#include "src/sensor/Pir.h"
#include "Arduino.h"
#include "src/sensor/ServoTimer2.h"
#include "src/sensor/Button.h"
#include "src/sensor/Led.h"
#include "src/SonarTask.h"
#include "src/ServoMotorTask.h"
#include "src/LcdScreenTask.h"
#include <EnableInterrupt.h>
#include "src/BlinkingTask.h"
#include "src/SerialComunicationTask.h"
#include "src/debug/MemoryFree.h"
#include "src/ManualControlTask.h"

#define SCHED_PERIOD 100
Scheduler sched;
Button *btn = new Button();

void setup()
{
  Serial.begin(9600);
  enableInterrupt(4, interruptCheck, RISING);
  sched.init(SCHED_PERIOD);
  ServoTimer2 *servo = new ServoTimer2();
  servo->attach(5);
  WaterTask *t0 = new WaterTask(new Led(9));
  LightTask *t1 = new LightTask(new PhotoResistor(A2), new Pir(11), new Led(10));
  SonarTask *t2 = new SonarTask(new Sonar(7, 8));
  ServoMotorTask *t3 = new ServoMotorTask(servo, new Potentiometer(A3));
  LcdScreenTask *t4 = new LcdScreenTask(new LiquidCrystal_I2C(0x3F, 16, 2));
  BlinkingTask *t5 = new BlinkingTask(new Led(6));
  SerialComunicationTask *t6 = new SerialComunicationTask();
  ManualControlTask *t7 = new ManualControlTask(btn);
  t0->init(SCHED_PERIOD);
  t1->init(5 * SCHED_PERIOD);
  t2->init(SCHED_PERIOD);
  t3->init(SCHED_PERIOD);
  t4->init(10 * SCHED_PERIOD);
  t5->init(20 * SCHED_PERIOD);
  t6->init(SCHED_PERIOD);
  t7->init(SCHED_PERIOD);
  /*
    the order in which the tasks are added to the scheduler is important
    because the scheduler will execute the tasks in the same order by calling tick()
    we decided to let the sensors tasks to be executed first because others tasks depend on them.
  */ 
  sched.addTask(t2);
  sched.addTask(t0);
  sched.addTask(t6);
  sched.addTask(t7);
  sched.addTask(t3);
  sched.addTask(t1);
  sched.addTask(t5);
  sched.addTask(t4);
  t0->attach(t1);
  t0->attach(t4);
  t0->attach(t5);
  t1->attach(t4);
  t2->attach(t0);
  t2->attach(t3);
  t2->attach(t4);
  t3->attach(t4);
  t6->attach(t3);
  t7->attach(t3);
}
void interruptCheck()
{
  btn->press();
}

void loop()
{
  // Serial.println(freeMemory());
  sched.schedule();
}
