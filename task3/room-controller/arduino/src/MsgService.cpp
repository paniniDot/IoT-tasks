#include "Arduino.h"
#include "MsgService.h"

MsgService::MsgService(){
  Serial.begin(9600);
  this->msg ="";
}

void MsgService::receiveMsg(){
   if (Serial.available()) {
    this->msg = Serial.readStringUntil('\n');
    this->notify();
  }
}

void MsgService::sendMsg(const String& msg){
  delay(100);
  Serial.println(msg);  
  delay(100);
}

void MsgService::notify() {
  Event<Msg> *e = new Event<Msg>(EventSourceType::MSG_SERVICE, new Msg(this->msg));  
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}

void MsgService::update(Event<Msg> *e){
  this->sendMsg(e->getEventArgs()->getContent());
}


