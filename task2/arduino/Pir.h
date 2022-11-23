#ifndef __PIR__
#define __PIR__

class Pir {

  private:
    int pin;

  public:
    Pir(int pin);
    virtual int getMotion() = 0;  

};

#endif