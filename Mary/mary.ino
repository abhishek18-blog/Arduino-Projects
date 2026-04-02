#define c4 261  // Frequency for C4
#define d4 294  // Frequency for D4
#define e4 329  // Frequency for E4
#define g4 392  // Frequency for G4

int buzzer = 7;

int melody[] = {e4, d4, c4, d4, e4, e4, e4, 
                d4, d4, d4, e4, g4, g4, 
                e4, d4, c4, d4, e4, e4, e4, 
                d4, d4, d4, e4, g4, g4, 
                e4, d4, c4, d4, e4, e4, e4};

int dur[] = {4, 4, 4, 4, 4, 4, 2, 
             4, 4, 4, 4, 4, 4, 
             4, 4, 4, 4, 4, 4, 2, 
             4, 4, 4, 4, 4, 4, 
             4, 4, 4};

void setup() {
  pinMode(buzzer, OUTPUT);  // Set buzzer pin as output
}

void loop() {
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int durn = 1000 / dur[i];
    tone(buzzer, melody[i], durn);
    delay(durn * 1.30);
    noTone(buzzer);  // Stop sound after the duration
  }
  delay(1000);  // Pause before repeating
}
