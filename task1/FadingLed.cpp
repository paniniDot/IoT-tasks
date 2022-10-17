#include "Arduino.h"
#include "FadingLed.h"

#define HIGH 255
#define LOW 0

FadingLed::FadingLed(uint8_t pin, uint8_t fadeAmount, uint32_t delayTime)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
    _fadeAmount = fadeAmount;
    _delay = delayTime;
}

FadingLed::fading()
{
    currentBrightness = 0;
    analogWrite(_pin, _fadeAmount);
    currentBrightness += _fadeAmount;
    if(currentBrightness <= LOW || currentBrightness >= HIGH) {
        _fadeAmount = -_fadeAmount;
    }
    delay(_delay);
}

FadingLed::powerOn()
{
    analogWrite(_pin, HIGH);
}

FadingLed::powerOff() 
{
    analogWrite(_pin, LOW);
}