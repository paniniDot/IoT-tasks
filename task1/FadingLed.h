/*
  FadingLed.h - Library for encapsulating a fading led implementation.
  Created by Eleonora Falconi, Alesja Delja, Riccardo Fiorani, Mattia Panni. October 13, 2022.
  Released into the public domain.
*/
#ifndef FADING_LED_H
#define FADING_LED_H

#include "Arduino.h"
#include <inttypes.h>

class FadingLed 
{
    public:
        FadingLed(uint8_t pin, uint8_t fadeAmount, uint32_t delayTime);
        void fading();
        void powerOn();
        void powerOff();
    private:
        uint8_t _pin;
        uint8_t _fadeAmount;
        uint32_t _delay;
        uint8_t _currentBrightness;
};

#endif
