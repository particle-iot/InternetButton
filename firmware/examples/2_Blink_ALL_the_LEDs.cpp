#include "InternetButton/InternetButton.h"

/* This SparkButton library has some useful functions.
Here we blink ALL the LEDs instead of just one.*/

InternetButton b = InternetButton();

void setup() {
    // Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();
}

void loop(){
    b.allLedsOn(0,20,20);
    delay(1000);
    b.allLedsOff();
    delay(1000);

    // Notice that I made them much dimmer, so it's a bit less painful
}
