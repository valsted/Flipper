#ifndef _POPBUMPER_H_
#define _POPBUMPER_H_

class Popbumper {
    unsigned long *scoreRef;
    int inPin; // Pin to fire Solenoid
    int outPin; // Read conductive tape
    int step; //counter
    bool idle;

    const int NUM_STEPS = 40; // No. of cycles to keep triggered
    const int POINTS = 250;

public:
    Popbumper(unsigned long *score, int sensePin, int solPin) {
        scoreRef = score;
        inPin = sensePin;
        outPin = solPin;
    }

    void Setup() {
        pinMode(inPin, INPUT);
        pinMode(outPin, OUTPUT);
        step = 0;
        idle = true;
    }

    bool IsHit() {
        if(idle) {
            return digitalRead(inPin) == HIGH;
        } else {
            return false;
        }
    }

    void Activate() {
        analogWrite(outPin, 255); // FIRE for full effect!
        idle = false;
        *scoreRef += POINTS;
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
        analogWrite(outPin, 0);
        step = 0;
    }

};

#endif // _POPBUMPER_H_
