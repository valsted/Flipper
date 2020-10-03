#ifndef _RGB_STRIP_H
#define _RGB_STRIP_H

// PREDEF COLORS  => See private function 'loadPredefColor'

class RGBStrip {
    int pins[3] = { 0, 0, 0 }; // A pin for each LED (R, G, B)
    int color[3] = { 100, 100, 100 }; // R, G, B values (0-255)
    int step; //counter
    bool fading;

    const int FADE_STEPS = 120;

public:
    RGBStrip(int rPin, int gPin, int bPin){
        pins[0] = rPin;
        pins[1] = gPin;
        pins[2] = bPin;
    }

    void Setup() {
        pinMode(pins[0], OUTPUT);
        pinMode(pins[1], OUTPUT);
        pinMode(pins[2], OUTPUT);
        step = 0;
        fading = false;
    }

    void Update() {
        if(fading) {
            if(step > 0) {
                for (int i = 0; i < 3; i++) {
                    int c = getColorComponent(i);
                    analogWrite(pins[i], c);
                }
                step--;
            } else {
                reset();
            }
        }
    }

    void TriggerFade(int itemId) {
        loadPredefColor(itemId);
        fading = true;
        step = FADE_STEPS;
    }

    void TriggerFade(int r, int g, int b) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        fading = true;
        step = FADE_STEPS;
    }

private:
    int getColorComponent(int i) {
        int val = map(step, 0, FADE_STEPS, 0, color[i]);
        return val;
    }

    void writeColor() {
        for (int i = 0; i < 3; i++) {
            digitalWrite(pins[i], color[i]);
        }
    }

    void reset() {
        fading = false;
        for (int i = 0; i < 3; i++) {
            color[i] = 0;
        }
        writeColor();
    }

// ============== PREDEF COLORS ===============
    void loadPredefColor(int itemId) {
        switch (itemId) {
            case 0: // Switch (Blue)
                color[0] = 0;
                color[1] = 0;
                color[2] = 255;
                break;
            case 1: // IRSensor (Green)
                color[0] = 0;
                color[1] = 255;
                color[2] = 0;
                break;
            case 2: // Popbumper (Red)
                color[0] = 255;
                color[1] = 0;
                color[2] = 0;
                break;
            case 3: // Falldown (Red)
                color[0] = 255;
                color[1] = 0;
                color[2] = 0;
                break;
            case 4: // Ramp (Cyan)
                color[0] = 0;
                color[1] = 200;
                color[2] = 255;
                break;
            case 5: // Combo (Orange)
                color[0] = 255;
                color[1] = 30;
                color[2] = 0;
                break;
            default:
                break;
        }
    }
// =================== END ====================
};

#endif // _RGB_STRIP_H
