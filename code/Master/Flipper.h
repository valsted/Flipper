#ifndef _FLIPPER_H_
#define _FLIPPER_H_

class Flipper {
    int outPin;
    int inPin;
    int step;

    const int BURST_PW = 255;   // Full power for initial triggering.
    const int HOLD_PW = 50;     // Low power when hold, to avoid burnout
    const int NUM_STEPS = 240;  // No. of cycles to keep triggered

public:
    Flipper(int btnPin, int solPin) {
        inPin = btnPin;
        outPin = solPin;
        pinMode(inPin, INPUT);
        pinMode(outPin, OUTPUT);
        step = 0;
    }

    void Update() {
        if(shouldFire()) {
            int pw = (step < NUM_STEPS) ? BURST_PW : HOLD_PW;
            analogWrite(outPin, pw);
        } else { // Reset
            analogWrite(outPin, 0);
        }
    }

private:
    bool shouldFire() {
        if(digitalRead(inPin) == HIGH) {
            step++;
            return true;
        } else {
            step = 0;
            return false;
        }
    }
};

#endif // _FLIPPER_H_
