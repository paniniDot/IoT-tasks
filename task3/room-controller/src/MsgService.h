#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"
#include "Msg.h"

class MsgService : public Subject<Msg>, public Observer<Msg> {
    
private:

  String msg;
  void notify();

public: 

  MsgService();
  void update(Event<Msg> *e);
  void receiveMsg();
  void sendMsg(const String& msg);
};

#endif
