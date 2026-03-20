// REACTION TIME GAME
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// --- Pin Definitions ---
const int ledPin = 13;
const int buttonPin = 2;
// --- Game Variables ---
LiquidCrystal_I2C lcd(0x27, 16, 2);
unsigned long highScore = 9999; // Initialize with a high value
bool gameRunning = true;
void setup() {
pinMode(ledPin, OUTPUT);
pinMode(buttonPin, INPUT);
lcd.init(); // Use lcd.init() or lcd.begin() depending on your library version
lcd.backlight();
randomSeed(analogRead(0)); // Helps generate truly random numbers
showIntro();
}
void loop() {
// 1. RESET PHASE
digitalWrite(ledPin, LOW);
lcd.clear();
lcd.print("Ready? Wait for");
lcd.setCursor(0, 1);
lcd.print("the Red LED...");
// 2. CHEAT PROTECTION
// If the button is already pressed, wait for them to let go
while (digitalRead(buttonPin) == HIGH) {
lcd.clear();
lcd.print("RELEASE BUTTON!");
delay(500);
}
// 3. RANDOM DELAY (2 to 5 seconds)
delay(random(2000, 5000));
// 4. TRIGGER
lcd.clear();
lcd.print(">> PRESS NOW <<");
digitalWrite(ledPin, HIGH);
unsigned long startTime = millis();
// 5. WAIT FOR REACTION
while (digitalRead(buttonPin) == LOW) {
// Waiting for the user to press the button
}
// 6. CALCULATE & DISPLAY
unsigned long reactionTime = millis() - startTime;
digitalWrite(ledPin, LOW);
displayResults(reactionTime);
delay(4000); // Wait 4 seconds before next round
}
// --- Helper Functions (Makes code cleaner for interviews!) ---
void showIntro() {
lcd.clear();
lcd.setCursor(3, 0);
lcd.print("REACTION TX");
lcd.setCursor(2, 1);
lcd.print("Get Clicking!");
delay(2000);
}
void displayResults(unsigned long time) {
lcd.clear();
lcd.print("Time: ");
lcd.print(time);
lcd.print("ms");
lcd.setCursor(0, 1);
if (time < highScore) {
highScore = time;
lcd.print("NEW RECORD! ***");
} else {
lcd.print("Best: ");
lcd.print(highScore);
lcd.print("ms");
}
}
