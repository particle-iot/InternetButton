#include "InternetButton/InternetButton.h"

// Create a Button named b. It will be your friend, and you two will spend lots of time together.
// You may be wondering about those two slashes and this gray text- they're called comments, and
// don't affect the code. Think of this as the voice of the narrator.
InternetButton b = InternetButton();

// The code in setup() runs once when the device is powered on or reset. Used for setting up states, modes, etc
void setup() {
    // Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();
}

/* loop(), in contrast to setup(), runs all the time. Over and over again.
Remember this particularly if there are things you DON'T want to run a lot. Like Spark.publish() */
void loop() {
    // Let's turn an LED on. How about #6, which is at the 6 o'clock position? Let's make it blue and bright.
    b.ledOn(6, 0, 0, 255);
    // The format here is (LED, red, green, blue), so we're making a color with no red or green, but ALL the blue
    // You should know that the range of brightness here is 0-255, so 0 is off and 255 is the most possible.
    // After you use this code, try making the LED white- all the red, green, and blue.

    // Since the LED is now on, let's have it stay that way for one second
    // Delay pauses the code for the amount of time given, in milliseconds- so 1000 millis is one whole second
    delay(1000);

    // And to blink the LED, we'll need to turn it back off and then pause for another second
    b.ledOff(6);
    delay(1000);

    // Now you're blinking! Play with which LED is blinking (1-11), the delays between, and the color.
}
