
//Resistor for switch: R 10 K

  int leftleft, leftright, rightleft, rightright;

  
void setup() {
  leftleft = 1;
  leftright = 1;
  rightleft = 1;
  rightright = 1;
  
  // put your setup code here, to run once:
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(8, INPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);

  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(11, HIGH);
}

void loop() {  

  // RIGHTLEFT
   if( (digitalRead(4) == LOW)) {
    
     if((rightleft == 1) && (rightright == 0)){
      digitalWrite(5, HIGH);
      rightleft = 0;
     }
     else{
      if(rightright == 1){
          for(int i = 0; i < 10; i ++){
            digitalWrite(5, LOW);
            digitalWrite(7, LOW);
            delay(100);
            digitalWrite(5, HIGH);
            digitalWrite(7, HIGH);
            delay(100);
          }

          rightleft = 0;
          rightright = 0;
      }
       else{
          digitalWrite(5, LOW);
          rightleft = 1;
       }
    }
    delay(500);
  } 
  // RIGHTRIGHT
  if( (digitalRead(8) == LOW)) {
    
     if((rightright == 1) && (rightleft == 0)){
      digitalWrite(7, HIGH);
      rightright = 0;
     }
     else{
      if(rightleft == 1){
          for(int i = 0; i < 10; i ++){
            digitalWrite(5, LOW);
            digitalWrite(7, LOW);
            delay(100);
            digitalWrite(5, HIGH);
            digitalWrite(7, HIGH);
            delay(100);
          }

          rightleft = 0;
          rightright = 0;
      }
       else{
          digitalWrite(7, LOW);
          rightright = 1;
       }
    }
    delay(500);
  }  


  //---*------*---------*------*---*------*------*------*-----/
   // LEFTLEFT
   if( (digitalRead(12) == LOW)) {
    
     if((leftleft == 1) && (leftright == 0)){
      digitalWrite(11, HIGH);
      leftleft = 0;
     }
     else{
      if(leftright == 1){
          for(int i = 0; i < 10; i ++){
            digitalWrite(9, LOW);
            digitalWrite(11, LOW);
            delay(100);
            digitalWrite(9, HIGH);
            digitalWrite(11, HIGH);
            delay(100);
          }

          leftleft = 0;
          leftright = 0;
      }
       else{
          digitalWrite(11, LOW);
          leftleft = 1;
       }
    }
    delay(500);
  } 
  // LEFTRIGHT
  if( (digitalRead(10) == LOW)) {
    
     if((leftright == 1) && (leftleft == 0)){
      digitalWrite(9, HIGH);
      leftright = 0;
     }
     else{
      if(leftleft == 1){
          for(int i = 0; i < 10; i ++){
            digitalWrite(9, LOW);
            digitalWrite(11, LOW);
            delay(100);
            digitalWrite(9, HIGH);
            digitalWrite(11, HIGH);
            delay(100);
          }

          leftleft = 0;
          leftright = 0;
      }
       else{
          digitalWrite(9, LOW);
          leftright = 1;
       }
    }
    delay(500);
  }  
  
}
