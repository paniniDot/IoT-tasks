#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "observer/Subject.h"
#include "observer/Event.h"
#include "observer/EventSourceType.h"
#include "Msg.h"

class MsgService : public Subject<Msg>, public Observer<Msg> {
    
private:
  SoftwareSerial *bt;
public: 
  MsgService(int rx, int tx);
  void notify();
  void update(Event<Msg> *e);
};

#endif
