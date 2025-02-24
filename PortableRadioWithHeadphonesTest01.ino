#include <Wire.h>
#include <TEA5767Radio.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 3, 4, 5, 6, 7);

#define CLK 34
#define DT 35
#define SW 31
#define BUTTON_PIN 2
#define SOUND_SENSOR_PIN 40

TEA5767Radio radio = TEA5767Radio();
float counter = 88.1;
int currentStateCLK;
int lastStateCLK;
int currentStateDT;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool isOn = false;
String receivedString = "";

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SOUND_SENSOR_PIN, INPUT);
  lastStateCLK = digitalRead(CLK);
  lcd.begin(16, 2);
  analogWrite(8, 65);
  lcd.print("Radio off");
  counter = 88.1;
  Wire.begin();
  radio.setFrequency(-10);
  // Initialize Serial1 for communication with ESP32
  Serial1.begin(9600); 
}

void loop() {
  currentStateCLK = digitalRead(CLK);
  currentStateDT = digitalRead(DT);
  int reading = digitalRead(BUTTON_PIN);
  int soundReading = digitalRead(SOUND_SENSOR_PIN);

  // Debounce button
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW) {
      // Button is pressed, change frequency
      counter = 97.5;
      radio.setFrequency(counter);

      // Update the LCD display
      lcd.clear();
      lcd.print("Frequency: ");
      lcd.setCursor(0, 1);
      lcd.print(counter);
    }
  }

  // Clap feature
  if (soundReading == 1) {
    if (isOn == true) {
      radio.setFrequency(-10);
      lcd.clear();
      lcd.print("Radio Off");
      isOn = false;
    } else {
      radio.setFrequency(counter);
      lcd.clear();
      lcd.print("Frequency: ");
      lcd.setCursor(0, 1);
      lcd.print(counter);
      isOn = true;
    }
  }

  lastButtonState = reading;

  // If the rotary encoder is turned
  if (currentStateCLK != lastStateCLK) {
    if (currentStateCLK == LOW) {
      if (currentStateDT == HIGH) {
        counter += 0.1;
        if (counter > 108.0) {
          counter = 108.0;
        }
      } else {
        counter -= 0.1;
        if (counter < 88.0) {
          counter = 88.0;
        }
      }

      // Set the new frequency
      radio.setFrequency(counter);

      // Update the LCD display
      lcd.clear();
      lcd.print("Frequency: ");
      lcd.setCursor(0, 1);
      lcd.print(counter);
    }
  }

  // Bluetooth communication
  if (Serial1.available()) {
    char receivedChar = Serial1.read();
    
    // If received character is a newline, process the string
    if (receivedChar == '\n') {
      float newFrequency = receivedString.toFloat();
      if (newFrequency >= 88.0 && newFrequency <= 108.0) {
        counter = newFrequency;
        radio.setFrequency(counter);
        lcd.clear();
        lcd.print("Frequency: ");
        lcd.setCursor(0, 1);
        lcd.print(counter);
      } else if (newFrequency == -10) {
        radio.setFrequency(-10);
        isOn = false;
        lcd.clear();
        lcd.print("Radio Off");
      }
      // Clear the received string
      receivedString = ""; 
    } else {
      // Add character to received string
      receivedString += receivedChar; 
    }
  }

  lastStateCLK = currentStateCLK;
}
