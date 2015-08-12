// You know the routine by now, just going to comment on the new things!

#include "InternetButton/InternetButton.h"

InternetButton b = InternetButton();

void setup() {
    b.begin();
    
    // playSong takes a string in the format
    // "NOTE,TYPE,NOTE,TYPE..."
    // Types are note types that define duration so 
    // 8 is a 1/8th note and 4 is a 1/4 note
    b.playSong("C4,8,E4,8,G4,8,C5,8,G5,4");
}

void loop() {
    if(b.allButtonsOn()){
        b.rainbow(10);
        b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8");
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