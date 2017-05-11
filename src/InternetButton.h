/*
 Arduino Library for Analog Devices ADXL362 - Micropower 3-axis accelerometer
 go to http://www.analog.com/ADXL362 for datasheet


 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!

 Created June 2012
 by Anne Mahaffey - hosted on http://annem.github.com/ADXL362

 Modified Mars 2014
 by pixelk

 Modified for Spark Core/Button October 2014
 Updated for Particle Photon July 2015
 by jenesaisdiq

 */

#include "application.h"

#ifndef InternetButton_h
#define InternetButton_h

//------------- InternetButton --------------

class InternetButton {

 public:

  InternetButton();

  void
    begin(void),
    begin(int i),
    setNumLeds(uint8_t i),
    allLedsOff(void),
    allLedsOn(uint8_t r, uint8_t g, uint8_t b),
    ledOn(uint8_t i, uint8_t r, uint8_t g, uint8_t b),
    ledOff(uint8_t i),
    rainbow(uint8_t wait),
    advanceRainbow(uint8_t amount, uint8_t wait),
    playNote(String note, int duration),
    playSong(String song),
    smoothLedOn(float i, uint8_t r, uint8_t g, uint8_t b),
    setBrightness(uint8_t),
    setBPM(int beats_per_minute);
  uint8_t
    buttonOn(uint8_t i),
    allButtonsOn(void),
    allButtonsOff(void),
    lowestLed(void),
    getBrightness(void);
  int
    readX(void),
    readY(void),
    readZ(void),
    readX16(void),
    readY16(void),
    readZ16(void),
    getBPM(void);
  uint32_t
    wheel(uint8_t WheelPos);

 private:

  int
    bpm = 250;

};


//----------------- LED Handling ------------------------
#define PIXEL_COUNT 11
//#define PIXEL_PIN D3
#define PIXEL_TYPE WS2812B

#endif // InternetButton_h
