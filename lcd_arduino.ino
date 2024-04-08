#include <LiquidCrystal.h>

// Initialize the LCD display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonPin = 6; // Push button pin
const int ledPin = 7;    // LED pin

void setup() {
  // Set up the LCD display
  lcd.begin(16, 2);
  
  // Set up the button pin
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Set up the LED pin
  pinMode(ledPin, OUTPUT);
  
  // Display initial message
  lcd.print("Press button");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { // Button is pressed
    startCountdown();
  }
}

void startCountdown() {
  // Turn on the LED
  digitalWrite(ledPin, HIGH);
  
  // Clear the LCD display
  lcd.clear();
  
  // Display countdown
  for (int i = 10; i >= 0; i--) {
    lcd.setCursor(0, 0);
    lcd.print("Countdown: ");
    lcd.print(i);
    
    // Wait for one second
    delay(1000);
  }
  
  // Turn off the LED
  digitalWrite(ledPin, LOW);
  
  // Clear the LCD display
  lcd.clear();
  
  // Display message to press button again
  lcd.print("Press button");
}
