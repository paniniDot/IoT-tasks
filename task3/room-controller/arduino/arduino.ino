
#include "src/Light.h"
#include "src/Bluetooth.h"
#include "src/Roll.h"
#include "src/MsgService.h"
#include "Arduino.h"

Bluetooth *bluetooth;
Light *light;
Roll *roll;
MsgService *msgService;
unsigned long lastNotifyTime = 0;
const unsigned long notifyInterval = 1000;
void setup() {
  msgService = new MsgService();
  Serial.begin(9600);
  while (!Serial) {};
  bluetooth = new Bluetooth(2, 3);
  light = new Light(13);
  roll = new Roll(6);
  bluetooth->attach(light);
  bluetooth->attach(roll);
  light->attach(bluetooth);
  roll->attach(bluetooth);
  msgService->attach(light);
  msgService->attach(roll);
  light->attach(msgService);
  roll->attach(msgService);
}

void loop() {
  delay(100);
  msgService->receiveMsg();
  bluetooth->notify();
  unsigned long currentTime = millis(); 
  if (currentTime - lastNotifyTime >= notifyInterval) {
    delay(100);
    light->notify();
    delay(100);
    roll->notify();
    delay(100);
    lastNotifyTime = currentTime; 
  }
}