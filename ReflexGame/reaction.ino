
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int ledRed    = 3;
const int ledGreen  = 2;
const int btnRed    = 5;
const int btnGreen  = 4;

const int ROUNDS = 10;       // Upped to 10 rounds!
int currentRound = 0;
int score = 0;
unsigned long timeLimit = 1000; // Starts at 1 second, but gets faster!

int lastChoice = -1;
int streakCount = 0;

void setup() {
  pinMode(btnRed, INPUT);
  pinMode(btnGreen, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
 
  Serial.begin(9600);
  randomSeed(analogRead(0));

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Boot Screen
  display.clearDisplay();
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);    
  display.println(F("--- HARDCORE ---"));
  display.println(F("  REFLEX GAME  "));
  display.println();
  display.println(F("   Get ready..."));
  display.display();
 
  delay(2000);
}

void loop() {
  if (currentRound < ROUNDS) {
    // Show current round info on screen while waiting
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("ROUND "));
    display.print(currentRound + 1);
    display.print(F(" / "));
    display.println(ROUNDS);
    display.print(F("Window: "));
    display.print(timeLimit);
    display.println(F("ms"));
    display.println(F("-----------------"));
    display.println(F("WAITING..."));
    display.display();

    // 1. THE CHAOS GAP: Completely unpredictable wait time (0.1s to 1.0s)
    delay(random(100, 1000));
   
    // Anti-Cheat: Wait for release
    while(digitalRead(btnRed) == HIGH || digitalRead(btnGreen) == HIGH) {
      delay(10);
    }
   
    // 2. ANTI-STREAK RANDOMNESS
    int choice = random(0, 2);
    if (choice == lastChoice) {
      streakCount++;
      if (streakCount >= 2) { // Max 2 of the same color in a row
        choice = (choice == 0) ? 1 : 0;
        streakCount = 0;
      }
    } else {
      streakCount = 0;
    }
    lastChoice = choice;

    int activeLed = (choice == 0) ? ledRed : ledGreen;
    int targetBtn = (choice == 0) ? btnRed : btnGreen;
    int wrongBtn  = (choice == 0) ? btnGreen : btnRed;
   
    digitalWrite(activeLed, HIGH);
    unsigned long startTime = millis();
    bool correctHit = false;
    bool fastFail = false;

    // 3. SHRINKING REACTION WINDOW
    while (millis() - startTime < timeLimit) {
      if (digitalRead(targetBtn) == HIGH) {
        correctHit = true;
        break;
      }
      if (digitalRead(wrongBtn) == HIGH) {
        fastFail = true;
        break;
      }
    }

    digitalWrite(activeLed, LOW);

    // Update Display with Results
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("ROUND "));
    display.println(currentRound + 1);
    display.println(F("-----------------"));
   
    if (correctHit) {
      score++;
      unsigned long reaction = millis() - startTime;
      display.setTextSize(2);
      display.println(F("HIT!"));
      display.setTextSize(1);
      display.print(F("Time: "));
      display.print(reaction);
      display.println(F("ms"));
    }
    else if (fastFail) {
      display.setTextSize(2);
      display.println(F("WRONG!"));
      display.setTextSize(1);
      display.println(F("Check your colors!"));
    }
    else {
      display.setTextSize(2);
      display.println(F("MISS!"));
      display.setTextSize(1);
      display.println(F("Too slow."));
    }
   
    display.display();
    currentRound++;
   
    // 4. THE LEVEL UP: Shave 50ms off the time limit for the next round!
    timeLimit = timeLimit - 50;
   
    delay(1500); // Give the player a second to read their result before the next round
   
  } else {
    // Game Over & Rank Display
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println(F("=== GAME OVER ==="));
    display.println();
   
    display.print(F("Final Score: "));
    display.print(score);
    display.println(F("/10"));
    display.println();
   
    display.println(F("RANK:"));
    display.setTextSize(2);
    if (score == 10) {
      display.println(F("PRO GAMER"));
    } else if (score >= 7) {
      display.println(F("SOLID"));
    } else {
      display.println(F("WAKE UP!"));
    }
    display.display();
   
    while(true); // Halt the game
  }
}

