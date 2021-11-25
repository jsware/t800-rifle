/**
 * @file t800rifle.h
 * @author John Scott
 * @brief Class to control the Westinghouse M95A1 Phased Plasma Rifle.
 * @version 1.0
 * @date 2021-11-11
 * 
 * @copyright Copyright (c) 2021 John Scott.
 */
#ifndef INCLUDED_T800RIFLE_H
#define INCLUDED_T800RIFLE_H
#include <Arduino.h>
#include <SoftwareSerial.h>

/**
 * @brief Westinghouse M95A! Phased Plasma Rifle in a 40W Range.
 * 
 */
class T800Westinghouse
{
  public:
    //
    // Constants...
    //

    // AdaFruit Audio FX Mini Sound Board: https://www.adafruit.com/product/2341.
    static const int SFX_TX = 2;
    static const int SFX_RX = 3;
    static const int SFX_RST = 4;
    static const int SFX_ACT = 5;
    static const int SFX_LSR = 6;
    static const int SFX_LED = 7;

    // Unconnected AR PIN for random seed generation.
    static const int PIN_RND = 0;
    static const int PIN_TRG = 8;

    // Operational modes.
    static const char MODE_OFF = 'Q'; // No firing.
    static const char MODE_AGGRESSIVE = 'A'; // Random firing.
    static const char MODE_BELLIGERENT = 'B'; // Heavy to light firing.
    static const char MODE_COMBATIVE = 'C'; // Light to heavy firing.
    static const char MODE_RESET = 'R'; // Reset SFX board.
    static const char MODE_DEFAULT = MODE_AGGRESSIVE; // Default to random firing.

    // Number of sounds.
    static const int SOUND_COUNT = 9;

  public:
    //
    // Constructors...
    //

    /**
     * @brief Construct a new Westinghouse Rifle controller.
     * 
     * @param hud Heads-Up-Display for diagnostic output.
     * @param txPin Transmit commands to SFX board (default SFX_TX).
     * @param rxPin  Receive responses from SFX board (default SFX_RX).
     * @param resetPin Reset SFX board (default SFX_RST).
     * @param actPin Monitor SFX playing activity.
     * @param ledPin Control muzzle flash.
     */
    T800Westinghouse(Stream &hud,
                     uint8_t txPin = SFX_TX,
                     uint8_t rxPin = SFX_RX,
                     uint8_t resetPin = SFX_RST,
                     uint8_t actPin = SFX_ACT,
                     uint8_t ledPin = SFX_LED,
                     uint8_t lsrPin = SFX_LSR,
                     uint8_t trgPin = PIN_TRG);

  public:
    //
    // Accessors...
    //

    /**
     * @brief Initialise Westinghouse (called from setup() function).
     * 
     */
    void init();

    /**
     * @brief Reset SFX board to clear any error.
     * 
     * @return true SFX reset successfully.
     * @return false SFX failed to reset.
     */
    bool reset();

    /**
     * @brief Fire the rifle using current mode.
     * 
     * @return true Successful firing.
     * @return false Misfire error.
     */
    bool fire();

    /**
     * @brief Fire a specific sound.
     * 
     * @param sound Character FIRST_SOUND through LAST_SOUND to use. 
     * @return true Successful firing.
     * @return false Misfire error.
     */
    bool fire(int sound);

    /**
     * @brief Set the operational mode.
     * 
     * @param mode One of the MODE_* constants.
     */
    void setMode(char mode);

    /**
     * @brief Determine if the trigger is pressed
     * 
     * @return true Trigger button pressed.
     * @return false Trigger button not pressed.
     */
    bool isTriggered() {return (digitalRead(trgPin) == LOW);}

  private:
    //
    // Helpers...
    //
    int readLine();

    void muzzleFlash(const struct FlashTiming *timings, bool laser = false);

  private:
    //
    // Implementation...
    //

    // Array of Muzzle Flash Timings (each array item is an array of timings).
    static const struct FlashTiming *FLASH_TIMINGS[];
    static const char *FIRE_NAMES[]; // Names of each shot.

    SoftwareSerial ss; // SFX board serial communications.
    Stream &hud;  // Heads-up-Display for diagnostics.

    uint8_t resetPin; // Pin to reset SFX board.
    uint8_t actPin; // Pin to monitor SFX board activity.

    uint8_t ledPin; // Pin to control muzzle flash.
    uint8_t lsrPin; // Pin to control muzzle laser.
    uint8_t trgPin; // Pin to control manual firing trigger.
    
    char rifleMode; // Operational mode.
    int lastFire; // Last fire sound used.

    char lineBuffer[80]; // Capture SFX board responses.
};

#endif /* INCLUDED_T800RIFLE_H */
