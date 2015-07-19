#include "InternetButton/InternetButton.h"

/* Here's a nice combination of features that I like to use.
Note the use of the allButtons function. */

InternetButton b = InternetButton();

bool rainbow_mode = false;

void setup() {
    // Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code above.
    b.begin();
}

void loop(){

    // If this calls for a full spectrum situation, let's go rainbow!
    if(b.allButtonsOn()) {
        // Publish the event "allbuttons" for other services like IFTTT to use
        Spark.publish("allbuttons",NULL, 60, PRIVATE);
        b.rainbow(5);
        rainbow_mode = true;

        // If all buttons are on, don't try to process
        // the individual button responses below.  Just return.
        return;
    }

    // If we are not in rainbow mode anymore, turn the LEDs off
    if (rainbow_mode == true) {
        b.allLedsOff();
        rainbow_mode = false;
    }

    // Process individual buttons and LED response
    if (b.buttonOn(1)) {
        b.ledOn(12, 255, 0, 0); // Red
        // Publish the event "button1" for other services like IFTTT to use
        Spark.publish("button1",NULL, 60, PRIVATE);
        delay(500);
    }
    else {
        b.ledOn(12, 0, 0, 0);
    }

    if (b.buttonOn(2)) {
        b.ledOn(3, 0, 255, 0); // Green
        // Publish the event "button2" for other services like IFTTT to use
        Spark.publish("button2",NULL, 60, PRIVATE);
        delay(500);
    }
    else {
        b.ledOn(3, 0, 0, 0);
    }

    if (b.buttonOn(3)) {
        b.ledOn(6, 0, 0, 255); // Blue
        // Publish the event "button3" for other services like IFTTT to use
        Spark.publish("button3",NULL, 60, PRIVATE);
        delay(500);
    }
    else {
        b.ledOn(6, 0, 0, 0);
    }

    if (b.buttonOn(4)) {
        b.ledOn(9, 255, 0, 255); // Magenta
        // Publish the event "button4" for other services like IFTTT to use
        Spark.publish("button4",NULL, 60, PRIVATE);
        delay(500);
    }
    else {
        b.ledOn(9, 0, 0, 0);
    }

    if(b.allButtonsOff()) {
        // Do something here when all buttons are off
    }
}
