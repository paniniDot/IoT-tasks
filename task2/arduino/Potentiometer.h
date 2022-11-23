#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

class Potentiometer {

  private:
    int pin;

  public:
  Potentiometer(int pin);
    virtual double measure() = 0;  

};

#endif