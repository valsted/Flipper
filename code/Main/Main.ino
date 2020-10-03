#include "RGBStrip.h"

#define RPIN 5
#define GPIN 3
#define BPIN 6
#define BTN 2

RGBStrip strip(RPIN, GPIN, BPIN);

void setup(){
    pinMode(BTN, INPUT);
}

void loop() {
    if(digitalRead(BTN) == HIGH) {
        int r = random(25, 255);
        int g = random(25, 255);
        int b = random(25, 255);
        strip.TriggerFade(r,g,b);
    }
    strip.Update();
}
