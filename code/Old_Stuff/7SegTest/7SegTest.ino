#include "DigitLedDisplay.h" // Library of arduino community

#define CLK 8
#define CS 9
#define DIN 10

#define _P B01100111
#define _I B00000110
#define _N B00110111
#define _B B01111111
#define _A B01110111
#define _L B00001110

// 7-segment control construct
DigitLedDisplay disp = DigitLedDisplay(DIN, CS, CLK); 

unsigned long score;

void setup(){
    disp.setBright(8); // [1..15]
    disp.setDigitLimit(8);
    score = 0;
    printPinball();
}

void test() {
    disp.write(1, B00000000);
    delay(300);
    disp.write(1, B00000001);
    delay(300);
    disp.write(1, B00000010);
    delay(300);
    disp.write(1, B00000100);
    delay(300);
    disp.write(1, B00001000);
    delay(300);
    disp.write(1, B00010000);
    delay(300);
    disp.write(1, B00100000);
    delay(300);
    disp.write(1, B01000000);
    delay(300);
    disp.write(1, B10000000);
}

void loop() {
    long points = random(100);
    addPoints(points);
    delay(points);
}

void addPoints(long value) {
    score += value;
    disp.printDigit(score);
}

// '''''''''''''''' Intro animation ''''''''''''''''''''''''''''
void printPinball() {
    sweepLeft();
    sweepRight();
    for(int i = 0; i < 5; i++) {
      pinball(); 
      delay(200);
      disp.clear();
      delay(200);
    }
    disp.clear();
}

void pinball() {
    disp.write(7, _P);
    disp.write(6, _I);
    disp.write(5, _N);
    disp.write(4, _B);
    disp.write(3, _A);
    disp.write(2, _L);
    disp.write(1, _L);
}


void sweepLeft() {
    for (unsigned int i = 1; i < 9; i++) {
        disp.write(i, B01001001);
        delay(80);
    }
    for (unsigned int i = 1; i < 9; i++) {
        disp.write(i, B00000000);
        delay(80);
    }
}

void sweepRight() {
    for (unsigned int i = 8; i > 0; i--) {
        disp.write(i, B01001001);
        delay(80);
    }
    for (unsigned int i = 8; i > 0; i--) {
        disp.write(i, B00000000);
        delay(80);
    }
}
// '''''''''''''''' Intro animation end ''''''''''''''''''''''''
