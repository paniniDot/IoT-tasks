#include "src/Light.h"
#include "src/Roll.h"
#include "src/MsgService.h"
#include "Arduino.h"

Light *light;
Roll *roll;
MsgService *msgService;

unsigned long lastNotifyTime = 0;
const unsigned long notifyInterval = 1000;

void setup() {
  msgService = new MsgService(2, 3);
  light = new Light(13);
  roll = new Roll(6);
  msgService->attach(light);
  msgService->attach(roll);
  light->attach(msgService);
  roll->attach(msgService);
}

void loop() {
  msgService->notify();
  unsigned long currentTime = millis(); 
  if (currentTime - lastNotifyTime >= notifyInterval) {
    light->notify();
    roll->notify();
    msgService->print();
    lastNotifyTime = currentTime; 
  }
}