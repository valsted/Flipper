#include "IRSensor.h"

// ------------ Pin definition section ------------ 
#define SENS1 A1
#define SENS2 A2
#define SENS3 A3

#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
// ------------------------------------------------

class SensorArray {
    const int POINTS = 2500;
    unsigned long *scoreRef;
    int leds[4] = { 0, 0, 0, 0 }; // Pins to LED's [0-3] - 4 in total
    bool on[4] = { false, false, false, false };

    // References to the individual switches
    IRSensor *left, *mid, *right;

    public:
    SensorArray(unsigned long *score, IRSensor* left, IRSensor* mid, IRSensor* right,
        int ledPin1, int ledPin2, int ledPin3, int ledPin4) {
        this->scoreRef = score;
        this->left = left;
        this->mid = mid;
        this->right = right;
        leds[0] = ledPin1;
        leds[1] = ledPin2;
        leds[2] = ledPin3;
        leds[3] = ledPin4;
    }

    void Setup() {
        pinMode(leds[0], OUTPUT);
        pinMode(leds[1], OUTPUT);
        pinMode(leds[2], OUTPUT);
        pinMode(leds[3], OUTPUT);
        left->Setup();
        mid->Setup();
        right->Setup();
    }

    void Read() {
        if(left->Read()) { Toggle(0); }
        if(mid->Read()) { Toggle(1); }
        if(right->Read()) { Toggle(2); }
    }

    void Toggle(int pos) { // [0-2]
        // Switch on-mappings
        switch (pos) {
            case 0:
                on[0] = !on[0];
                on[1] = !on[1];
                break;   
            case 1:
                on[1] = !on[1];
                on[2] = !on[2];
                break;
            case 2:
                on[2] = !on[2];
                on[3] = !on[3];
                break;
            default:
                break;
        }
        // If everythings active, add bonus points
        if(on[0] && on[1] && on[2] && on[3]) {
            *scoreRef += POINTS;
        }
        // Write new mappings to LED's (0-4)
        for(int i = 0; i < 4; i++) {
            digitalWrite(leds[i], on[i]);
        }
    }
};
// ------------------------ Main skecth from here -------------------------------

unsigned long score = 0; 
IRSensor leftSens(&score, SENS1);
IRSensor midSens(&score, SENS2);
IRSensor rightSens(&score, SENS3);
SensorArray sensors(&score, &leftSens, &midSens, &rightSens, LED1, LED2, LED3, LED4);

void setup() {
    Serial.begin(9600);
    sensors.Setup();
}

void loop() {
    Serial.println(score);
    sensors.Read();
}