

const int laser2_1 = 2;
const int laser2_2 = 4;
//const int laser3 = 12;
const int laser2_3 = 0;
const int laser3_1 = 14;
const int laser3_2 = 13;
const int laser2_4 = 15;
const int pushBtn = 12;
const int ledPin = 5;




void setup() {
  // put your setup code here, to run once:
   pinMode(laser2_1, OUTPUT);
   pinMode(laser2_2, OUTPUT);
  // pinMode(laser3, OUTPUT);
   pinMode(laser2_3, OUTPUT);
   pinMode(laser3_1, OUTPUT);
   pinMode(laser3_2, OUTPUT);
    pinMode(laser2_4, OUTPUT);
    pinMode(pushBtn, INPUT);
  pinMode(ledPin, OUTPUT);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(laser2_1,HIGH);
  digitalWrite(laser2_2,HIGH);
  //digitalWrite(laser3,HIGH);
  digitalWrite(laser2_3,HIGH);
  digitalWrite(laser3_1,HIGH);
  digitalWrite(laser3_2,HIGH);
  digitalWrite(laser2_4,HIGH);

  int push_btn_state = digitalRead(pushBtn);
  if (push_btn_state == HIGH) {
          digitalWrite(ledPin, HIGH);
     } 
     else {
      digitalWrite(ledPin, LOW);
      //buttonPressed = true; 
     }
}
