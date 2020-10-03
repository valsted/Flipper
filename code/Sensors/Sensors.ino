#include "Sensor.h"
#include "C:\Users\Shika\Documents\ITU\Master\2semester\Flipper\code\Switches\Flasher.h"

// ----- Pin definitions -----

// In
#define sLeft A1
#define sMid A2
#define sRight A3
// Out
#define LSpin 2
#define LBpin 3
#define RBpin 4
#define RSpin 5

#define intv 100


// ----- Global variables -----
unsigned long score;

Sensor sensorLeft(&score, sLeft);
Sensor sensorMid(&score, sMid);
Sensor sensorRight(&score, sRight);

Flasher leftSmall(LSpin, intv, true, &score);
Flasher leftBig(LBpin, intv, true, &score);
Flasher rightBig(RBpin, intv, true, &score);
Flasher rightSmall(RSpin, intv, true, &score);

// ----- Primary code -----
void setup(){
  score = 0;
  digitalWrite(LSpin, LOW);
  digitalWrite(LBpin, LOW);
  digitalWrite(RBpin, LOW);
  digitalWrite(RSpin, LOW);
}

void loop(){
  update();
  if(sensorLeft.IsHit()){leftSmall.Toggle();}
  if(sensorMid.IsHit()){
    leftBig.Toggle();
    rightBig.Toggle();
    }
  if(sensorRight.IsHit()){rightSmall.Toggle();}
  comboHit(&leftSmall, &leftBig, &rightBig, &rightSmall);
  
}

void comboHit(Flasher *sl, Flasher *bl, Flasher *br, Flasher *sr){
  if(sl->GetIsOn() && bl->GetIsOn() && br->GetIsOn() && sr->GetIsOn()){
    sl->Flash(5);
    bl->Flash(5);
    br->Flash(5);
    sr->Flash(5);
  }
}

void update() {
  sensorLeft.Update();
  sensorMid.Update();
  sensorRight.Update();

  leftSmall.Update();
  leftBig.Update();
  rightSmall.Update();
  rightBig.Update();
}
