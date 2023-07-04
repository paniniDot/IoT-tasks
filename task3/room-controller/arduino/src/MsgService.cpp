#include "Arduino.h"
#include "MsgService.h"

MsgService::MsgService(){
  content.reserve(512);
  content = "";
  currentMsg = NULL;
  msgAvailable = false;  
}


bool MsgService::isMsgAvailable(){
  return msgAvailable;
}

void MsgService::receiveMsg(){
  if (msgAvailable){
    Msg* msg = currentMsg;
    delay(100);
    Serial.println(msg->getContent());
    delay(100);
    this->notify();
    msgAvailable = false;
    currentMsg = NULL;
    content = "";
  }
}

void MsgService::notify() {
  Event<Msg> *e = new Event<Msg>(EventSourceType::MSG_SERVICE, this->currentMsg);  
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}

void MsgService::sendMsg(const String& msg){
  delay(100);
  Serial.println(msg);  
  delay(100);
}

void MsgService::serialEvent() {
  /* reading the content */
  while (Serial.available()) {
    char ch = (char) Serial.read();
    if (ch == '\n'){
      currentMsg = new Msg(content);
      msgAvailable = true;      
    } else {
      content += ch;      
    }
  }
}

void MsgService::update(Event<Msg> *e){
  this->sendMsg(e->getEventArgs()->getContent());
}


