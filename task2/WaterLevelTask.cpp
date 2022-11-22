#include "Task.h"
#include "Sonar.h"
#include <Servo.h>
#include "Potentiometer.h"
#include "Light.h"
#include "Button.h"
#include <LiquidCrystal.h>


class WaterLevelTask : public Task {
        public:
            WaterLevelTask(Sonar sonar, Servo servo, Potentiometer pot, Light ledB, Light ledC, Button btn, LiquidCrystal lcdScreen);
            void init();
            void tick();
}