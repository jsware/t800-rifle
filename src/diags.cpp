/**
 * @file diags.cpp
 * @author John Scott
 * @brief Built-in LED Diagnostics (Morse Code)
 * @version 1.0
 * @date 2021-11-11
 * 
 * @copyright Copyright (c) 2021 John Scott
 * 
 */
#include <Arduino.h>
#include "diags.h"

#define SPEED 180

void wait(unsigned long ms) {
  unsigned long t = millis() + ms;

  while(millis() < t);
}

void dit(int count) {
  for(int i=0; i < count; ++i) {
    digitalWrite(LED_BUILTIN, HIGH);
    wait(DIT_LEN * SPEED);
    digitalWrite(LED_BUILTIN, LOW);
    wait(DIT_LEN * SPEED);
  }
}

void dah(int count) {
  for(int i=0; i < count; ++i) {
    digitalWrite(LED_BUILTIN, HIGH);
    wait(DAH_LEN * SPEED);
    digitalWrite(LED_BUILTIN, LOW);
    wait(DIT_LEN * SPEED);
  }
}

void gap(int count) {
  wait(DIT_LEN * SPEED * count);
}

void S_O_S() {
  dit(3);
  dah(3);
  dit(3);
}