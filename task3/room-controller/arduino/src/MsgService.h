#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"
#include "Msg.h"

class MsgService : public Subject<Msg>, public Observer<Msg> {
    
private:

  String content;
  void notify();
  void serialEvent();

public: 

  MsgService();
  Msg* currentMsg;
  bool msgAvailable;
  void update(Event<Msg> *e);
  bool isMsgAvailable();
  void receiveMsg();
  void sendMsg(const String& msg);
};

#endif
