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

void FadingLed::fading()
{
    uint8_t currentBrightness = 0;
    analogWrite(_pin, currentBrightness);
    currentBrightness += _fadeAmount;
    if(currentBrightness <= LOW || currentBrightness >= HIGH) {
        _fadeAmount = -_fadeAmount;
    }
    delay(_delay);
}

void FadingLed::powerOn()
{
    analogWrite(_pin, HIGH);
}

void FadingLed::powerOff() 
{
    analogWrite(_pin, LOW);
}
