#include "InternetButton/InternetButton.h"
#include "math.h"

/* Did you know that the Internet Button can detect if it's moving? It's true!
Specifically it can read when it's being accelerated. Recall that gravity
is a constant acceleration and this becomes very useful- you know the orientation!*/

InternetButton b = InternetButton();

void setup() {
    // Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();
}

void loop(){
    // Want to figure out which LED is the lowest?
    // We've hidden the necessary trigonometry in this function.
    int ledPos = b.lowestLed();

    // Turn the LEDs off so they don't all end up on
    b.allLedsOff();

    // Now turn that LED on
    b.ledOn(ledPos, 0, 30, 30);

    // Wait a mo'
    delay(100);
}
