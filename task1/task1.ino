#define LEDS 4
#include <avr/sleep.h>
#include <stdbool.h>

enum State {OFF, BLINKING, WAITING_USER_INPUT, GAME_OVER};

int debug_led = 11;
int debug_led_brightness = 0;
int fadeAmount = 5;

bool led_states[LEDS];
bool user_input[LEDS];
int leds[LEDS] = {10, 9, 8, 7};
int buttons[LEDS] = {6, 5, 4, 3};
State currentState;

void setup() {
  Serial.begin(9600);
  setup_hw();
  setup_current_state();
  randomSeed(analogRead(0));
}

void setup_hw() {
  //configuring game leds and buttons
  for (int i=0; i<LEDS; i++) {
    //leds
    led_states[i] = false;
    pinMode(leds[i], OUTPUT);
    //buttons
    user_input[i] = false;
    pinMode(buttons[i], INPUT);
  }
  //configuring debug led
  pinMode(debug_led, OUTPUT);
}


void setup_current_state() {
  currentState = OFF;
}

void sleep_setup() {
  sleep_enable();
  attachInterrupt(0, wakeUp, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
}

void wakeUp() {
   
}

void random_sequence_generator() {
  for (int i=0; i<LEDS; i++) {
    led_states[i] = random(0, 1) & 1;
  }
}

void blink_debug_led() {
  analogWrite(debug_led, debug_led_brightness);
  debug_led_brightness += fadeAmount;
  if (debug_led_brightness <= 0 || debug_led_brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30);
}

void handle_off_state() {
  blink_debug_led();
}

void loop() {
  switch(currentState) {
    case OFF: handle_off_state();
    break;
    default: handle_off_state();
    break;
  }
}
