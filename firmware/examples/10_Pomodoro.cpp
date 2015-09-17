// This #include statement was automatically added by the Particle IDE.
#include "InternetButton/InternetButton.h"

InternetButton b = InternetButton();

unsigned long startTime = 0;
int ledNum = 0;
bool checkFlag = false;
bool subFlag = false;


void setup() {
    //initiating Internet button
    b.allLedsOff();
    b.begin();
    initPomo();
}

void loop() {
    checkButton();
    pomoMain();
}//main Application Loop

void pomoMain(){
    if(millis()-startTime > 54500UL && checkFlag){//750UL = .75seconds, ex: 54500UL = 5.45 minutes
        if(ledNum > 11){
            checkFlag = false;
            subFlag = true;
            partiTime();
        }else if(ledNum > 8){
            b.ledOn(ledNum++, 0,53,0); //ex: b.ledOn(ledNumber, red, green, blue)
        }else{
            b.ledOn(ledNum++, 105, 0,255);
        }
        
        startTime = millis();
        
    }
}//pomoMain() is end of "work" cycle

void partiTime(){
    
    while(b.buttonOn(2) == 0 && subFlag){
        b.rainbow(10);
        Particle.process();
    }
    b.allLedsOff();
    //b.playSong("E5,8,G5,8,E6,8,C6,8,D6,8,G6,8");
    initPomo();
    
}//partiTime function = end of full cycle

void initPomo(){
    ledNum = 0;
    b.ledOn(ledNum, 105,0,255);
    startTime = millis(); 
    checkFlag = false;
    subFlag = false;
}//initializing function for variables

void checkButton(){
    
    if(b.buttonOn(2)){
        checkFlag = !checkFlag;
        delay(50);
        while(b.buttonOn(2));
        delay(50);
    }//end of checkFlag toggle
    
}//checkButton() is for Flag Checking


