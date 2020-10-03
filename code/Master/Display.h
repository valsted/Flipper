#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "DigitLedDisplay.h" // Library of arduino community

#define CLK 8
#define CS 9
#define DIN 10

// Letter constants
#define _P B01100111
#define _I B00000110
#define _N B00110111
#define _B B01111111
#define _A B01110111
#define _L B00001110

class Display {
    unsigned long *scoreRef;
    int* livesRef;

    DigitLedDisplay disp = DigitLedDisplay(DIN, CS, CLK);

public:
    Display(unsigned long *score, int* lives) {
        scoreRef = score;
        livesRef = lives;
    }

    void Setup() {
        disp.setBright(8); // [1..15]
        disp.setDigitLimit(8);
    }

    // Waring blocks! (Contains delays)
    void PlayAnimation() {
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

    void Update() {
        disp.printDigit(*scoreRef);
    }

    void ShowLives() {
        for (int i = 0; i < 3; i++)
        {
            disp.clear();
            disp.write(7, _B);
            disp.write(6, _A);
            disp.write(5, _L);
            disp.write(4, _L);
            delay(800);
            disp.printDigit(*livesRef);
            delay(800);
        }
        disp.clear();
    }

    void GameOver() {
        disp.clear();
        for (unsigned int r = 1; r < 6; r++) {
            for (unsigned int i = 1; i < 9; i++) { disp.write(i, B00000001); }
            delay(80);
            for (unsigned int i = 1; i < 9; i++) { disp.write(i, B00001000); }
            delay(80);
            for (unsigned int i = 1; i < 9; i++) { disp.write(i, B01000000); }
            delay(80);
        }
        disp.clear();
    }

private:
    // '''''''''''''''' Intro animation ''''''''''''''''''''''''''''
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
};

#endif // _DISPLAY_H_
