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

/* Choose if using Ultrasonic SR04 sensor */
#undef USE_ULTRASONIC
#ifdef USE_ULTRASONIC
#include <SR04.h>
#endif

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
    static const int PIN_RX = 2;  // Receive from SFX Pin
    static const int PIN_TX = 3;  // Transmit to SFX Pin
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

    /**
     * @brief Identify if the rifle is active.
     * 
     * @return true 
     * @return false 
     */
    bool isActive() {return rifleMode != MODE_OFF;}
    
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

    /**
     * @brief Read line of text from soud board.
     * 
     * @return Length of characters read.
     */
    int readLine();

    /**
     * @brief Flash the muzzle in time with the sounds.
     * 
     * @param timings Flash timing to use.
     * @param laser Also flash the laser.
     */
    void muzzleFlash(const struct FlashTiming *timings, bool laser = false);

    /**
     * @brief Wait for the required number of milliseconds. An alternative to
     *        delay() which does not pause the Arduino (allows interrupts to
     *        continue running and handles if interrupts cause delays).
     * 
     * @param ms The number of milliseconds to wait (1000 = 1 second).
     */
    static void wait(unsigned long ms) {
        unsigned long t = millis() + ms;
        while(millis() < t);
    }
    
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

#ifdef USE_ULTRASONIC
    SR04 sr04; // SR04 ultrasonic sensor.
    int lastDistance; // Last sensoring distance recorded.
#endif

    char lineBuffer[80]; // Capture SFX board responses.
};

#endif /* INCLUDED_T800RIFLE_H */
