#include "InternetButton/InternetButton.h"

/* How about we make this interactive? */

InternetButton b = InternetButton();

void setup() {
    // Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();
}

void loop(){

    // When you click the second button (at the 3 o'clock position) let's turn that LED on
    if(b.buttonOn(2)){
        b.ledOn(3, 255, 255, 255);
    }
    // And if the button's not on, then the LED should be off
    else {
        b.ledOff(3);
    }

    /* Much like the LEDs, there are also functions to check if all the buttons are on- b.allButtonsOn()
    or if all the buttons are off- b.allButtonsOff() */
}
