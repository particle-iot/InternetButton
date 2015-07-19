#include "InternetButton/InternetButton.h"
#include "math.h"

/*Did you know that the SparkButton can detect if it's moving? It's true!
Specifically it can read when it's being accelerated. Recall that gravity
is a constant acceleration and this becomes very useful- you know the orientation!*/


InternetButton b = InternetButton();

void setup() {
    //Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();
}

void loop(){

    //How much are you moving in the x direction? (look at the white text on the board)
    int xValue = b.readX();

    //How about in the y direction?
    int yValue = b.readY();

    //And the z!
    int zValue = b.readZ();

    //This will make the color of the Button change with what direction you shake it
    //The abs() part takes the absolute value, because negatives don't work well
    b.allLedsOn(abs(xValue), abs(yValue), abs(zValue));

    //Wait a mo'
    delay(50);
}
