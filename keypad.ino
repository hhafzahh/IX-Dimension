#include "Keypad.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte rowCount = 4;
const byte colCount = 3;
const byte rowPins[rowCount] = { 11, 10, 9, 8 };
const byte colPins[colCount] = { 7, 6, 5 };
const char keys4x3[rowCount][colCount] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

Keypad keypad = Keypad(makeKeymap(keys4x3), rowPins, colPins, rowCount, colCount);

const int maxPwdLen = 16;
const String password = "5024";
String input;
String inputword;
char keypressed;
boolean success = false;


void setup() {
  Serial.begin(9600);
  input.reserve(maxPwdLen);
  inputword.reserve(maxPwdLen);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Please enter the");
  lcd.setCursor(0, 1);
  lcd.print("passcode");
}


void loop() {
  readKeypad();
  if (!success) {
    if (input.length() > 0) {
      lcd.clear();
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Please enter the");
      lcd.setCursor(0, 1);
      lcd.print("passcode");
    }
  }
  if (keypressed == '#') {
    if (input == password) {
      lcd.setCursor(0, 0);
      lcd.print("Access Granted");
      success = true;
      input = "";
      inputword = "";
      delay(1000);
      lcd.clear();
      delay(1000);
      lcd.print("You have escaped");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Access Denied");
      input = "";
      inputword = "";
      delay(2000);

      lcd.clear();
      delay(500);
      lcd.print("Please Try Again");
      delay(2000);
      lcd.clear();
    }
  }
  if (keypressed == '*') {
    if (input.length() > 0) {
      int lastIndex = input.length() - 1;
      input.remove(lastIndex);
      int lastIndexWord = inputword.length() - 1;
      inputword.remove(lastIndexWord);
      
      lcd.clear();
      lcd.print(input);
      lcd.setCursor(0, 1);
      lcd.print(inputword);
    }
  }
  lcd.setCursor(0, 0);
  lcd.print(input);
  lcd.setCursor(0, 1);
  lcd.print(inputword);
  delay(100);
}

void readKeypad() {
  keypressed = keypad.getKey();
  if (keypressed != '#' && keypressed != '*' && (input.length() < maxPwdLen || inputword.length() < maxPwdLen)) {
    String key = String(keypressed);
    input += key;

    if (keypressed){
      int asciiValue = (keypressed - '0') + 65;
      char asciiLetter = char(asciiValue);
      inputword += asciiLetter;
    }
  }
}