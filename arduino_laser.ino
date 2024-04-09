#include "NewPing.h"

unsigned int distance6;
unsigned int distance2;
unsigned int irReading;
unsigned long startTime;
bool mazeActivated = false;
bool motionDetected = false;
bool buttonPressed = false;
bool wall2Activated = false;
bool wall6Activated = false;
bool wall7Activated = false;
bool wall5Activated = false;
bool wall1Activated = false;//not sure if need 
bool countdown_over = false;
bool irdetected = false;


//declaring constant variables
//US 2,5,6,7 (only using 2 ultrasonic for now)
const int trig_six = 4;
const int echo_six = 15;
const int trig_two = 19;
const int echo_two = 18;
const int max_dist = 100;
const int laser1 = 12;
const int laser2 = 13;
const int laser5 = 26;
const int laser6 = 25;
const int laser6_1 = 33;
const int laser6_2 = 32;
const int laser7 = 27;
const int irSensor = 14;
const int pushBtn = 5;
const int ledPin = 22;
//lcd display might need 2 pins (21&22 based on reserach)

//declare ultrasonic 
NewPing sonar6(trig_six,echo_six, max_dist);
NewPing sonar2(trig_two,echo_two,30);


void setup() {
  Serial.begin(115200);
  pinMode(trig_six, OUTPUT); 
  pinMode(echo_six, INPUT); 
  pinMode(trig_two, OUTPUT); 
  pinMode(echo_two, INPUT); 
  pinMode(pushBtn, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
  pinMode(irSensor, INPUT);
  pinMode(laser5, OUTPUT);
  pinMode(laser6, OUTPUT);
  pinMode(laser7, OUTPUT);
  pinMode(laser6_1, OUTPUT);
  pinMode(laser6_2, OUTPUT);
}

void loop() {
  delay(50);
  int push_btn_state = digitalRead(pushBtn);
  irReading = digitalRead(irSensor);
  distance6 = sonar6.ping_cm();//need t ocndition less than 6
  distance2 = sonar2.ping_cm();
  Serial.println(distance2);

  if (irReading == LOW){
    Serial.println("Motion Detected, Visitors entered the maze");
    mazeActivated = true;
    irdetected = true;
   }

   if (mazeActivated == true){
      if (distance6 > 0 && wall6Activated == false && irdetected == true) {
        //wall 6 should be open!
        
        Serial.println("Countdown of 10s have started");
        startCountdown();
        if (countdown_over = true){
          Serial.println("It is now safe to close off the wall");
          trapGrid6();
          wall6Activated = true;
          Serial.println("All walls of grid 6 is closed!");
        }
        
      }

      if (distance2 > 0 && wall2Activated == false && irdetected == true){
        //wall2 should be open!
        Serial.println("Countdown of 10s have started");
        startCountdown();
        if (countdown_over = true){
          Serial.println("It is now safe to close off the wall");
          digitalWrite(laser2,HIGH);
          wall2Activated = true;
          Serial.println("All walls of grid 2 is closed!");
        }  
      }

     if (push_btn_state == HIGH) {
          digitalWrite(ledPin, HIGH);
     } 
     else {
      digitalWrite(ledPin, LOW);
      buttonPressed = true; 
     }

     if (wall6Activated == true && buttonPressed == true){
        Serial.println("User successfully finished the mini game");
        Serial.println("Grid 6 Deactivated, You can now enter either wall 5 or 7!");
        releaseWall5();
        releaseWall7();
        wall6Activated = false;
        Serial.println("Countdown of 10s have started");
        startCountdown();
        if (countdown_over = true){
          Serial.println("It is now safe to close off the wall");
          trapGrid6();
          wall6Activated = true;
          buttonPressed = false;
          Serial.println("All walls of grid 6 is closed!");
          //wall6 to be opened to allow new users to enter
          releaseWall6();
          releaseWall2();
          irdetected = false;
          
        }
      }


      //assume for this case to restart the program
      if (wall2Activated == true && buttonPressed == true){
        Serial.println("User successfully finished the mini game");
        Serial.println("Grid 2 Deactivated");
        releaseWall2();
        wall2Activated = false;
        buttonPressed = false;
        irdetected = false;
      }
    
    
    
    }

}

void startCountdown() {
  // Start the countdown from 10 to 1
  for (int i = 10; i >= 1; i--) {
    // Display the current count (optional)
    Serial.println(i);

    // Blink the LED for each second
    digitalWrite(ledPin, HIGH); 
    delay(500);                    
    digitalWrite(ledPin, LOW);   
    delay(500);                   

    // set countdown_over boolean val = true
    if (i == 1) {
      countdown_over = true;
    }
  }
}


void trapGrid6(){
  digitalWrite(laser1,HIGH);
  digitalWrite(laser6,HIGH);
  digitalWrite(laser5,HIGH);
  digitalWrite(laser6_1,HIGH);
  digitalWrite(laser6_2,HIGH);
  digitalWrite(laser7,HIGH);
  wall6Activated = true;
  
}

void releaseWall5(){
  digitalWrite(laser5,LOW);
  Serial.println("Wall 5 is released"); 
}

void releaseWall7(){
  digitalWrite(laser7,LOW);
  Serial.println("Wall 7 is released");  
}

void releaseWall6(){
  digitalWrite(laser6_1, LOW);
  Serial.println("Wall 6 is released");
  wall6Activated = false;
}

void releaseWall2(){
  digitalWrite(laser2, LOW);
  Serial.println("Wall 2 is released");
  wall2Activated = false;
}
