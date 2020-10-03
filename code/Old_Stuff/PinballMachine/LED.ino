class LED {
    int pin;
    int interval;
    bool on;
    unsigned long prevTime;

    public:
    LED(int pin, int interval) {
        this.pin = pin;
        this.interval = interval;
    }

    void Setup() {
        pinMode(pin, OUTPUT);
        on = false;
        prevTime = 0;
    }

    void Flash(int intensity) {
        unsigned long curTime = millis();
        if(curTime - prevTime > interval) {
            prevTime = curTime;
            on = !on;
            if(on) {
                analogWrite(pin, intensity);
            } else {
                analogWrite(pin, 0);
            }
        }
    }
};