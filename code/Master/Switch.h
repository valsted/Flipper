#ifndef _SWITCH_H_
#define _SWITCH_H_

class Switch {
  unsigned long *scoreRef;
  int pin;
  int step; //counter
  bool idle;

  const int NUM_STEPS = 120; // No. of cycles to wait for next trigger
  const int POINTS = 250;

  public:
      Switch(unsigned long *score, int inPin) {
          scoreRef = score;
          pin = inPin;
          pinMode(pin, INPUT);
    }

    void Setup() {
        pinMode(pin, INPUT);
        step = 0;
          idle = true;
    }

      bool GetIdle(){ return idle; }

      bool IsHit() {
          if(idle) {
              if(digitalRead(pin) == LOW){
                *scoreRef += POINTS;
                idle = false;
                return true;
              }
              else{return false;}
          } else {
              return false;
          }
      }

      void Update() {
          if(!idle) {
              step++;
              if(step > NUM_STEPS) {
                  Reset();
              }
          }
      }

private:
    void Reset() {
        idle = true;
        step = 0;
    }
};

#endif // _SWITCH_H_
