
#include "src/Light.h"
#include "src/Bluetooth.h"
#include "src/Roll.h"
#include "src/MsgService.h"
#include "Arduino.h"

Bluetooth *bluetooth;
void setup() {
  //MsgServiceBT.init();
  MsgService.init();
  while (!Serial) {};
  bluetooth = new Bluetooth(2,3);
  Light *light = new Light(9);
  Roll *roll = new Roll(6);
  bluetooth->attach(light);
  bluetooth->attach(roll);
  light->attach(bluetooth);
  roll->attach(bluetooth);
}

void loop() {
  if (MsgService.isMsgAvailable()) {
    Serial.println("messaggio arrivato!");
    Msg* msg = MsgService.receiveMsg();
    Serial.println(msg->getContent());
  }
  bluetooth->notify();
}