#define SENSOR A1 

const int threshold = 300;  // TODO: mål og sæt according hvornår bolden skal detectes. 
const int POINTS = 100;
int score = 0;

void setup() {
    Serial.begin(9600);
    pinMode(SENSOR, INPUT);
}

void loop() {
    // Serial.println(score);
    Read();
}

bool Read() {
    int sense = analogRead(SENSOR);
    Serial.println(sense);
    if(sense < threshold) {
        score += POINTS;
        return true;
    }
    return false;
}