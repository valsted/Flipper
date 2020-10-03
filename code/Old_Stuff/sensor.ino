int const sensorLeft = A1; //10;
int const sensorMid = A2; //11;
int const sensorRight = A3; //12;

int const leftSmall = 5;
int const leftBig = 6;
int const rightBig = 7;
int const rightSmall = 8;

int boolLeft;
int boolMid;
int boolRight;
int val;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorLeft, INPUT);
  pinMode(sensorMid, INPUT);
  pinMode(sensorRight, INPUT);

  pinMode(leftSmall, OUTPUT);
  pinMode(leftBig, OUTPUT);
  pinMode(rightBig, OUTPUT);
  pinMode(rightSmall, OUTPUT);

  int boolLeft = 0;
  int boolMid = 0;
  int boolRight = 0;


  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // LEFT
  if(analogRead(sensorLeft) < 40){
   if((boolMid + boolRight) == 2) allHit();

    else if(boolLeft == 1){
      digitalWrite(leftSmall, LOW);
      boolLeft = 0;
    }
    else  {
      digitalWrite(leftSmall, HIGH);
      boolLeft = 1;
    }
      delay(1000);
  }

  // MID
  if(analogRead(sensorMid) < 40) {
    if((boolLeft + boolRight) == 2) allHit();

    else if(boolMid == 1){
      digitalWrite(leftBig, LOW);
      digitalWrite(rightBig, LOW);
      boolMid = 0;
    }
    else  {
      digitalWrite(leftBig, HIGH);
      digitalWrite(rightBig, HIGH);
      boolMid = 1;
    }
    delay(1000);
  }

  // RIGHT
  val = analogRead(sensorRight);  // read the input pin
  Serial.println(val);
  if(analogRead(sensorRight) < 40){
    if((boolMid + boolLeft) == 2) allHit();

    else if(boolRight == 1){
      digitalWrite(rightSmall, LOW);
      boolRight = 0;
    }
    else{
      digitalWrite(rightSmall, HIGH);
      boolRight = 1;
    }
    delay(1000);
  }

}

void allHit(){
  for(int i = 0; i < 10; i ++){
      digitalWrite(leftSmall, LOW);
      digitalWrite(leftBig, LOW);
      digitalWrite(rightSmall, LOW);
      digitalWrite(rightBig, LOW);
      delay(200);
      digitalWrite(leftSmall, HIGH);
      digitalWrite(leftBig, HIGH);
      digitalWrite(rightSmall, HIGH);
      digitalWrite(rightBig, HIGH);
      delay(200);
  }
      delay(300);
      digitalWrite(leftSmall, LOW);
      digitalWrite(leftBig, LOW);
      digitalWrite(rightSmall, LOW);
      digitalWrite(rightBig, LOW);

      boolRight = 0;
      boolMid = 0;
      boolLeft = 0;
}
