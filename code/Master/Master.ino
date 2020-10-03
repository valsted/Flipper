#include "Display.h"
#include "Flasher.h"
#include "Sensor.h"
#include "Switch.h"
#include "Flipper.h"
#include "Popbumper.h"
#include "RGBStrip.h"

// #define DEBUG // Debugging toggler
// ---------- Pin definitions ----------
#define sPin A5     // Falldown detector

// In
#define LLpinSwitch 51  // Switches
#define LRpinSwitch 50
#define RLpinSwitch 52
#define RRpinSwitch 53
// Out
#define LLpin 46
#define LRpin 47
#define RLpin 48
#define RRpin 49

// In
#define sLeft A2        // Top IR Sensors
#define sMid A0
#define sRight A1 
// Out
#define LSpin 31        // IR Sensor LED's
#define LBpin 33 
#define RBpin 32
#define RSpin 30 

#define POP1 4      // Popbumpers
#define POP2 6
#define POP3 5
#define TAPE1 17
#define TAPE2 18
#define TAPE3 19

#define FLIP_L 2   // Flippers
#define FLIP_R 3
#define BTN_L 14
#define BTN_R 15

#define RPIN 11      // RGB strip 
#define GPIN 12
#define BPIN 13

// ---------- Constants -----------
#define intv 100
#define limit 100

// ---------- Global variables ----------
unsigned long score;
int lives;

// ---------- Component declarations -----------
Sensor fallSens(&score, sPin, 25);            // Falldown sensor

RGBStrip strip(RPIN, GPIN, BPIN);               // RGBStrip

Display display(&score, &lives);                // Display

Sensor sensorLeft(&score, sLeft, 70);           // Top dividers
Sensor sensorMid(&score, sMid, 70);
Sensor sensorRight(&score, sRight, 70);
Flasher leftSmall(LSpin, intv, true, &score);
Flasher leftBig(LBpin, intv, true, &score);
Flasher rightBig(RBpin, intv, true, &score);
Flasher rightSmall(RSpin, intv, true, &score);

Switch llSwitch(&score, LLpinSwitch);           // Switches
Switch lrSwitch(&score, LRpinSwitch);
Switch rlSwitch(&score, RLpinSwitch);
Switch rrSwitch(&score, RRpinSwitch);
Flasher leftleft(LLpin, intv, false, &score);   
Flasher leftright(LRpin, intv, false, &score);
Flasher rightleft(RLpin, intv, false, &score);
Flasher rightright(RRpin, intv, false, &score);

Flipper flipperLeft(BTN_L, FLIP_L);             // Flippers
Flipper flipperRight(BTN_R, FLIP_R);

Popbumper bumper1(&score, TAPE1, POP1);         // Popbumpers
Popbumper bumper2(&score, TAPE2, POP2);
Popbumper bumper3(&score, TAPE3, POP3);

// ---------- Primary code ----------
void setup() {
    score = 0;
    lives = 3;

    display.Setup();
    strip.Setup();

    bumper1.Setup();
    bumper2.Setup();
    bumper3.Setup();

    sensorLeft.Setup();
    sensorMid.Setup();
    sensorRight.Setup();    
    leftSmall.Setup();
    leftBig.Setup();
    rightSmall.Setup();
    rightBig.Setup();

    llSwitch.Setup();
    lrSwitch.Setup();
    rlSwitch.Setup();
    rrSwitch.Setup();
    leftleft.Setup();
    leftright.Setup();
    rightleft.Setup();
    rightright.Setup();

    // Ensure turned off.
    digitalWrite(LLpin, HIGH);
    digitalWrite(LRpin, HIGH);
    digitalWrite(RRpin, HIGH);
    digitalWrite(RLpin, HIGH);

    display.PlayAnimation();
}

void loop() {
    update();

    // Life-check
    if (fallSens.IsHit()) {
        if (lives > 0) {
            lives--;
            display.ShowLives(); // Warning! Stalls game temporarily
        } else {
            EndGame();
        }
    }

    // Popbumpers
    if (bumper1.IsHit()) {
        bumper1.Activate();
        strip.TriggerFade(2);
    }
    if (bumper2.IsHit()) {
        bumper2.Activate();
        strip.TriggerFade(2);
    }
    if (bumper3.IsHit()) {
        bumper3.Activate();
        strip.TriggerFade(2);
    }

    // Top IR Sensors (TriggerID = 1)
    if (sensorLeft.IsHit()) {
        leftSmall.Toggle();
        strip.TriggerFade(1);
    } 
    if (sensorMid.IsHit()) {
        leftBig.Toggle();
        rightBig.Toggle();
        strip.TriggerFade(1);
    } 
    if (sensorRight.IsHit()) { 
        rightSmall.Toggle();
        strip.TriggerFade(1);
    }
    comboHitSensor(&leftSmall, &leftBig, &rightBig, &rightSmall);

    // Switches (TriggerId = 0)
    if(llSwitch.IsHit()) { 
        leftleft.Toggle(); 
        strip.TriggerFade(0);
    }
    if(lrSwitch.IsHit()) { 
        leftright.Toggle(); 
        strip.TriggerFade(0);
    }

    comboHitSwitch(&leftleft, &leftright);
    if(rrSwitch.IsHit()) { 
        rightright.Toggle();
        strip.TriggerFade(0); 
    }
    if(rlSwitch.IsHit()) { 
        rightleft.Toggle(); 
        strip.TriggerFade(0);
    }
    comboHitSwitch(&rightleft, &rightright);
}

void update() {
    fallSens.Update();
    display.Update();
    strip.Update();

    flipperLeft.Update();   // Solenoids
    flipperRight.Update();
    bumper1.Update();
    bumper2.Update();
    bumper3.Update();

    sensorLeft.Update();    // Sensors
    sensorMid.Update();
    sensorRight.Update();
    leftSmall.Update();
    leftBig.Update();
    rightSmall.Update();
    rightBig.Update();

    llSwitch.Update();      // Switches
    lrSwitch.Update();
    rrSwitch.Update();
    rlSwitch.Update();
    leftleft.Update();
    leftright.Update();
    rightright.Update();
    rightleft.Update();
}

void comboHitSensor(Flasher *sl, Flasher *bl, Flasher *br, Flasher *sr) {
    if (sl->GetIsOn() && bl->GetIsOn() && br->GetIsOn() && sr->GetIsOn()) {
        sl->Flash(10);
        bl->Flash(10);
        br->Flash(10);
        sr->Flash(10);
        strip.TriggerFade(5);
    }
}

void comboHitSwitch(Flasher *fl, Flasher *fr) {
    if (fl->GetIsOn() && fr->GetIsOn()) {
        fl->Flash(10);
        fr->Flash(10);
        strip.TriggerFade(5);
    }
}

void EndGame() {
    display.GameOver();
    setup();
}
