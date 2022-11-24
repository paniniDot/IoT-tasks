#ifndef __WATERLEVELTASK__
#define __WATERLEVELTASK__

#include "WaterLevelUtils.h"
#include "Task.h"
#include "Sonar.h"
#include "Potentiometer.h"
#include "PhotoResistor.h"
#include "Pir.h"
/*#include <Servo.h>
#include "Light.h"
#include "Button.h"
#include <LiquidCrystal.h>*/

class WaterLevelTask: public Task {
        
        private:
            Sonar* sonar;
            Potentiometer* pot;
            PhotoResistor* pho;
            Pir *pir;
            
            
            /*
            Servo* servo;
            Light* ledB;
            Light* ledC;
            Button* btn;
            LiquidCrystal* screen;*/
            State state;

            void normalStateHandler();
            void preAlarmStateHandler();
            void alarmStateHandler();
            double measureWaterLevel();
            void updateState(); 

        public:
            WaterLevelTask(Sonar* sonar, Potentiometer* pot,PhotoResistor* pho, Pir *pir/*, Servo* servo, Light* ledB, Light* ledC, Button btn,  LiquidCrystal* lcdScreen*/);
            void init();
            void tick();
};

#endif