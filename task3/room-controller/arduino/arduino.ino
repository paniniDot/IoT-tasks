
#include "src/Light.h"
#include "src/Bluetooth.h"
#include "src/Roll.h"
#include "src/MsgService.h"
#include "Arduino.h"

Bluetooth *bluetooth;
Light *light;
Roll *roll;
MsgService *msgService;

void setup() {
  msgService = new MsgService();
  bluetooth = new Bluetooth(2,3);
  light = new Light(13);
  roll = new Roll(6);
  bluetooth->attach(light);
  //bluetooth->attach(roll);
  light->attach(bluetooth);
  //roll->attach(bluetooth);
  msgService->attach(light);
  msgService->attach(roll);
  light->attach(msgService);
  roll->attach(msgService);
}

void loop() {
  //msgService->receiveMsg();
  bluetooth->notify();
  delay(100);
}