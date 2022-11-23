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
          /*WaterLevelUtils.State state;*/

        public:
            WaterLevelTask(Sonar* sonar, Servo* servo, Potentiometer* pot, Light* ledB, Light* ledC, /*Button btn,*/ LiquidCrystal* lcdScreen);
            void init();
            void tick();
};

#endif