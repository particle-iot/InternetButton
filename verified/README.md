## Library verification for Internet Button
The purpose of this test is to verify the current Internet Button library from our community. To make sure all the others can feel comfortable to use this library in their project. This verification code is based the Particle platform.

### Preparation for running this firmware.
* Photon
* An Internet Button (https://store.particle.io/products/internet-button)
* MicroUSB Cable
* Particle Web IDE

### Library version list
* internetbutton library `0.1.10`

### Verify process

To make sure the Internet Button library works as expected, will go through each example.

1. Setup a new Photon
2. Attached an Internet Button to it
3. Flashed `1_BLINK_AN_LED`. Works as expected, and a single LED blinks blue.
4. Flashed `2_BLINK_ALL_THE_LEDS`. All the LEDS blink blue.
5. Flashed `3_BUTTONS_AND_LEDS`. Pressing on the second button turns on the LED.
6. Flashed `4_GOOD_COMBINATION`. Pressing on each button turns on the corresponding LED (the one above).
7. Flashed `5_MOTION`. Rotating the Internet Button changes the colors.
8. Flashed `6_ORIENTATION`. Rotating the Internet Button lights up the LED on the bottom.
9. Flashed `7_INTERNET`. Changed the device name to "InternetButton". Downloaded the example code from the description, and opened the HTML file in Chrome. Clicking on different parts of the knob lights up the right LEDS.
10. Flashed `8_MAKINGMUSIC`. Pressing on buttons produces different musical notes.
11. Flashed `9_RELEASEFIRMWARE`. Clicking on buttons turns on the LEDS. API calls to functions work.
