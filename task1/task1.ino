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
  currentState = WAITING_USER_INPUT;
}

void waiting_user_input() {
  enableInterrupt(buttons[0], interrupt0Check, RISING);
  enableInterrupt(buttons[1], interrupt1Check, RISING);
  enableInterrupt(buttons[2], interrupt2Check, RISING);
  enableInterrupt(buttons[3], interrupt3Check, RISING);
  delay(2000);
  currentState = GAME_OVER;
}

void interruptCheck(int n) {
  user_input[n] = 1;
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

void game_over() {
  if (memcmp(led_states, user_input, LEDS) == 0) {
    Serial.println("you won!!");
  } else {
    Serial.println("you lost!!");
  }
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
      waiting_user_input();
      break;
    case GAME_OVER: game_over();
      break;
    default:
      handle_off_state();
      break;
  }
}