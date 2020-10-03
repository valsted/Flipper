#include "Popbumper.h"
#include "Flipper.h"

// ----- Pin definitions -----
#define POP1 3      // Popbumpers
#define POP2 5
#define POP3 6
#define TAPE1 2     
#define TAPE2 4
#define TAPE3 7

#define FLIP_L 10   // Flippers
#define FLIP_R 11
#define BTN_L 8
#define BTN_R 9

// ----- Global variables -----
unsigned long score;

Flipper flipperLeft(BTN_L, FLIP_L);
Flipper flipperRight(BTN_R, FLIP_R);

Popbumper bumper1(&score, TAPE1, POP1);
Popbumper bumper2(&score, TAPE2, POP2);
Popbumper bumper3(&score, TAPE3, POP3);

// ----- Primary code -----
void setup() {
    score = 0;
    // Maybe init SerialPrint?
}

void loop() {
    update();
    if(bumper1.IsHit()) { bumper1.Activate(); }
    if(bumper2.IsHit()) { bumper2.Activate(); }
    if(bumper3.IsHit()) { bumper3.Activate(); }
}

// Remember to add everything with a timestep here!
void update() {
    flipperLeft.Update();
    flipperRight.Update();
    bumper1.Update();
    bumper2.Update();
    bumper3.Update();
}