/**
 * @file t800rifle.cpp
 * @author John Scott
 * @brief Westinghouse M95A1 Phased Plasma Rifle
 * @version 1.0
 * @date 2021-11-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "t800rifle.h"
#include "diags.h"

/**
 * @brief Muzzle Flash on-off timings.
 * 
 */
struct FlashTiming {
  int onMilli;
  int offMilli;
};

// Dummy timing to mark end of timings.
#define END_TIMINGS {0,0}


T800Westinghouse::
T800Westinghouse()
: ss(PIN_TX,PIN_RX)
, rifleMode(MODE_DEFAULT)
, lastFire(-1)
, sr04(PIN_SND, PIN_ECH)
, lastDistance(sr04.read())
{

}


void T800Westinghouse::
init()
{
  Serial.println(F("Initialising I/O."));

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_ACT, INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LSR, OUTPUT);
  pinMode(PIN_TRG, INPUT_PULLUP);

  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_SEN, INPUT_PULLUP);

  Serial.println(F("Randomising."));
  randomSeed(analogRead(A0));  // Randomise

  Serial.println(F("Checking SFX Board."));
  ss.begin(9600);
  
  if (!reset()) {
    Serial.println(F("ERROR: Board not responding!"));
    while (true) {
      S_O_S();
      gap(EOW_LEN);
    }
  }
}


bool T800Westinghouse::
reset()
{
  digitalWrite(PIN_RST, LOW);
  pinMode(PIN_RST, OUTPUT);

  wait(10);
  
  pinMode(PIN_RST, INPUT);
  wait(1000); // Let it boot

  readLine();
  readLine();
  if (!strstr(lineBuffer, "Adafruit FX Sound Board")){
    return false;
  }

  wait(250);

  readLine(); // FAT type.
  readLine(); // Files found.

  return true;
}


bool T800Westinghouse::
isMotionDetected() {
  int pirValue = digitalRead(PIN_PIR);
  long distance = sr04.read();
  bool rc = false;
  
  if (pirValue || abs(lastDistance - distance) > lastDistance / 4) {
    Serial.print(("Motion! PIR: "));
    Serial.print(pirValue);
    Serial.print(" @ ");
    Serial.print(distance);
    Serial.print("cm (");
    Serial.print(lastDistance - distance);
    Serial.println(" cm)");

    rc = true;
    lastDistance = distance;
  }

  return rc;
}


int T800Westinghouse::
readLine() {
  int x = ss.readBytesUntil('\n', lineBuffer, sizeof(lineBuffer) - 1);
  lineBuffer[x] = '\0';

  if(x > 1) {
    Serial.println(lineBuffer);
  }

  return x;
}


bool T800Westinghouse::
fire(int n) {
  char c = '0' + n; // Convert file number to char '0' through '9'.

  Serial.println(FIRE_NAMES[n]);

  // Send #n to the SFX board.
  ss.print(F("#"));
  ss.println(c);

  readLine(); // eat return.
  readLine(); // SFX outcome.

  muzzleFlash(FLASH_TIMINGS[n], true);

  // Check we got "play" back.
  if (strstr(lineBuffer, "play") == 0) {
    return false;
  }

  readLine(); // SFX done.

  lastFire=n;
  return true;
}


bool T800Westinghouse::
fire() {
  bool rc = false;
  int thisFire;

  switch(rifleMode) {
    case MODE_AGGRESSIVE:
      do {
        thisFire=random(SOUND_COUNT);
      } while(thisFire == lastFire);

      lastFire = thisFire;
      rc = fire(thisFire);
      break;

    case MODE_BELLIGERENT:
      if(lastFire <= 0) lastFire = SOUND_COUNT;
      rc = fire(--lastFire);
      break;

    case MODE_COMBATIVE:
      if(lastFire >= SOUND_COUNT - 1) lastFire = -1;
      rc = fire(++lastFire);
      break;

    case MODE_OFF:
      rc = true;
      // Fall through.

    default:
      break;
  }

  if(!rc) {
    Serial.println("ERROR: Misfire!");
    S_O_S();
  }

  return rc;
}


void T800Westinghouse::
muzzleFlash(const struct FlashTiming *timings, bool laser)
{
  int ms = 0; // Play time in milliseconds (approx).

  // Control flash from each timing entry. Timings are ms from recording start
  // so convert to relative delay to flash-on and flash-off. Off time of 0ms
  // is dummy end-of-timings entry.
  while(timings->offMilli) {
    int onDelay = timings->onMilli - ms; // Delay to flash on.
    int offDelay = timings->offMilli - onDelay - ms; // Delay to flash off.
    
    // Wait to turn on flash.
    wait(onDelay);
    digitalWrite(PIN_LED, HIGH);
    if(laser) {
      digitalWrite(PIN_LSR, HIGH);
    }

    // Wait to turn off flash.
    wait(offDelay);
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_LSR, LOW);

    // Now we're at flash-off point, move to next flash.
    ms = timings->offMilli;
    timings++;

    // Abort sound if the trigger has been pressed.
    if(rifleMode != MODE_OFF && isTriggered()) {
      break;
    }
  }

  // delay till SFX board shows no play activity.
  do {
    wait(100);

    if(isTriggered()) {
      ss.print(F("q\n"));

      break; // Abort sequence
    }
  } while(!digitalRead(PIN_ACT));
}


void T800Westinghouse::
setMode(char mode)
{
  rifleMode = mode;

  switch(rifleMode) {
    case MODE_AGGRESSIVE:
      lastFire=random(SOUND_COUNT);
      break;

    case MODE_BELLIGERENT:
      lastFire = -1;
      break;

    case MODE_COMBATIVE:
      lastFire = SOUND_COUNT;
      break;

    case MODE_OFF:
    default:
      break;
  }
}


//
// Definitions of timings for each SFX file (T00.WAV through T07.WAV).
// Timings are in milliseconds from the start of the WAV file. muzzleFlash()
// converts them to relative delays so the flash coincides with the sound file.
//
const struct FlashTiming T00[] = {
  { 50, 150 },
  END_TIMINGS
};

const struct FlashTiming T01[] = {
  {  50, 150 },
  { 250, 350 },
  { 450, 550 },
  { 650, 750 },
  END_TIMINGS
};

const struct FlashTiming T02[] = {
  {  40, 100 },
  { 160, 220 },
  { 280, 340 },
  { 400, 460 },
  END_TIMINGS
};

const struct FlashTiming T03[] = {
  {  60, 130 },
  { 180, 245 },
  { 305, 367 },
  { 423, 485 },
  { 535, 596 },
  { 650, 750 },
  END_TIMINGS
};

const struct FlashTiming T04[] = {
  {  38,  75 },
  { 112, 149 },
  { 187, 225 },
  { 258, 296 },
  { 329, 366 },
  { 400, 460 },
  END_TIMINGS
};

const struct FlashTiming T05[] = {
  {   70,  132 },
  {  190,  254 },
  {  301,  385 },
  {  827,  890 },
  {  950, 1010 },
  { 1070, 1131 },
  { 1185, 1248 },
  { 1301, 1362 },
  { 1417, 1541 },
  END_TIMINGS
};

const struct FlashTiming T06[] = {
  {   58,  118 },
  {  180,  240 },
  {  289,  377 },
  {  815,  875 },
  {  936,  996 },
  { 1057, 1118 },
  { 1173, 1234 },
  { 1288, 1349 },
  { 1407, 1469 },
  { 1530, 1591 },
  { 1646, 1707 },
  { 1761, 1822 },
  { 1882, 1949 },
  { 2010, 2065 },
  { 2123, 2181 },
  { 2240, 2295 },
  { 2356, 2459 },
  END_TIMINGS
};

const struct FlashTiming T07[] = {
  {   35,   73 },
  {  110,  147 },
  {  177,  221 },
  {  501,  539 },
  {  576,  613 },
  {  651,  688 },
  {  722,  760 },
  {  793,  831 },
  {  864,  927 },
  { 1145, 1183 },
  { 1218, 1259 },
  { 1294, 1330 },
  { 1363, 1401 },
  { 1434, 1472 },
  { 1506, 1550 },
  { 1587, 1625 },
  { 1662, 1699 },
  { 1733, 1771 },
  { 1804, 1841 },
  { 1875, 1949 },
  END_TIMINGS
};

const struct FlashTiming T08[] = {
  {   3,   30 },
  END_TIMINGS
};

// The array of each file's timing.
const struct FlashTiming *T800Westinghouse::FLASH_TIMINGS[] = {
  T00, T01, T02, T03, T04, T05, T06, T07, T08
};

const char *T800Westinghouse::FIRE_NAMES[] = {
  "Single shot",
  "Four slow",
  "Four fast",
  "Six fast",
  "Six ultra fast",
  "Two short bursts",
  "Two long bursts",
  "Three bursts",
  "You are terminated"
};
