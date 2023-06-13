
#include "src/Light.h"
#include "src/Bluetooth.h"
#include "src/Roll.h"
#include "src/MsgService.h"
#include "Arduino.h"

Bluetooth *bluetooth;
Light *light;
Roll *roll;

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
  if (MsgService.isMsgAvailable()) {
    Msg* msg = MsgService.receiveMsg();
    //creo due eventi distinti in modo che ciascuno possa eliminare il proprio
    light->update(new Event<Msg>(EventSourceType::MSG_SERVICE, msg));
    roll->update(new Event<Msg>(EventSourceType::MSG_SERVICE, msg));
  }
  bluetooth->notify();
}