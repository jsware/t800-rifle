/**
 * @file main.cpp
 * @author John Scott
 * @brief Westinghouse M95A1 Phased Plasma Rifle Control Program.
 * @version 1.0
 * @date 2021-11-11
 * 
 * @copyright Copyright (c) 2021 John Scott
 * 
 */
#include <Arduino.h>
#include "diags.h"
#include "t800rifle.h"
#include "ver_info.h"

// Create a rifle.
T800Westinghouse rifle = T800Westinghouse(Serial);

/**
 * @brief One-time setup code here.
 * 
 */
void setup() {
  if(Serial) Serial.begin(115200);

  Serial.print(F("\n\nCyberdine Systems (JSWare Division)\nWestinghouse M95A1 Phased Plasma Rifle\n40W Range Version "));
  Serial.println(F(VER_STRING));
  Serial.println("\nSystem Restart...");

  rifle.init();

  Serial.println(F("System Restart Complete"));
}

/**
 * @brief Main code here, to run repeatedly.
 * 
 */
void loop() {
  static int count = 0;
  char cmd = '\0';

  ++count;
  
  if(DEBUG) {
    Serial.print(F("Loop "));
    Serial.print(count);
    Serial.println("");
  }

  if(rifle.isTriggered()) {
    Serial.println(F("Manual Firing"));
    rifle.setMode(T800Westinghouse::MODE_OFF);
    rifle.fire(4);
  } else if(Serial.available()) {
    cmd = toupper(Serial.read());

    switch(cmd) {
      case T800Westinghouse::MODE_RESET:
        Serial.println(F("Resetting"));
        if (!rifle.reset()) {
          Serial.println(F("ERROR: Weapon reset failed"));
          S_O_S();
        }
        break; 

      case T800Westinghouse::MODE_OFF:
        Serial.println(F("Passive Mode"));
        rifle.setMode(cmd);
        break;

      case T800Westinghouse::MODE_AGGRESSIVE:
        Serial.println(F("Aggressive Mode"));
        rifle.setMode(cmd);
        break;

      case T800Westinghouse::MODE_BELLIGERENT:
        Serial.println(F("Belligerent Mode"));
        rifle.setMode(cmd);
        break;

      case T800Westinghouse::MODE_COMBATIVE:
        Serial.println(F("Combative Mode"));
        rifle.setMode(cmd);
        break;

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
        Serial.print(F("Fire Mode "));
        Serial.println(cmd);
        rifle.setMode(T800Westinghouse::MODE_OFF);
        if(!rifle.fire(cmd - '0')) {
          Serial.println(F("ERROR: PRIMARY WEAPON DAMAGED SEEK ALTERNATIVE"));
        }
        break;
    }
  } else if(!random(0,10)) {
    rifle.fire();
  }
}
