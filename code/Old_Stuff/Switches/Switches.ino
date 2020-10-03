#include "Switch.h"
#include "Flasher.h"

// ----- Pin definitions -----
#define LLpin 2        // Out
#define LRpin 4
#define RLpin 6
#define RRpin 8

#define LLpinSwitch 3  // In
#define LRpinSwitch 5
#define RLpinSwitch 7
#define RRpinSwitch 9

#define intv 100

// ----- Global variables -----

unsigned long score;

Flasher leftleft(LLpin, intv, false, &score);
Flasher leftright(LRpin, intv, false, &score);
Flasher rightleft(RLpin, intv, false, &score);
Flasher rightright(RRpin, intv, false, &score);

Switch llSwitch(&score, LLpinSwitch);
Switch lrSwitch(&score, LRpinSwitch);
Switch rlSwitch(&score, RLpinSwitch);
Switch rrSwitch(&score, RRpinSwitch);


// ----- Primary code -----
void setup(){
  score = 0;
  digitalWrite(LLpin, HIGH);
  digitalWrite(LRpin, HIGH);
  digitalWrite(RRpin, HIGH);
  digitalWrite(RLpin, HIGH);
}

void loop() {
  update();
  if(llSwitch.IsHit()){leftleft.Toggle();}
  if(lrSwitch.IsHit()){leftright.Toggle();}
  comboHit(&leftleft, &leftright);

  if(rrSwitch.IsHit()){rightright.Toggle();}
  if(rlSwitch.IsHit()){rightleft.Toggle();}
  comboHit(&rightleft, &rightright);
}

void comboHit(Flasher *fl, Flasher *fr){
  if(fl->GetIsOn() && fr->GetIsOn()){
    fl->Flash(14);
    fr->Flash(14);
  }
}
// Remember to add everything with a timestep here!
void update() {
  llSwitch.Update();
  lrSwitch.Update();
  rrSwitch.Update();
  rlSwitch.Update();
  
  leftleft.Update();
  leftright.Update();
  rightright.Update();
  rightleft.Update();
}
