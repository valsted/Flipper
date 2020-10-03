// TODO: extend to handle all 4 (8-leds)
// TODO: make reactive LED-events and hold states etc. 

class LimitSwitch {
    const int POINTS = 100;
    int *score; // Pointer to score variable

    int inPin;
    int outPin;
    int pressed; // HIGH | LOW
    bool active; // Currently part of combo?

    public:
    LimitSwitch(int *score, int inPin, int outPin, int btnMode) {
        this.score = score;
        this.inPin = inPin;
        this.outPin = outPin;        
        this.pressed = btnMode;
    }

    void Setup() {
        pinMode(inPin, INPUT);
        pinMode(outPin, OUTPUT);
        active = false;
    }

    void Read() {
        int btn = digitalRead(inPin);
        if(btn == pressed) {
            active = !active;
            *score += POINTS; // Update score
            if(active) { LedON(); }
            else { LedOff(); }
        }
    }

    void LedOn() {
        analogWrite(outPin, 255);
    }

    void LedOff() {
        analogWrite(outPin, 0);
    }    
};