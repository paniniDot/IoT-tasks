#ifndef __WATERLEVELTASK__
#define __WATERLEVELTASK__

#include "WaterLevelUtils.h"
#include "Task.h"
#include "Sonar.h"
#include <Servo.h>
#include "Potentiometer.h"
#include "Light.h"
#include "Button.h"
#include <LiquidCrystal.h>

class WaterLevelTask: public Task {
        
        private:
            Sonar* sonar;
            Servo* servo;
            Potentiometer* pot;
            Light* ledB;
            Light* ledC;
            /*Button* btn;*/
            LiquidCrystal* screen;
            State state;

            void normalStateHandler();
            void preAlarmStateHandler();
            void alarmStateHandler();
            double measureWaterLevel();
            void updateState(); 

        public:
            WaterLevelTask(Sonar* sonar, Servo* servo, Potentiometer* pot, Light* ledB, Light* ledC, /*Button btn,*/ LiquidCrystal* lcdScreen);
            void init();
            void tick();
};

#endif