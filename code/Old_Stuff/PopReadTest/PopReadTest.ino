#define TAPE 2

unsigned long bold;


void setup() {
    pinMode(TAPE, INPUT);
    Serial.begin(9600);
}

void loop() {
    int read = digitalRead(TAPE);
    if(read == HIGH) {
        bold += 7;
    }
    Serial.println(bold);
}