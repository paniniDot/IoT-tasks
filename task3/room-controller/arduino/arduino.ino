
#include "src/Light.h"
#include "src/Bluetooth.h"
#include "src/Roll.h"
#include "src/MsgService.h"
#include "Arduino.h"

Bluetooth *bluetooth;
Light *light;
Roll *roll;
unsigned long previousMillis = 0;
const unsigned long interval = 1000;

void setup() {
  //MsgServiceBT.init();
  MsgService.init();
  while (!Serial) {};
  bluetooth = new Bluetooth(2,3);
  light = new Light(13);
  roll = new Roll(6);
  bluetooth->attach(light);
  bluetooth->attach(roll);
  light->attach(bluetooth);
  roll->attach(bluetooth);
  MsgService.attach(light);
  MsgService.attach(roll);
}

void loop() {
 unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    MsgService.sendMsg(light->toJson());
    MsgService.sendMsg(roll->toJson());
  }
  MsgService.receiveMsg();
  //bluetooth->notify();
}