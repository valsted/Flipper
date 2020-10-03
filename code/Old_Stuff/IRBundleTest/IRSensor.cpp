#include "IRSensor.h"   // include this library's description file
#include "Arduino.h"

//const int POINTS = 100;
//const int threshold = 50; 
unsigned long *scoreRef;
int inPin;

IRSensor::IRSensor(unsigned long *score_arg, int inPin_arg) {
    scoreRef = score_arg;
    inPin = inPin_arg;
}

void IRSensor::Setup(void) {
    pinMode(inPin, INPUT);
}

bool IRSensor::Read(void) {
    int sense = analogRead(inPin);
    if(sense < threshold) {
        *scoreRef += POINTS;
        return true;
    }
    return false;
}