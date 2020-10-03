// ------------ Pin definition section ------------ 
#define SENSOR A1 
// ------------------------------------------------

class IRSensor {
    const int POINTS = 100;
    unsigned long *score;

    const int threshold = 300;  // TODO: mål og sæt according hvornår bolden skal detectes. 
    int inPin;

    public: 
    IRSensor(unsigned long *score, int inPin) {
        this->score = score;
        this->inPin = inPin;
    }

    void Setup() {
        pinMode(inPin, INPUT);
    }

    bool Read() {
        int sense = analogRead(inPin);
        if(sense < threshold) {
            *score += POINTS;
            return true;
        }
        return false;
    }
};
// ------------------------ Main skecth from here -------------------------------

unsigned long score = 0; 
IRSensor sensor(&score, SENSOR);

void setup() {
    Serial.begin(9600);
    sensor.Setup();
}

void loop() {
    Serial.println(score);
    sensor.Read();
}