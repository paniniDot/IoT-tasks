#include "Arduino.h"
#include "MsgService.h"

String content;

MsgServiceClass MsgService;

bool MsgServiceClass::isMsgAvailable(){
  return msgAvailable;
}



void MsgServiceClass::receiveMsg(){
  if (msgAvailable){
    Msg* msg = currentMsg;
    Serial.println(msg->getContent());
    this->notify();
    msgAvailable = false;
    currentMsg = NULL;
    content = "";
  }
}



void MsgServiceClass::init(){
  Serial.begin(9600);
  content.reserve(512);
  content = "";
  currentMsg = NULL;
  msgAvailable = false;  
}

void MsgServiceClass::notify() {
  Event<Msg> *e = new Event<Msg>(EventSourceType::MSG_SERVICE, this->currentMsg);  
  for (int i = 0; i < this->getNObservers(); i++)
  {
    this->getObservers()[i]->update(e);
  }
  delete e;
}

void MsgServiceClass::sendMsg(const String& msg){
  Serial.println(msg);  
}

void serialEvent() {
  /* reading the content */
  while (Serial.available()) {
    char ch = (char) Serial.read();
    if (ch == '\n'){
      MsgService.currentMsg = new Msg(content);
      MsgService.msgAvailable = true;      
    } else {
      content += ch;      
    }
  }
}

bool MsgServiceClass::isMsgAvailable(Pattern& pattern){
  return (msgAvailable && pattern.match(*currentMsg));
}

void MsgServiceClass::receiveMsg(Pattern& pattern){
  if (msgAvailable && pattern.match(*currentMsg)){
    Msg* msg = currentMsg;
    msgAvailable = false;
    currentMsg = NULL;
    content = "";
  }
}


