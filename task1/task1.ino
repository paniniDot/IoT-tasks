#define LEDS 4
#define MAX_PENALTIES 3

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

FadingLed debug_led(11, 5, 30);
long prevts = 0;
long ts;

int led_states[LEDS];
int user_input[LEDS];
int leds[LEDS] = { 10, 9, 8, 7 };
int buttons[LEDS] = { 6, 5, 4, 3 };

State currentState;

int pattern_time;
int user_input_time;
int decreasing_factor;

User user;

void setup() {
  Serial.begin(9600);
  setup_hw();
  setup_current_state();
  randomSeed(analogRead(0));
  pattern_time = 10000000;
  user_input_time = 10000000;
  decreasing_factor = 5000;
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
  //currentState = OFF;
  changeState(OFF);
}

void sleep_setup() {
  //currentState = SLEEP;
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
  }
  for (int i = 0; i < LEDS; i++) {
    analogWrite(leds[i], (led_states[i] == 0) ? 0 : 255);
  }
  delay(1000);
  for (int i = 0; i < LEDS; i++) {
    analogWrite(leds[i], 0);
  }
  changeState(WAITING_USER_INPUT);
}

void changeState(State newState) {
  currentState = newState;
  Serial.println(newState);
}

void waiting_user_input() {
  delay(5000);
  changeState(GAME_OVER);
}

void check_penality() {
  if (user.getPenalties() == 3) {
    Serial.println("you gameover!!");
    user.resetPenalties();
    user.resetScore();
    prevts = ts;
    currentState = OFF;
  }
}

void penality() {
  user.addPenalty();
  debug_led.powerOn();
  delay(1000);
  debug_led.powerOff();
}

void check_result() {
  if (memcmp(led_states, user_input, LEDS) == 0 && user.getPenalties() != MAX_PENALTIES) {
    user.incrementScore();
    pattern_time < decreasing_factor ? 0 : pattern_time - decreasing_factor;
    user_input_time < decreasing_factor ? 0 : user_input_time - decreasing_factor;
    Serial.print("you won!!");
    Serial.println(user.getCurrentScore());
  } else {
    penality();
    Serial.println("you lost!!");
  }
  for (int i = 0; i < LEDS; i++) {
    user_input[i] = 0;
  }
  changeState(SHOWING_PATTERN);
  check_penality();
}

void interruptCheck(int n) {
  switch (currentState) {
    case OFF:
      changeState(SHOWING_PATTERN);
      debug_led.powerOff();
      break;
    case SHOWING_PATTERN:
      penality();
      break;
    case WAITING_USER_INPUT:
      user_input[n] = 1;
      break;
    case GAME_OVER:
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