#include "InternetButton.h"
#include "neopixel.h"
#include "ADXL362.h"
#include <math.h>
//----------------- Button ----------------//

uint8_t pin = 3;
uint8_t b1 = 4;
uint8_t b2 = 5;
uint8_t b3 = 6;
uint8_t b4 = 7;

// start with pixel output not floating to avoid random pixels turning on during power-up
STARTUP(pinMode(pin, INPUT_PULLDOWN);)

Adafruit_NeoPixel ring = Adafruit_NeoPixel(PIXEL_COUNT, pin, PIXEL_TYPE);
ADXL362 accelerometer;

InternetButton::InternetButton(){

}

void InternetButton::begin(){
    ring.begin();
    ring.show();

    accelerometer.begin();                   // Setup SPI protocol, issue device soft reset
    accelerometer.beginMeasure();            // Switch ADXL362 to measure mode
    // Uncomment to enable diagnostic info
    // accelerometer.checkAllControlRegs();     // Burst Read all Control Registers, to check for proper setup

    pinMode(b1, INPUT_PULLUP);
    pinMode(b2, INPUT_PULLUP);
    pinMode(b3, INPUT_PULLUP);
    pinMode(b4, INPUT_PULLUP);
}

void InternetButton::begin(int i){
    if(i == 1 || i == 0){
        pin = 17;
        b1 = 1;
        b2 = 2;
        b3 = 3;
        b4 = 4;
    }

    ring.begin();
    ring.setPin(pin);
    ring.show();

    accelerometer.begin();                   // Setup SPI protocol, issue device soft reset
    accelerometer.beginMeasure();            // Switch ADXL362 to measure mode
    accelerometer.checkAllControlRegs();     // Burst Read all Control Registers, to check for proper setup

    pinMode(b1, INPUT_PULLUP);
    pinMode(b2, INPUT_PULLUP);
    pinMode(b3, INPUT_PULLUP);
    pinMode(b4, INPUT_PULLUP);
}

/* If you solder on a 12th LED (WS2812B), then you'll want to call
 * this function b.setNumLeds(12); after you call b.begin(); Any number of
 * LEDs can also be soldered onto the output of the button.
 */
void InternetButton::setNumLeds(uint8_t i) {
    ring.updateLength(i);
}

void InternetButton::ledOn(uint8_t i, uint8_t r, uint8_t g, uint8_t b){
    //i-1 shifts the location from human readable to the right index for the LEDs
    if(i == 12 && ring.getNumLeds() < 12){
        ring.setPixelColor(0, ring.Color(r,g,b));
        ring.setPixelColor(10, ring.Color(r,g,b));
    }
    else{
        ring.setPixelColor(i-1, ring.Color(r,g,b));
    }
    ring.show();
}

void InternetButton::smoothLedOn(float i, uint8_t r, uint8_t g, uint8_t b){
    //uint8_t intI = lrintf(i);
    //Serial.print("intI: ");
    //Serial.println(intI);

    //float differ = i-(float)intI + 0.5;
    //Serial.print("differ: ");
    //Serial.println(differ);

    float tempI;
    float differ = modff(i, &tempI);
    uint8_t intI = (uint8_t)tempI;


    // checks to see if it's reeeeally close to being an integer
    //if(abs(differ) < 0.01){
      // intI-1 shifts the location from human readable to the right index for the LEDs
    //  ring.setPixelColor(intI-1, ring.Color(r,g,b));
    //  Serial.println("tripped int check");
    //}
    //else {
      // diff > 0 means that it's closer to the lower one
      float differ1 = 1.0-differ;
      //differ1 = logf(differ1);
      //differ = logf(differ);
      if(differ > 0.5){
        differ1 /= 2;
        //ring.setPixelColor(intI-2, ring.Color((int)(differ1*r),(int)(differ1*g),(int)(differ1*b)));
        ring.setPixelColor(intI-1, ring.Color((int)(differ1*r),(int)(differ1*g),(int)(differ1*b)));
        ring.setPixelColor(intI, ring.Color((int)(differ*r),(int)(differ*g),(int)(differ*b)));
      }
      else {
        differ /= 2;
        //ring.setPixelColor(intI-2, ring.Color((int)(differ*r),(int)(differ*g),(int)(differ*b)));
        ring.setPixelColor(intI-1, ring.Color((int)(differ1*r),(int)(differ1*g),(int)(differ1*b)));
        ring.setPixelColor(intI, ring.Color((int)(differ*r),(int)(differ*g),(int)(differ*b)));
      }
    //}
    ring.show();
}

void InternetButton::ledOff(uint8_t i){
    ledOn(i,0,0,0);
}

void InternetButton::allLedsOff(){
    for(int i = 0; i<PIXEL_COUNT; i++){
            ring.setPixelColor(i, ring.Color(0, 0, 0));
    }
    ring.show();
}

void InternetButton::allLedsOn(uint8_t r, uint8_t g, uint8_t b){
    for(int i = 0; i<PIXEL_COUNT; i++){
            ring.setPixelColor(i, ring.Color(r, g, b));
    }
    ring.show();
}

uint8_t InternetButton::buttonOn(uint8_t i){
    if(b1 == 4){
        return !digitalRead(i+3);
    }
    else {
        return !digitalRead(i);
    }
}

uint8_t InternetButton::allButtonsOn(){
    if(!digitalRead(b1) && !digitalRead(b2) && !digitalRead(b3) && !digitalRead(b4)) {
        return 1;
    }
    else {
        return 0;
    }
}

uint8_t InternetButton::allButtonsOff(){
    if(digitalRead(b1) && digitalRead(b2) && digitalRead(b3) && digitalRead(b4)) {
        return 1;
    }
    else {
        return 0;
    }
}

uint32_t InternetButton::wheel(uint8_t WheelPos) {
  if(WheelPos < 85) {
   return ring.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return ring.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return ring.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void InternetButton::rainbow(uint8_t wait) {
    uint16_t i, j;

    for(j=0; j<256; j++) { // 1 cycle of all colors on wheel
        for(i=0; i< 12; i++) {
            uint8_t idx = ((i * 256 / ring.numPixels()) + j) & 255;
            ring.setPixelColor(i, wheel(idx));
        }
        ring.show();
        delay(wait);
    }
}

void InternetButton::advanceRainbow(uint8_t amount, uint8_t wait) {
    uint16_t i;
    static uint16_t j = 0;

    if (amount == 0) {
        j = 0;
        return;
    }

    if (j < 256) {
        j += amount;
    } else {
        j = 0;
    }

    for(i=0; i< 12; i++) {
        uint8_t idx = ((i * 256 / ring.numPixels()) + j) & 255;
        ring.setPixelColor(i, wheel(idx));
    }
    ring.show();
    if (wait > 0) delay(wait);
}

int InternetButton::readX(){
    return accelerometer.readX();
}

int InternetButton::readY(){
    return accelerometer.readY();
}

int InternetButton::readZ(){
    return accelerometer.readZ();
}

int InternetButton::readX16(){
    return accelerometer.readX16();
}

int InternetButton::readY16(){
    return accelerometer.readY16();
}

int InternetButton::readZ16(){
    return accelerometer.readZ16();
}

//Thanks christophevg!
uint8_t InternetButton::lowestLed(){
    float rads = atan2(accelerometer.readY16(),accelerometer.readX16());
    uint8_t ledPos = (uint8_t)(12 - (rads/(M_PI/6) - 3)) % 12;
    return ledPos;
}

void InternetButton::setBrightness(uint8_t brightness) {
    ring.setBrightness(brightness);
}

uint8_t InternetButton::getBrightness() {
    return ring.getBrightness();
}

int InternetButton::getBPM() {
    return bpm;
}

void InternetButton::setBPM(int beats_per_minute) {
    bpm = beats_per_minute;
}

void InternetButton::playSong(String song){
    char inputStr[song.length()];
    song.toCharArray(inputStr,song.length());

    // Uncomment for debugging, will affect BPM.
    // Serial.println(inputStr);

    char *note = strtok(inputStr,",");
    char *duration = strtok(NULL,", \n");

    while (duration != NULL) {
        playNote(note,String(duration).toInt());
        // Uncomment for debugging, will affect BPM.
        // Serial.printlnf("note: %s dur: %s", note, duration);
        note = strtok(NULL,",");
        duration = strtok(NULL,", \n");
    }
}

/*
 * Supports all notes, sharp and flat.  Sharp can be 's','S' or '#'. Flat can be 'b' or 'B'.
 * Octaves supported are 0-9, however only part of 0 is audible.
 * Rest notes require a duration just like regular notes and can be 'r','R',"rest" or "REST".
 * All song strings should end with ',',' ' or '\n' or else the last digit in a multi-digit
 * duration will be truncated, i.e. 16 will become 1.
 *
 * // EXAMPLE USAGE
 * b.playSong("C0,8,CS0,8,D0,8,DS0,8,E0,8,F0,8,FS0,8,G0,8,GS0,8,A0,8,AS0,8,B0,8\n");
 * b.playSong("C1,8,CS1,8,D1,8,DS1,8,E1,8,F1,8,FS1,8,G1,8,GS1,8,A1,8,AS1,8,B1,8\n");
 * b.playSong("C2,8,Cs2,8,D2,8,Ds2,8,E2,8,F2,8,Fs2,8,G2,8,Gs2,8,A2,8,As2,8,B2,8\n");
 * b.playSong("C3,8,DB3,8,D3,8,EB3,8,E3,8,F3,8,GB3,8,G3,8,AB3,8,A3,8,BB3,8,B3,8\n");
 * b.playSong("C4,8,Db4,8,D4,8,Eb4,8,E4,8,F4,8,Gb4,8,G4,8,Ab4,8,A4,8,Bb4,8,B4,8\n");
 * b.playSong("c5,8,db5,8,d5,8,eb5,8,e5,8,f5,8,gb5,8,g5,8,ab5,8,a5,8,bb5,8,b5,8\n");
 * b.playSong("C6,8,C#6,8,D6,8,D#6,8,E6,8,F6,8,F#6,8,G6,8,G#6,8,A6,8,A#6,8,B6,8\n");
 * b.playSong("C7,8,R,8,D7,8,REST,8,E7,8,F7,8,R,8,G7,8,REST,8,A7,8,R,8,B7,8\n");
 * b.playSong("C8,16,CS8,16,D8,16,DS8,16,E8,16,F8,16,FS8,16,G8,16,GS8,16,A8,16,AS8,16,B8,16\n");
 * b.playSong("C9,32,CS9,32,D9,32,DS9,32,E9,32,F9,32,FS9,32,G9,32,GS9,32,A9,32,AS9,32,B9,32,C9,32,CS9,32,D9,32,DS9,32,E9,32,F9,32,FS9,32,G9,32,GS9,32,A9,32,AS9,32,B9,32\n");
 */
void InternetButton::playNote(String note, int duration) {

    int noteNum = 0;
    int noteSharp = 0;
    int noteFlat = 0;
    int octave = 5;
    int freq = 256;

    int octIndex = note.length()-1; // octave is the last char
    String tempOctave = note.substring(octIndex, octIndex+1);
    octave = tempOctave.toInt();
    String tempNote = note.substring(0, octIndex);
    tempNote.toUpperCase();
    if (tempNote.length()==2) {
        if (tempNote.charAt(1)=='S' || tempNote.charAt(1)=='#') {
            noteSharp = 1;
        } else if (tempNote.charAt(1)=='B') {
            noteFlat = 1;
        }
    }

    // Using 240 instead of 250 after calibrating at 60 BPM and 240 BPM with a stopwatch.
    // Seems to work well with and without Serial logging, so that is ok to leave uncommented below.
    if (duration != 0) {
        duration = 1000*240/bpm/duration;
    }

    switch (tempNote.charAt(0)) {
        case 'C':
            noteNum = 0 + noteSharp;
            break;
        case 'D':
            noteNum = 2 + noteSharp - noteFlat;
            break;
        case 'E':
            noteNum = 4 - noteFlat;
            break;
        case 'F':
            noteNum = 5 + noteSharp;
            break;
        case 'G':
            noteNum = 7 + noteSharp - noteFlat;
            break;
        case 'A':
            noteNum = 9 + noteSharp - noteFlat;
            break;
        case 'B':
            noteNum = 11 - noteFlat;
            break;
        case 'R': // Rest note 'R' or 'REST'
            octave = -1;
            break;
        default:
            break;
    }

    // based on equation at http://www.phy.mtu.edu/~suits/NoteFreqCalcs.html and the Verdi tuning
    // fn = f0*(2^1/12)^n where n = number of half-steps from the reference frequency f0
    freq = float(256*pow(1.05946,(     12.0*(octave-4)        +noteNum)));
    //          C4^  (2^1/12)^    12 half-steps in an octave      ^how many extra half-steps within that octave, 0 for 'C'

    // Serial.printlnf("%-3s o:%-2d f:%-5d d:%d", tempNote.c_str(), octave, int(freq), duration);

    if (octave != -1) tone(D0, int(freq), duration);
    delay(duration);
    if (octave != -1) noTone(D0);
}
