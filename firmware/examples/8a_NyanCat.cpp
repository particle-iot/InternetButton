// This #include statement was automatically added by the Particle IDE.
#include "InternetButton/InternetButton.h"

InternetButton b = InternetButton();

const char nyan_cat_intro[] = "DS5,16,E5,16,FS5,8,B5,8,DS5,16,E5,16,FS5,16,B5,16,CS6,16,DS6,16,CS6,16,AS5,16,B5,8,FS5,8,DS5,16,E5,16,FS5,8,B5,8,CS6,16,AS5,16,B5,16,CS6,16,E6,16,DS6,16,E6,16,B5,16\n";
const char nyan_cat_melody[] = "FS5,8,GS5,8,DS5,16,DS5,16,R,16,B4,16,D5,16,CS5,16,B4,16,R,16,B4,8,CS5,8,D5,8,D5,16,CS5,16,B4,16,CS5,16,DS5,16,FS5,16,GS5,16,DS5,16,FS5,16,CS5,16,DS5,16,B4,16,CS5,16,B4,16,DS5,8,FS5,8,GS5,16,DS5,16,FS5,16,CS5,16,DS5,16,B4,16,D5,16,DS5,16,D5,16,CS5,16,B4,16,CS5,16,D5,8,B4,16,CS5,16,DS5,16,FS5,16,CS5,16,DS5,16,CS5,16,B4,16,CS5,8,B4,8,CS5,8,FS5,8,GS5,8,DS5,16,DS5,16,R,16,B4,16,D5,16,CS5,16,B4,16,R,16,B4,8,CS5,8,D5,8,D5,16,CS5,16,B4,16,CS5,16,DS5,16,FS5,16,GS5,16,DS5,16,FS5,16,CS5,16,DS5,16,B4,16,CS5,16,B4,16,DS5,8,FS5,8,GS5,16,DS5,16,FS5,16,CS5,16,DS5,16,B4,16,D5,16,DS5,16,D5,16,CS5,16,B4,16,CS5,16,D5,8,B4,16,CS5,16,DS5,16,FS5,16,CS5,16,DS5,16,CS5,16,B4,16,CS5,8,B4,8,CS5,8,B4,8,FS4,16,GS4,16,B4,8,FS4,16,GS4,16,B4,16,CS5,16,DS5,16,B4,16,E5,16,DS5,16,E5,16,FS5,16,B4,8,B4,8,FS4,16,GS4,16,B4,16,FS4,16,E5,16,DS5,16,CS5,16,B4,16,FS4,16,DS4,16,E4,16,FS4,16,B4,8,FS4,16,GS4,16,B4,8,FS4,16,GS4,16,B4,16,B4,16,CS5,16,DS5,16,B4,16,FS4,16,GS4,16,FS4,16,B4,8,B4,16,AS4,16,B4,16,FS4,16,GS4,16,E4,16,E5,16,DS5,16,E5,16,FS5,16,B4,8,AS4,8,B4,8,FS4,16,GS4,16,B4,8,FS4,16,GS4,16,B4,16,CS5,16,DS5,16,B4,16,E5,16,DS5,16,E5,16,FS5,16,B4,8,B4,8,FS4,16,GS4,16,B4,16,FS4,16,E5,16,DS5,16,CS5,16,B4,16,FS4,16,DS4,16,E4,16,FS4,16,B4,8,FS4,16,GS4,16,B4,8,FS4,16,GS4,16,B4,16,B4,16,CS5,16,DS5,16,B4,16,FS4,16,GS4,16,FS4,16,B4,8,B4,16,AS4,16,B4,16,FS4,16,GS4,16,B4,16,E5,16,DS5,16,E5,16,FS5,16,B4,8,CS5,8\n";

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
    b.kickTheRainbow(25, 0);
    while (isPaused()) {        // while paused...
        b.setBrightness(50);    // dim the LEDs
        b.kickTheRainbow(1, 2); // smoother rainbow
        Particle.process();     // keep our Cloud connection going
    }
    b.setBrightness(255); // re-brighten the jam!
}

/* This is the InternetButton::playSong(String song) routine
 * pulled out here so we can call kickTheRainbow() and read
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

void setup()
{
    b.begin();
    b.setBrightness(255); // 0 - 255
    b.setBPM(142); // Nyan Cat BPM is 142
    playSongAndProcess(nyan_cat_intro); // play the intro
}

void loop() {
    // Now loop the melody forever! Well, until it's paused :)
    playSongAndProcess(nyan_cat_melody);
}
