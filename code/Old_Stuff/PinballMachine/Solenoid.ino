// TODO: consider doing version with interupt, for flippers

class Solenoid {
    int outPin; // Pin to fire Solenoid
    int inPin; // Read button / spoon
    int btnPressed; // HIGH | LOW
    int numSteps; // No. of cycles
    int step;

    // TODO: Skal de her være indstillelige udefra?
    const int BURST_PW = 255;
    const int HOLD_PW = 50;

    public:
    Solenoid(int inPin, int outPin, int numSteps, int btnMode) {
        this->inPin = inPin;
        this->outPin = outPin;
        this->numSteps = numSteps;
        this->btnPressed = btnMode;
    }
    
    void Setup() {
        pinMode(inPin, INPUT);
        pinMode(outPin, OUTPUT);
        step = 0;
    }

    void Update() {
        if(shouldFire()) {
            int pw = (step < numSteps) ? BURST_PW : HOLD_PW;
            analogWrite(outPin, pw);
        } else { // Reset
            analogWrite(outPin, 0);
        }
    }

    // Reads input and determines 
    bool shouldFire() {
        int btn = digitalRead(inPin);
        if(btn == btnPressed) {
            step++;
            return true;
        } else {
            step = 0;
            return false;
        }
    }
};