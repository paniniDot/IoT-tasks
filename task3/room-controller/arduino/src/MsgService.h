#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "ArduinoJson.h"
#include "observer/EventSourceType.h"

class Msg {
  String content;

public:
  Msg(String content){
    this->content = content;
  }
  
  String getContent(){
    return content;
  }

// fai 3 funzioni separate per sensorName, timestamp e measure in modo da non passare per riferimento
  void ParseJson(String& sensorName, long& timestamp, String& measure) {
    DynamicJsonDocument doc(128); 
    deserializeJson(doc, content);

    sensorName = doc["name"].as<String>();
    timestamp = doc["timestamp"].as<long>();
    measure = doc["measure"].as<String>();
  }

};

class Pattern {
public:
  virtual boolean match(const Msg& m) = 0;  
};

class MsgServiceClass : Subject<Msg> {
    
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
