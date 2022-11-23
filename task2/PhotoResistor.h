#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__

class PhotoResistor {

  private:
    int pin;

  public:
    PhotoResistor(int pin);
    double measure();  

};

#endif