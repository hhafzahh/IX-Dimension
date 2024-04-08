#include "NewPing.h"

unsigned int distance2;
unsigned int irReading;
int v_in = 0;
int v_out = 0;

bool motionDetected = false; // Flag to keep track of motion detection
bool buttonPressed = false; // later program with a physical button
bool wall2Activated = false;
unsigned long startTime; 
const int TRIG = 4;
const int ECHO = 15;
const int MAX_DIST = 100;
const int Laser1 = 12; //entrance wall
const int Laser2 = 13; //second grid wall2
const int Laser3 = 27; //second grid wall3 
const int irsensor = 14;//entrance ir sensor
const int pushBtn = 5;
const int ledpin = 22;

NewPing sonar(TRIG, ECHO, MAX_DIST);//second grid motion sensor

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT); 
  pinMode(ECHO, INPUT);  
  pinMode(pushBtn, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(Laser1, OUTPUT);
  pinMode(Laser2, OUTPUT);
  pinMode(Laser3,OUTPUT);
  pinMode(irsensor, INPUT);
}

void loop() {
  delay(50);
  int push_btn_state = digitalRead(pushBtn);
  irReading = digitalRead(irsensor);
  distance2 = sonar.ping_cm();
  //Serial.println(distance2);
  
  if (irReading == LOW) {
    v_in++; // Increment the count of people entering
      
    if (v_in - v_out == 1) { //entrance wall closed
      Serial.println("Motion Detected");
      motionDetected = true;
      Serial.print("Number of Visitors Going In: ");
      Serial.println(v_in);
      trapWall1();
      trapWall2();
      
    } else {
      // Otherwise, deny entry and reset motion detection
      Serial.println("Sensor is just playing with u!");
      v_in--; // Decrement the count since entry is denied
      motionDetected = false;
    }
 }
  
  
    if (v_in == 1 && buttonPressed == false){
     digitalWrite(ledpin, HIGH);
     //buttonPressed == true;
    }else{
     digitalWrite(ledpin, LOW);
    }

  
  // if condition checks if push button is pressed
  // if pressed LED will turn on otherwise remain off 
  if (push_btn_state == HIGH) {
    digitalWrite(ledpin, HIGH);
  } else {
    digitalWrite(ledpin, LOW);
    
  }

  if (digitalRead(ledpin) == LOW && v_in == 1){
    Serial.println("User successfully finished the mini game");
    buttonPressed = true;
  }
  
 if (distance2 != 0 && v_in == 1 && buttonPressed == true) {
    Serial.println("User entered second grid! Distance: ");
    Serial.print(distance2);
    Serial.println("cm");
    v_out = 1; // Only increment v_out if someone is inside
    Serial.print("Number of Visitors Going Out: ");
    Serial.println(v_out);
    buttonPressed = false;
  }
  
  if ((v_in == 1) && (v_in - v_out == 0)){
    Serial.println("The visitor entered have left the grid, a new user can now come in!! ");
    v_in = 0;
    v_out = 0;
    motionDetected = false;
    releaseWall1();
  }
}

void trapWall1() {
  digitalWrite(Laser1, HIGH);
  Serial.println("Laser1 Switched On");
}

void trapWall2() {
  digitalWrite(Laser2, HIGH);
  wall2Activated = true; // Set wall 2 activation flag to true
  Serial.println("Laser2 Switched On");
}

void releaseWall2() {
  digitalWrite(Laser2, LOW); // Turn off lasers for wall 2
}

void releaseWall1() {
  digitalWrite(Laser1, LOW); // Turn off lasers for wall 1
}
