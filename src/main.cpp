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

// Define Heads-Up Display for diagnostics.
Stream &hud(Serial);

// Create a rifle.
T800Westinghouse rifle = T800Westinghouse(hud);

/**
 * @brief One-time setup code here.
 * 
 */
void setup() {
  if(Serial) Serial.begin(115200);

  hud.print(F("\n\nCYBERDINE SYSTEMS (JSWARE DIVISION)\nWESTINGHOUSE M95A1 PHASED PLASMA RIFLE\n40W RANGE VERSION "));
  hud.println(F(VER_STRING));
  hud.println("\nSYSTEM RESTART");

  rifle.init();

  hud.println(F("SYSTEM RESTART COMPLETE\n"));
}

/**
 * @brief Main code here, to run repeatedly.
 * 
 */
void loop() {
  static int count = 0;
  char cmd = '\0';

  DIAG {
    hud.print(F("Loop "));
    hud.print(++count);
    hud.println("");
  }

  if(rifle.isTriggered()) {
    DIAG hud.println(F("Manual Fire"));
    rifle.setMode(T800Westinghouse::MODE_OFF);
    rifle.fire(4);
  } else if(hud.available()) {
    cmd = toupper(hud.read());

    switch(cmd) {
      case T800Westinghouse::MODE_RESET:
        hud.println(F("Resetting"));
        if (!rifle.reset()) {
          hud.println(F("WEAPON RESET FAILED SEEK ALTERNATIVE"));
          S_O_S();
        }
        break; 

      case T800Westinghouse::MODE_OFF:
        hud.println(F("Passive Mode"));
        rifle.setMode(cmd);
        break;

      case T800Westinghouse::MODE_AGGRESSIVE:
        hud.println(F("Aggressive Mode"));
        rifle.setMode(cmd);
        break;

      case T800Westinghouse::MODE_BELLIGERENT:
        hud.println(F("Belligerent Mode"));
        rifle.setMode(cmd);
        break;

      case T800Westinghouse::MODE_COMBATIVE:
        hud.println(F("Combative Mode"));
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
          hud.println(F("PRIMARY WEAPON DAMAGED SEEK ALTERNATIVE"));
        }
        break;
    }
  } else if(!random(0,10)) {
    rifle.fire();
  }
}
