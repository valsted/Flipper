// Inputs
#define BTN 12
#define SKE 11

// Outputs 
#define SOL1 3      // NB! Should be PWM pin
#define SOL2 5
#define SOL3 6

// Control vars
const int HOLD_TIME = 100; // #cycles before going to low-power state
const int HIGH_PW = 255;
const int LOW_PW = 50;

int timer;

void setup() {
    Serial.begin(9600);
    pinMode(BTN, INPUT);
    pinMode(SKE, INPUT);
    pinMode(SOL1, OUTPUT);
    pinMode(SOL2, OUTPUT);
    pinMode(SOL3, OUTPUT);
    timer = 0;
}

void loop() {
    // Retrieve button state and adjust according to how long it has been pressed
    int val = calcValue();
    Serial.println(val);

    // Trigger solenoid (PWM)
    analogWrite(SOL1, val);
    analogWrite(SOL2, val);
    analogWrite(SOL3, val);
}

int calcValue() {
    int btn = digitalRead(BTN);
    if(btn == HIGH) {  // Assumning pull-up resistor
        timer++;
        return  (timer < HOLD_TIME) ? HIGH_PW : LOW_PW;
    } else {
        timer = 0;
        return 0;
    }
}