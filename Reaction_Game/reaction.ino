const int ledRed    = 9;
const int ledGreen  = 8;
const int btnRed    = 3;
const int btnGreen  = 2;

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

  Serial.println("\n--- HARDCORE REFLEX GAME ---");
  Serial.println("Get ready... The timer gets faster every round!"); 
  delay(1500); 
}

void loop() {
  if (currentRound < ROUNDS) {
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

    // Results
    Serial.print("Round "); 
    Serial.print(currentRound + 1);
    Serial.print(" (Window: ");
    Serial.print(timeLimit);
    Serial.print("ms) -> ");
    
    if (correctHit) {
      score++;
      unsigned long reaction = millis() - startTime;
      Serial.print("HIT! Time: ");
      Serial.print(reaction);
      Serial.println("ms");
    } 
    else if (fastFail) {
      Serial.println("WRONG BUTTON!");
    } 
    else {
      Serial.println("MISS! Too slow.");
    }

    currentRound++;
    
    // 4. THE LEVEL UP: Shave 50ms off the time limit for the next round!
    timeLimit = timeLimit - 50; 
    
    delay(200); // Barely a pause before the next round fires
    
  } else {
    // Game Over & Rank
    Serial.println("\n=== TOURNAMENT OVER ===");
    Serial.print("Final Score: ");
    Serial.print(score);
    Serial.println("/10");
    
    if (score == 10) {
      Serial.println("RANK: ESPORTS PRO!");
    } else if (score >= 7) {
      Serial.println("RANK: SOLID REFLEXES.");
    } else {
      Serial.println("RANK: WAKE UP!");
    }
    
    while(true); 
  }
}

