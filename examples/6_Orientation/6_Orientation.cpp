
#include "InternetButton.h"
#include "math.h"

/* Did you know that the Internet Button can detect if it's moving? It's true!
Specifically it can read when it's being accelerated. Recall that gravity
is a constant acceleration and this becomes very useful- you know the orientation!*/

InternetButton b = InternetButton();
int ledPos = 0;

void setup() {
    // Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();

    // reduce to less than full eye-blazing brightness
    b.setBrightness(95);
    
    Particle.variable("ledPos",ledPos);
}

void loop(){
    // previous LED off (or 'null' LED0 off the first time through)
    b.ledOn(ledPos, 0, 0, 0);
    
    // Want to figure out which LED is the lowest?
    // We've hidden the necessary trigonometry in this function.
    ledPos = b.lowestLed();
    
    // give some time for human retinal response
    delay(330);
    
    // Now turn the lowest LED on
    b.ledOn(ledPos, 0, 30, 30);

    // Wait a mo'
    delay(330);
}
