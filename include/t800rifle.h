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
#include <Ultrasonic.h>

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
    static const int PIN_TX = 2;  // Transmit Pin
    static const int PIN_RX = 3;  // Receive Pin
    static const int PIN_RST = 4; // Reset Pin
    static const int PIN_ACT = 5; // Activity (Play) Pin

    static const int PIN_LSR = 6; // Laser Pin
    static const int PIN_LED = 7; // LED Pin
    static const int PIN_TRG = 8; // Trigger Pin

    static const int PIN_SEN = 9;  // Sensoring Pin.
    static const int PIN_PIR = 10; // PIR Sensor Pin.
    static const int PIN_ECH = 11; // Ultrasonic Echo Pin.
    static const int PIN_SND = 12; // Trigger (Send) Pin.

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
     * @param txPin Transmit commands to SFX board (default PIN_TX).
     * @param rxPin  Receive responses from SFX board (default PIN_RX).
     * @param resetPin Reset SFX board (default PIN_RST).
     * @param actPin Monitor SFX playing activity.
     * @param ledPin Control muzzle flash.
     */
    T800Westinghouse();

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

    bool isActive() {return rifleMode == MODE_AGGRESSIVE;}
    
    /**
     * @brief Determine if the trigger is pressed
     * 
     * @return true Trigger button pressed.
     * @return false Trigger button not pressed.
     */
    bool isTriggered() {return (digitalRead(PIN_TRG) == LOW);}

    /**
     * @brief Determine if sensors are connected.
     * 
     * @return true Sensors connected.
     * @return false Sensors not connected.
     */
    bool isSensoring() {return (digitalRead(PIN_SEN) == LOW);}

    /**
     * @brief Determine if motion is detected.
     * 
     * @return true Motion detected.
     * @return false Motion not detected.
     */
    bool isMotionDetected();

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
    char rifleMode; // Operational mode.
    int lastFire; // Last fire sound used.

    Ultrasonic sr04; // SR04 ultrasonic sensor.
    int lastDistance; // Last sensoring distance recorded.

    char lineBuffer[80]; // Capture SFX board responses.
};

#endif /* INCLUDED_T800RIFLE_H */
