// You know the routine by now, just going to comment on the new things!

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

#include "InternetButton/InternetButton.h"

InternetButton b = InternetButton();

void setup() {
    // uncomment to enable Serial logging to see note output
    Serial.begin(9600);

    b.begin();

    // Set the BPM if you desire, the default is 250
    b.setBPM(250);

    // playSong takes a string in the format
    // "NOTE,TYPE,NOTE,TYPE..."
    // Types are note types that define duration so
    // 8 is a 1/8th note and 4 is a 1/4 note
    b.playSong("C4,8,E4,8,G4,8,C5,8,G5,4\n");
}

void loop() {
    if(b.allButtonsOn()){
        b.rainbow(10);
        b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8\n");
        b.allLedsOff();
    }

    if(b.buttonOn(1)){
        // playNote just plays a single note, and takes
        // a note name as a string and a note type as an int
        // Note types define duration like in scored music, so
        // 8 is a 1/8th note and 4 is a 1/4 note
        b.playNote("G3",8);
    }

    if(b.buttonOn(2)){
        b.playNote("G4",8);
    }

    if(b.buttonOn(3)){
        b.playNote("G5",8);
    }

    if(b.buttonOn(4)){
        b.playNote("G6",8);
    }
}