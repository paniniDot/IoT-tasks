#ifndef __SONAR__
#define __SONAR__

class Sonar {

  private:
    int triggerPin;
    int echoPin;

  public:
    Sonar(int triggerPin, int echoPin);
    virtual double measure() = 0;  

};

#endif