#ifndef _SENSOR_H_
#define _SENSOR_H_

class Sensor {
    unsigned long *scoreRef;
    int pin;
    int step;   //counter
    bool idle;
    int limit;  //threshold for sensor input when activated or not

    const int NUM_STEPS = 160; // No. of cycles to wait for next trigger
    const int POINTS = 250;

public:
    Sensor(unsigned long *score, int inPin, int threshold) {
        scoreRef = score;
        pin = inPin;
        limit = threshold;
    }

    void Setup() {
        pinMode(pin, INPUT);
        step = 0;
        idle = true;
    }

    bool GetIdle() { return idle; }

    bool IsHit() {
        if(idle) {
            Serial.println(analogRead(pin));
            if(analogRead(pin) < limit){
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
#endif
