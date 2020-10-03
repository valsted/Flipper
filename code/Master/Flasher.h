#ifndef _FLASHER_H_
#define _FLASHER_H_

class Flasher {
    int pin; // Pin to drive LED from
    bool onVal; // Value to set to trigger LED.
    int step = 0;
    int numSteps = 0; // No. of cycles to keep triggered
    bool isOn = false;
    bool flashing = false;
    unsigned long previousTime = 0;
    int interval;

    unsigned long *scoreRef;
    const int POINTS = 500;

public:
    Flasher(int ledPin, int flashInterval, bool onMode, unsigned long *score) {
        scoreRef = score;
        pin = ledPin;
        interval = flashInterval;
        onVal = onMode ? true : false; // Expect HIGH, else invert
    }

    void Setup() {
        pinMode(pin, OUTPUT);
        step = 0;
        numSteps = 0;
        isOn = false;
        flashing = false;
        previousTime = 0;
    }

    void Flash(int noOfTimes) {
        numSteps = noOfTimes << 1; // *2*/
        flashing = true;
    }

    void Toggle(){
      if(isOn){
        digitalWrite(pin, !onVal);
        isOn = false;
      }
      else{
        digitalWrite(pin, onVal);
        isOn = true;
      }
    }

    void Update() {
        if(flashing) {
            if(step < numSteps) {
              unsigned long currentTime = millis();
              if(currentTime - previousTime > interval){
                Toggle();
                previousTime = currentTime;
                step++;
              }
            } else {
                *scoreRef += POINTS;
                Stop();
            }
        }
    }

    bool GetIsOn(){ return isOn;}

private:
    void Stop() {
        if(isOn) Toggle();
        flashing = false;
        step = 0;
        numSteps = 0;
    }
};

#endif // _FLASHER_H_
