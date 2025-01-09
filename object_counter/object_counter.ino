#include <LiquidCrystal.h>

// Initialize the LCD (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Define pins
const int irSensorPin = 8; // IR sensor connected to digital pin 8
const int ledPin = 9;      // LED connected to digital pin 9

// Variables
int objectCount = 0;
bool objectDetected = false;

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // LED off initially

  lcd.begin(16, 2); // Initialize the LCD (16 columns, 2 rows)

  // Display initial messages
  lcd.setCursor(0, 0);
  lcd.print("Hello All!");
  delay(2000); // Delay for 2 seconds
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to BHS");
  delay(2000); // Delay for 2 seconds
  lcd.clear();
}

void loop() {
  int sensorState = digitalRead(irSensorPin); // Read the IR sensor state

  if (sensorState == LOW && !objectDetected) {
    // Object detected
    objectDetected = true; // Prevent multiple counts for one object
    objectCount++;         // Increment the object count

    if (objectCount <= 5) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Object Count:");
      lcd.setCursor(0, 1);
      lcd.print(objectCount);
    }

    if (objectCount == 5) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Room Full");
      digitalWrite(ledPin, HIGH); // Turn on the LED
    }
  }

  if (sensorState == HIGH && objectDetected) {
    // Object no longer detected
    objectDetected = false;
  }

  if (objectCount < 5) {
    digitalWrite(ledPin, LOW); // Turn off the LED if less than 5 objects
  }
}
