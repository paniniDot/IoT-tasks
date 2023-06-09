#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "ArduinoJson.h"
#include "observer/EventSourceType.h"

class Msg {
  String content;
  DynamicJsonDocument doc;

public:
  Msg(String content) : content(content), doc(128) {
    deserializeJson(doc, this->content);
  }
  
  String getContent(){
    return content;
  }

  String getSensorName() {
    return this->doc["name"].as<String>();
  }

  long getTimestamp() {
    return this->doc["timestamp"].as<long>();
  }

  bool getMeasure() {
    return this->doc["measure"].as<bool>();
  }

};

class Pattern {
public:
  virtual boolean match(const Msg& m) = 0;  
};

class MsgServiceClass :public  Subject<Msg> {
    
private:

  void notify();

public: 
  
  Msg* currentMsg;
  bool msgAvailable;


  void init();  

  bool isMsgAvailable();
  Msg* receiveMsg();

  bool isMsgAvailable(Pattern& pattern);

  /* note: message deallocation is responsibility of the client */
  Msg* receiveMsg(Pattern& pattern);
  
  void sendMsg(const String& msg);
};

extern MsgServiceClass MsgService;

#endif
