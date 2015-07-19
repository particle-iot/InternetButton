#include "InternetButton/InternetButton.h"
#include "math.h"

/* Let me show you how easy it is to put the Button on the Internet.
Useful info, like how to access the data from your browser, can be
found here: http://docs.particle.io/photon/firmware/#spark-function

The code to control the number of illuminated LEDs is here:
https://github.com/spark/InternetButton/blob/master/controlKnob.html
Try naming one of your devices "InternetButton" and running controlKnob in your browser or on your phone!
Note that the Core or Photon *must* be named "InternetButton" because the javascript looks for it.
*/

InternetButton b = InternetButton();
float brightness = 0.1;
int red, green, blue;
int howMany = 6;
int whichColor = 100;
bool changed = false;

void setup() {
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();

    //This is all you need to make the function controller() available to the internet
    //The API name and the local name don't need to be the same; just my style
    Spark.function("controller", controller);

    //This function figures out what combination color, brightness and LEDs to display
    makeColors();

}

void loop(){
    //Clicking "up" makes the LEDs brighter
    if(b.buttonOn(1)){
        if(brightness < 1){
            brightness += 0.005;
            changed = true;
        }
    }
    //Clicking "down" makes the LEDs dimmer
    else if (b.buttonOn(3)){
        if(brightness > 0){
            brightness -= 0.005;
            if(brightness < 0){
                brightness = 0;
            }
            changed = true;
        }
    }
    //Clicking "right" and "left" change the color
    else if (b.buttonOn(2)){
        if(whichColor < 255){
            whichColor += 1;
            changed = true;
        }
    }
    else if (b.buttonOn(4)){
        if(whichColor > 0){
            whichColor -= 1;
            changed = true;
        }
    }

    //If anything's been altered by clicking or the Spark.function, update the LEDs
    if(changed){
        delay(10);
        makeColors();
        changed = false;
    }
}

//Uses the brightness and the color values to compute what to show
void makeColors(){
  uint8_t x = whichColor;
  if(x < 85) {
    red = brightness * x * 3;
    green = brightness * (255 - x * 3);
    blue = 0;
  } else if(x < 170) {
     x -= 85;
     red = brightness * (255 - x * 3);
     green = 0;
     blue = brightness * x * 3;
  } else {
     x -= 170;
     red = 0;
     green = brightness * x * 3;
     blue = brightness * (255 - x * 3);
  }

  b.allLedsOff();
  for(int i = 1; i <= howMany; i++){
    b.ledOn(i, red, green, blue);
  }
}

/*
controller() is the local function that is executed when the API function "controller" is called.
It changes how many LEDs on the Button are illuminated.
*/
int controller(String command){
    //parse the string into an integer
    int state = atoi(command.c_str());

    //Check that the value it's been given is in the right range
    if (state > 11) {state = 11;}
    else if (state < 0) {state = 0;}

    howMany = state;

    changed = true;

    return 1;
}
