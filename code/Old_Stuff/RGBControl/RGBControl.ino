// Color channel outputs (must be PMW pins)
#define RED 3
#define GREEN 6
#define BLUE 5
#define FADESPEED 2

// ---- RGB arrays (R=0, G=1, B=2) ----
long prevTimes[] = {0, 0, 0};
bool onStates[] = {false, false, false};
int delays[] = {100, 200, 300};
// ------------------------------------

long curTime; 

void setup() {
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);

    clear(); // RESET
}

void loop() {
    curTime = millis(); 

    blink(RED, 0);
    blink(GREEN, 1);
    blink(BLUE, 2);
}

// Uses arrays prevTimes, onStates & delays;
void blink(int pin, int idx) {
    if(curTime - prevTimes[idx] > delays[idx]) {
        prevTimes[idx] = curTime;
        onStates[idx] = !onStates[idx];
        if(onStates[idx]) {
            analogWrite(pin, 100);
        } else {
            analogWrite(pin, 0);
        }
    }
}

void clear() { setColor(0,0,0); }
void setColor(int r, int g, int b) {
    analogWrite(RED, r);
    analogWrite(GREEN, g);
    analogWrite(BLUE, b);
}

void sweep() {
    int r, g, b;

  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    analogWrite(RED, r);
    delay(FADESPEED);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUE, b);
    delay(FADESPEED);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(GREEN, g);
    delay(FADESPEED);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(RED, r);
    delay(FADESPEED);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUE, b);
    delay(FADESPEED);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREEN, g);
    delay(FADESPEED);
  } 
}