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
  String roll_state;
  String light_State;
public: 
  MsgService(int rx, int tx);
  void notify();
  void print();
  void update(Event<Msg> *e);
};

#endif
