#define LEDS 4
#define MAX_PENALTIES 3
#define POTENTIOMETER_PIN A0
#define DIFFICULTIES 4

#include <avr/sleep.h>
#include <stdbool.h>
#include <EnableInterrupt.h>
#include "User.h"
#include "FadingLed.h"

enum State { OFF,
             SHOWING_PATTERN,
             WAITING_USER_INPUT,
             GAME_OVER,
             SLEEP };

long prevts;
long ts;
bool penality;
int led_states[LEDS];
int user_input[LEDS];
int leds[LEDS] = { 12, 10, 8, 6 };
int buttons[LEDS] = { 11, 9, 7, 5 };
int decreasing_factors[DIFFICULTIES] = { 250, 500, 750, 1000 };
int pattern_time;
int user_input_time;
int decreasing_factor;

/*requires as parameters, in the following order
  - the pin in which the led is plugged
  - the step of brightness
  - how much delay between each step
*/
FadingLed debug_led(3, 5, 30);
State currentState;
User user;

void setup() {
  Serial.begin(9600);
  setup_hw();
  setup_current_state();
  randomSeed(analogRead(A0));
  decreasing_factor = decreasing_factors[getDifficulty()];
  pattern_time = 2000;
  user_input_time = 3500;
  penality = false;
  prevts = 0;
}

int getDifficulty() {
  return map(analogRead(POTENTIOMETER_PIN), 0, 1023, 0, 3);
}

void setup_hw() {
  //configuring game leds and buttons
  for (int i = 0; i < LEDS; i++) {
    //leds
    led_states[i] = 0;
    pinMode(leds[i], OUTPUT);
    //buttons
    user_input[i] = 0;
    pinMode(buttons[i], INPUT);
  }
  enableInterrupt(buttons[0], interrupt0Check, RISING);
  enableInterrupt(buttons[1], interrupt1Check, RISING);
  enableInterrupt(buttons[2], interrupt2Check, RISING);
  enableInterrupt(buttons[3], interrupt3Check, RISING);
}

void interrupt0Check() {
  interruptCheck(0);
}

void interrupt1Check() {
  interruptCheck(1);
}

void interrupt2Check() {
  interruptCheck(2);
}

void interrupt3Check() {
  interruptCheck(3);
}

void setup_current_state() {
  changeState(OFF);
}

void sleep_setup() {
  changeState(SLEEP);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
}

void check_time() {
  ts = micros();
  if (ts - prevts > 10000000) {
    prevts = ts;
    debug_led.powerOff();
    sleep_setup();
  }
}

void handle_off_state() {
  check_time();
  debug_led.fading();
}

void blinking() {
  for (int i = 0; i < LEDS; i++) {
    led_states[i] = random(0, 2);
    analogWrite(leds[i], 0);
  }
  delay(1000);
  for (int i = 0; i < LEDS; i++) {
    analogWrite(leds[i], (led_states[i] == 0) ? 0 : 255);
  }
  delay(pattern_time);
  for (int i = 0; i < LEDS; i++) {
    analogWrite(leds[i], 0);
  }
  changeState(WAITING_USER_INPUT);
}

void changeState(State newState) {
  currentState = newState;
}

void waiting_user_input() {
  changeState(GAME_OVER);
  delay(user_input_time);
}

void check_penality() {
  if (user.getPenalties() >= MAX_PENALTIES) {
    Serial.print("Game over!! Final Score: ");
    Serial.println(user.getCurrentScore());
    user.resetPenalties();
    user.resetScore();
    prevts = micros();
    changeState(OFF);
  }
}
void add_penality() {
  user.addPenalty();
  debug_led.powerOn();
  delay(1000);
  debug_led.powerOff();
  check_penality();
}

void check_result() {
  changeState(SHOWING_PATTERN);
  if (memcmp(led_states, user_input, LEDS) == 0 && penality == false) {
    user.incrementScore();
    pattern_time -= decreasing_factor;
    user_input_time -= decreasing_factor;
    Serial.print("New point!! Score: ");
    Serial.println(user.getCurrentScore());
  } else {
    Serial.println("Penalty!");
    add_penality();
  }
  for (int i = 0; i < LEDS; i++) {
    user_input[i] = 0;
  }
  penality = false;
}

void interruptCheck(int n) {
  switch (currentState) {
    case OFF:
      if (n == 0) {
        debug_led.powerOff();
        changeState(SHOWING_PATTERN);
      }
      break;
    case SHOWING_PATTERN:
      penality = true;
      break;
    case WAITING_USER_INPUT:
      break;
    case GAME_OVER:
      analogWrite(leds[n], 255);
      user_input[n] = 1;
      break;
    case SLEEP:
      sleep_disable();
      changeState(OFF);
      break;
    default:
      break;
  }
}

void loop() {
  switch (currentState) {
    case OFF:
      handle_off_state();
      break;
    case SHOWING_PATTERN:
      blinking();
      break;
    case WAITING_USER_INPUT:
      waiting_user_input();
      break;
    case GAME_OVER:
      check_result();
      break;
    case SLEEP:
      break;
    default:
      handle_off_state();
      break;
  }
}