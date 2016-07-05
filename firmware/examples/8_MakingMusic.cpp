// You know the routine by now, just going to comment on the new things!

#include "InternetButton/InternetButton.h"

InternetButton b = InternetButton();

// This is our Nyan Cat song definition
const char nyan_cat_intro[] = "DS5,16,E5,16,FS5,8,B5,8,DS5,16,E5,16,FS5,16,B5,16,CS6,16,DS6,16,CS6,16,AS5,16,B5,8,FS5,8,DS5,16,E5,16,FS5,8,B5,8,CS6,16,AS5,16,B5,16,CS6,16,E6,16,DS6,16,E6,16,B5,16\n";
const char nyan_cat_melody[] = "FS5,8,GS5,8,DS5,16,DS5,16,R,16,B4,16,D5,16,CS5,16,B4,16,R,16,B4,8,CS5,8,D5,8,D5,16,CS5,16,B4,16,CS5,16,DS5,16,FS5,16,GS5,16,DS5,16,FS5,16,CS5,16,DS5,16,B4,16,CS5,16,B4,16,DS5,8,FS5,8,GS5,16,DS5,16,FS5,16,CS5,16,DS5,16,B4,16,D5,16,DS5,16,D5,16,CS5,16,B4,16,CS5,16,D5,8,B4,16,CS5,16,DS5,16,FS5,16,CS5,16,DS5,16,CS5,16,B4,16,CS5,8,B4,8,CS5,8,FS5,8,GS5,8,DS5,16,DS5,16,R,16,B4,16,D5,16,CS5,16,B4,16,R,16,B4,8,CS5,8,D5,8,D5,16,CS5,16,B4,16,CS5,16,DS5,16,FS5,16,GS5,16,DS5,16,FS5,16,CS5,16,DS5,16,B4,16,CS5,16,B4,16,DS5,8,FS5,8,GS5,16,DS5,16,FS5,16,CS5,16,DS5,16,B4,16,D5,16,DS5,16,D5,16,CS5,16,B4,16,CS5,16,D5,8,B4,16,CS5,16,DS5,16,FS5,16,CS5,16,DS5,16,CS5,16,B4,16,CS5,8,B4,8,CS5,8,B4,8,FS4,16,GS4,16,B4,8,FS4,16,GS4,16,B4,16,CS5,16,DS5,16,B4,16,E5,16,DS5,16,E5,16,FS5,16,B4,8,B4,8,FS4,16,GS4,16,B4,16,FS4,16,E5,16,DS5,16,CS5,16,B4,16,FS4,16,DS4,16,E4,16,FS4,16,B4,8,FS4,16,GS4,16,B4,8,FS4,16,GS4,16,B4,16,B4,16,CS5,16,DS5,16,B4,16,FS4,16,GS4,16,FS4,16,B4,8,B4,16,AS4,16,B4,16,FS4,16,GS4,16,E4,16,E5,16,DS5,16,E5,16,FS5,16,B4,8,AS4,8,B4,8,FS4,16,GS4,16,B4,8,FS4,16,GS4,16,B4,16,CS5,16,DS5,16,B4,16,E5,16,DS5,16,E5,16,FS5,16,B4,8,B4,8,FS4,16,GS4,16,B4,16,FS4,16,E5,16,DS5,16,CS5,16,B4,16,FS4,16,DS4,16,E4,16,FS4,16,B4,8,FS4,16,GS4,16,B4,8,FS4,16,GS4,16,B4,16,B4,16,CS5,16,DS5,16,B4,16,FS4,16,GS4,16,FS4,16,B4,8,B4,16,AS4,16,B4,16,FS4,16,GS4,16,B4,16,E5,16,DS5,16,E5,16,FS5,16,B4,8,CS5,8\n";

// Prototypes of the functions that we'll use
bool isPaused();
void otherTasks();
void playSongAndProcess(String song);

void setup() {
    b.begin();

    // Set the BPM if you desire, the default is 250
    b.setBPM(250);

    // playSong takes a string in the format
    // "NOTE,TYPE,NOTE,TYPE..."
    // Types are note types that define duration so
    // 16 is a 1/16th note, 8 is a 1/8th note and 4 is a 1/4 note, etc..
    // (SEE A FULL DESCRIPTION OF playSong() at the end of this file)
    // Here we will go up the complete scale in the 5th octave as 1/8th notes:
    b.playSong("C5,16,C#5,16,D5,16,D#5,16,E5,16,F5,16,F#5,16,G5,16,G#5,16,A5,16,A#5,16,B5,16\n");

    // playNote just plays a single note, and takes
    // a note name as a string and a note type as an int
    // Note types define duration like in scored music, so
    // 16 is a 1/16th note, 8 is a 1/8th note and 4 is a 1/4 note, etc..
    // And now we will go back down the complete scale using flat semi-tones
    // instead of their sharp counterparts (5th octave as 1/8th notes):
    b.playNote("Bb5",16);
    b.playNote("A5",16);
    b.playNote("Ab5",16);
    b.playNote("G5",16);
    b.playNote("Gb5",16);
    b.playNote("F5",16);
    b.playNote("E5",16);
    b.playNote("Eb5",16);
    b.playNote("D5",16);
    b.playNote("Db5",16);
    b.playNote("C5",16);
    delay(500);

    // Now let's get ready to play Nyan Cat
    b.setBrightness(255); // 0 - 255
    b.setBPM(142); // Nyan Cat BPM is 142
    playSongAndProcess(nyan_cat_intro); // play the intro
}

void loop() {
    // Now loop the melody forever! You may pause the song by pressing any button :)
    playSongAndProcess(nyan_cat_melody);
}



/*********************************
 * Below are our helper functions
 *********************************/

// If any button is pressed, toggle `paused` and return it's value
bool isPaused() {
    static bool paused = false;
    if ( b.buttonOn(1) || b.buttonOn(2) || b.buttonOn(3) || b.buttonOn(4)) {
        delay(50);
        paused = !paused;
        // wait until button is released
        while ( b.buttonOn(1) || b.buttonOn(2) || b.buttonOn(3) || b.buttonOn(4));
        delay(50);
    }
    return paused;
}

// Called once per note in the song
void otherTasks() {
    b.advanceRainbow(25, 0);
    while (isPaused()) {        // while paused...
        b.setBrightness(50);    // dim the LEDs
        b.advanceRainbow(1, 2); // smoother rainbow
        Particle.process();     // keep our Cloud connection going
    }
    b.setBrightness(255); // re-brighten the jam!
}

/* This is the InternetButton::playSong(String song) routine
 * pulled out here so we can call advanceRainbow() and read
 * buttons in-between playing notes!
 */
void playSongAndProcess(String song){
    char inputStr[song.length()];
    song.toCharArray(inputStr,song.length());
    char* note = strtok(inputStr,",");
    char* duration = strtok(NULL,", \n");

    while (duration != NULL) {
        // Play the note, and then process otherTasks()
        b.playNote(note, atoi(duration));
        otherTasks();

        // advance the note
        note = strtok(NULL,",");
        duration = strtok(NULL,", \n");
    }
}

/*
 * b.playSong(String)
 *
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
