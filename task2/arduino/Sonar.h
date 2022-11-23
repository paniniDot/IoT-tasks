#ifndef __SONAR__
#define __SONAR__

class Sonar {

  private:
    int triggerPin;
    int echoPin;

  public:
    Sonar(int triggerPin, int echoPin);
    double measure();  

};

#endif