#ifndef __PIR__
#define __PIR__

class Pir {
public:
  Pir(int pin);
  virtual int getMotion() = 0;  
};

#endif