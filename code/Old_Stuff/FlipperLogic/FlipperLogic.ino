// Inputs
#define BTN_LEFT 2
#define BTN_RIGHT 3

// Outputs 
#define SOL_LEFT 5      // NB! Should be PWM pin
#define SOL_RIGHT 6     // NB! Should be PWM pin

// Control vars
const int HOLD_TIME = 80; // #cycles before going to low-power state
const int HIGH_PW = 255;
const int LOW_PW = 40;

int leftTimer, rightTimer;

void setup() {
    pinMode(BTN_LEFT, INPUT);
    pinMode(BTN_RIGHT, INPUT);
    pinMode(SOL_LEFT, OUTPUT);
    pinMode(SOL_RIGHT, OUTPUT);
    leftTimer = 0;
    rightTimer = 0;
}

void loop() {
    // Retrieve button state and adjust according to how long it has been pressed
    int leftVal = calcLeftValue();
    int rightVal = calcRightValue();

    // Trigger solenoids (PWM)
    analogWrite(SOL_LEFT, leftVal);
    analogWrite(SOL_RIGHT, rightVal);
}

int calcLeftValue() {
    int lBtn = digitalRead(BTN_LEFT);
    if(lBtn == HIGH) {  // Assumning pull-down resistor
        leftTimer++;
        return  (leftTimer < HOLD_TIME) ? HIGH_PW : LOW_PW;
    } else {
        leftTimer = 0;
        return 0;
    }
}

int calcRightValue() {
    int rBtn = digitalRead(BTN_RIGHT);
    if(rBtn == HIGH) {  // Assumning pull-down resistor
        rightTimer++;
        return  (rightTimer < HOLD_TIME) ? HIGH_PW : LOW_PW;
    } else {
        rightTimer = 0;
        return 0;
    }
}
