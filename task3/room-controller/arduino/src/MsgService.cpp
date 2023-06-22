#include "Arduino.h"
#include "MsgService.h"

MsgServiceClass MsgService;

void MsgServiceClass::init() {
  Serial.begin(9600);
  currentMsg = NULL;
}
bool MsgServiceClass::isMsgAvailable() {
  return Serial.available() > 0;
}
void MsgServiceClass::receiveMsg() {
  if (isMsgAvailable()) {
    currentMsg = new Msg(Serial.readStringUntil('\n'));
    Serial.println(currentMsg->getContent());
    this->notify();
  }
}

void MsgServiceClass::sendMsg(const String& msg) {
    Serial.println(msg);
}

void MsgServiceClass::notify() {
  Event<Msg> *e = new Event<Msg>(EventSourceType::MSG_SERVICE, this->currentMsg);  
  for (int i = 0; i < this->getNObservers(); i++) {
    this->getObservers()[i]->update(e);
  }
  delete e;
}


