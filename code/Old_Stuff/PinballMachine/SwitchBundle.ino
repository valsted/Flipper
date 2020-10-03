#include LimitSwitch.ino;

class SwitchBundle {
    const int POINTS = 5000;
    int *score;

    // References to the individual switches
    LimitSwitch &LL, &LR, &RL, &RR;

    // Light-control vars
    int interval;
    int flashCount, noOfTimes;
    bool on = false;
    bool flashing = false;
    unsigned long prevTime = 0;

    public: 
    SwitchBundle(int *score, int flashInterval, 
      LimitSwitch &LL, LimitSwitch &LR, LimitSwitch &RL, LimitSwitch &RR) {
        this->score = score;
        this->interval = flashInterval;
        this->LL = LL;
        this->LR = LR;
        this->RL = RL;
        this->RR = RR;
    }

    // Will start flashing for the given number of times
    void BeginFlash (int noOfTimes) {
        this.noOfTimes = noOfTimes * 2;
        flashing = true;
        LedsOn();
        *score += POINTS; // Add points!
    }

    void EndFlash() {
        flashing = false;
        flashCount = 0;
        noOfTimes = 0;
        LL.active = false;
        LR.active = false;
        RL.active = false;
        RR.active = false;
        LedsOff();
    }

    // TODO: måske lav noget med en side kan flashes ad gangen?
    void Update() {
        // Check if all were active
        if(LL.active && LR.active && RL.active && RR.active) {
            BeginFlash(6);
        }
        // Handle flashing logic
        if(flashing && flashCount < noOfTimes) {
            unsigned long curTime = millis();
            if(curTime - prevTime > interval) {
                prevTime = curTime;
                on = !on;
                if(on) {
                    LedsOn();
                } else {
                    LedsOff();
                }
                flashCount++;
            }
        } else {
            EndFlash();
        }
    }

    void LedsOn() {
        LL.LedOn();    
        LR.LedOn();
        RL.LedOn();
        RR.LedOn();
    }

    void LedsOff() {
        LL.LedOff();
        LR.LedOff();
        RL.LedOff();
        RR.LedOff();
    }
};