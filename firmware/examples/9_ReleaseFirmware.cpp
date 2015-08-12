/*
Well, this is the big one. It does a LOT of things. You should read the comments,
read in between the comments, and generally play around. I highly recommend
downloading Particle Dev from http://particle.io/dev because Dev makes it easy
to run functions. Check out the "Cloud Functions" view under the Particle menu.
*/

#include "InternetButton/InternetButton.h"
#include "math.h"

// Set up lots of global variables that we'll be using
InternetButton b = InternetButton();
uint8_t button1 = 0;
uint8_t button2 = 0;
uint8_t button3 = 0;
uint8_t button4 = 0;
uint8_t buttonAll = 0;
int gaugeCount = 0;

float ledPos = 1;
float ledDesired = 3;
uint8_t ledPosAchieved = 0;

// Prototypes of the functions that we'll use
int rainbowRemote(String command);
int ledOnRemote(String command);
int ledOffRemote(String command);
int ledAllOnRemote(String command);
int ledAllOffRemote(String command);
int gaugeRemote(String command);
int playSong(String command);

void setup() {
    // Starting InternetButton b
    b.begin();
    
    // Registering a whole bunch of useful functions
    
    // Turn an LED on using the format "LED_NUMBER,RED_INT,GREEN_INT,BLUE_INT"
    Spark.function("ledOn", ledOnRemote);
    
    // Turn an LED off, format is "LED_NUMBER"
    Spark.function("ledOff", ledOffRemote);
    
    // Turn all the LEDs on, format is "RED_INT,GREEN_INT,BLUE_INT"
    Spark.function("allLedsOn", ledAllOnRemote);
    
    // Turn all the LEDs off. Doesn't take any arguments. Or any of your lip.
    Spark.function("allLedsOff", ledAllOffRemote);
    
    // Woooo rainbows! Just tell it how many seconds.
    Spark.function("rainbow", rainbowRemote);
    
    // Gauge display- animates a value, just send it a number 1-66
    Spark.function("gauge",gaugeRemote);
    
    /* Takes in a string of the format "NOTE,DURATION,NOTE,DURATION..."
       For example "C4,8,D4,4" will play a middle C 1/8th note, then a middle D 1/4 note
       and "E5,8,G5,8,E6,8,C6,8,D6,8,G6,8" will play a familiar tune */
    Spark.function("play",playTune);
}

/* loop(), in contrast to setup(), runs all the time. Over and over again. 
Remember this particularly if there are things you DON'T want to run a lot. Like Spark.publish() */
void loop() {
    if(b.allButtonsOn()){
        if(!buttonAll){
            buttonAll = 1;
            Spark.publish("allbuttons",NULL, 60, PRIVATE);
            b.rainbow(10);
        }
    }
    else {buttonAll = 0;}
    
    // OK, I'll explain this structure once...
    if(b.buttonOn(1)){                                      // If button1 is on
        if(!button1){                                       // and hasn't already been on
            button1 = 1;                                    // then you should know that it's on now
            Spark.publish("button1",NULL, 60, PRIVATE);     // and publish that it's on
            ledControl(12);                                 // and do some pretty LED things for the user
        }
    }
    else {button1 = 0;}                                     // but if it's not on, we should reset this
                                                            // so we'll know when it comes on again
    if(b.buttonOn(2)){ 
        if(!button2){
            button2 = 1;
            Spark.publish("button2",NULL, 60, PRIVATE);
            ledControl(3);
        }
    }
    else {button2 = 0;}
    
    if(b.buttonOn(3)){
        if(!button3){
            button3 = 1;
            Spark.publish("button3",NULL, 60, PRIVATE);
            ledControl(6);
        }
    }
    else {button3 = 0;}
    
    if(b.buttonOn(4)){
        if(!button4){
            button4 = 1;
            Spark.publish("button4",NULL, 60, PRIVATE);
            ledControl(9);
        }
    }
    else {button4 = 0;}
    
    // This set of conditionals animates the moving LEDs
    if(abs(ledPos - ledDesired) > .001){
        ledPos = ledPos - (ledPos - ledDesired)/300;
        b.allLedsOff();
        
        // What's this hidden in here? Oh my, a function that takes
        // the position as a float! Smooth positions from 0-12!
        b.smoothLedOn(ledPos, 0, 60, 60);
    }
    else if(ledPosAchieved == 1){
        b.allLedsOff();
        ledPosAchieved = 2;
    }                
    else if(ledPosAchieved != 2){
        ledPosAchieved = 1;
    }
}

// playTune takes in a string of the format NOTE,DURATION,NOTE,DURATION...
// For example "C4,8,D4,4" will play a middle C 1/8th note, then a middle D 1/4 note
int playTune(String command){
    b.playSong(command);
    return 1;
}

// I've put some of the messiness of the LED animation setup in here
void ledControl(int ledn){
    b.ledOn(ledn,60,60,60);
    delay(200);
    ledDesired = ledn;
    if(ledPos < ledDesired){ledDesired++;}
    else{ledDesired--;}
    ledPosAchieved = 0;
}

// Lets you control rainbows, takes the desired rainbow time in seconds
int rainbowRemote(String command){
    char inputStr[10];
    command.toCharArray(inputStr,10);
    int i = atoi(inputStr);
    long startMillis = millis();
    while(millis() < startMillis + i*1000){
        b.rainbow(30);
    }
    return 1;
}

// Turn an LED on over the Internet!
// Format is "LED_NUMBER,RED_INT,GREEN_INT,BLUE_INT"
// with special cases for "LED_NUMBER,red" ... green,blue,white
int ledOnRemote(String command){
    int i = 0;
    
    char inputStr[20];
    command.toCharArray(inputStr,20);
    char *p = strtok(inputStr,",");
    i = atoi(p);
    p = strtok(NULL,",");
    if(String(p).equals("red")){
        b.ledOn(i,150,0,0);
    }
    else if(String(p).equals("green")){
        b.ledOn(i,0,150,0);
    }
    else if(String(p).equals("blue")){
        b.ledOn(i,0,0,150);
    }
    else if(String(p).equals("white")){
        b.ledOn(i,150,150,150);
    }
    else {
        //parse out CSV colors
        
        uint8_t red = atoi(p);
        p = strtok(NULL,",");
        uint8_t grn = atoi(p);
        p = strtok(NULL,",");
        uint8_t blu = atoi(p);
        
        b.ledOn(i,red,grn,blu);
    }
    return 1;
}

// Turn off a specific LED. Just send its number.
int ledOffRemote(String command){
    char inputStr[10];
    command.toCharArray(inputStr,10);
    char *p = strtok(inputStr,",");
    int i = atoi(p);
    b.ledOff(i);
    return 1;
}

// Turn all the LEDs on!
// Format is "RED_INT,GREEN_INT,BLUE_INT"
// with special cases for "red" ... green,blue,white
int ledAllOnRemote(String command){
    if(command.equals("red")){
        b.allLedsOn(150,0,0);
    }
    else if(command.equals("green")){
        b.allLedsOn(0,150,0);
    }
    else if(command.equals("blue")){
        b.allLedsOn(0,0,150);
    }
    else if(command.equals("white")){
        b.allLedsOn(150,150,150);
    }
    else {
        
        char inputStr[20];
        command.toCharArray(inputStr,20);
        char *p = strtok(inputStr,",");
        int red = atoi(p);
        p = strtok(NULL,",");
        int grn = atoi(p);
        p = strtok(NULL,",");
        int blu = atoi(p);
        p = strtok(NULL,",");
        b.allLedsOn(red,grn,blu);
    }
    return 1;
}

// Turn all the LEDs off!
int ledAllOffRemote(String command){
    b.allLedsOff();
    return 1;
}

// This one's fun. Just send it a number from 1-66 and it'll
// display it as though the Button is a round graph
int gaugeRemote(String command){
    char temp[5];
    command.toCharArray(temp,5);
    //int level = map(atoi(temp),1,100,1,33);
    int level = atoi(temp);
    b.allLedsOff();
    for(int i = 0; i < level+1; i++){
        if(i < 12){
            b.ledOn(i,0,40,0);
        }
        else if(i < 23){
            b.ledOn(i-11,0,90,10);
        }
        else if(i < 34){
            b.ledOn(i-22,20,20,0);
        }
        else if(i < 45){
            b.ledOn(i-33,80,80,10);
        }
        else if(i < 56){
            b.ledOn(i-44,30,0,0);
        }
        else if(i < 67){
            b.ledOn(i-55,90,0,5);
        }
        delay(50);
    }
    return 1;
}

void gaugeRemoteSub(const char *event, const char *data)
{
    gaugeRemote(String(data));
}

void gaugeCounter(const char *event, const char *data)
{
    gaugeCount++;
    gaugeRemote(String(gaugeCount));
}