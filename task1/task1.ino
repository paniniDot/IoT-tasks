#define LEDS 4
#include <avr/sleep.h>
#include <stdbool.h>
#include <EnableInterrupt.h>


enum State { OFF,
             BLINKING,
             WAITING_USER_INPUT,
             GAME_OVER };

int debug_led = 11;
int debug_led_brightness = 0;
int fadeAmount = 5;
long prevts = 0;
long ts;

int led_states[LEDS];
int user_input[LEDS];
int leds[LEDS] = { 10, 9, 8, 7 };
int buttons[LEDS] = { 6, 5, 4, 3 };
State currentState;

void setup() {
  Serial.begin(9600);
  setup_hw();
  setup_current_state();
  randomSeed(analogRead(0));
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
    enableInterrupt(buttons[i], interruptCheckState, RISING);
  }
  //configuring debug led
  pinMode(debug_led, OUTPUT);
}


void setup_current_state() {
  currentState = OFF;
}

void sleep_setup() {
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void blinking() {
  for (int i = 0; i < LEDS; i++) {
    led_states[i] = random(0, 2);
  }
  delay(1000);
  for (int i = 0; i < LEDS; i++) {
    analogWrite(leds[i], (led_states[i] == 0) ? 0 : 255);
  }
  delay(1000);
  currentState = WAITING_USER_INPUT;
}

void handle_off_state() {
  ts = micros();
  if (ts - prevts > 10000000) {
    //Serial.print("10 secondi passati");
    //break;
  }
  analogWrite(debug_led, debug_led_brightness);
  debug_led_brightness += fadeAmount;
  if (debug_led_brightness <= 0 || debug_led_brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30);
}

void interruptCheckState() {
  switch (currentState) {
    case OFF:
      currentState = BLINKING;
      analogWrite(debug_led, 0);
      Serial.print("interrupt");
      break;
    case BLINKING:
      break;
    case WAITING_USER_INPUT:
      break;
    case GAME_OVER:
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
    case BLINKING:
      blinking();
      break;
    case WAITING_USER_INPUT:
      break;
    case GAME_OVER:
      break;
    default:
      handle_off_state();
      break;
  }
}