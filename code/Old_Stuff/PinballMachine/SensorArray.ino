#include IRSensor.ino;

enum SensorPosition {
    LEFT,
    MID,
    RIGHT
};

class SensorArray {
    const int POINTS = 2500;
    int *score;
    int leds[]; // Pins to LED's [0-3] - 4 in total
    bool on[] = { false, false, false, false };

    // References to the individual switches
    IRSensor &left, &mid, &right;

/// NB!!!  Se IRBundleTest i stedet. Der er mere opdateret logik.

    public:
    SensorArray(int *score, IRSensor &left, IRSensor &mid, IRSensor &right,
        int ledpin1, int ledpin2, int ledpin3, int ledpin4) {
        this.score = score;
        this.left = left;
        this.mid = mid;
        this.right = right;
        this.ledpin1 = led1;
        this.ledpin2 = led2;
        this.ledpin3 = led3;
        this.ledpin4 = led4;
    }

    void Setup() {
        pinMode(led1, OUTPUT);
        pinMode(led2, OUTPUT);
        pinMode(led3, OUTPUT);
        pinMode(led4, OUTPUT);
    }

    void Read() {

    }

    void Toggle(SensorPosition pos) {
        *score += POINTS;
        // Switch 
        switch (pos) {
            case LEFT:
                on[0] = !on[0];
                on[1] = !on[1];
                break;
        
            default:
                break;
        }
        
    }

};