#include <LiquidCrystal.h>

// Initialize the LCD with the appropriate pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define the current and next destinations
const char* currentDestination = "WELCOME TO THE PORTAL";
const char* nextDestination = "ABHISHEK DESHMUKH!!!";

void setup() {
    lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
}

void loop() {
    // Display current destination scrolling from left to right
    scrollMessage(currentDestination);
    
    // Short delay before showing next destination
    delay(2000);
    
    // Display next destination scrolling from left to right
    scrollMessage(nextDestination);
    
    // Short delay before repeating the loop
    delay(2000);
}

// Function to scroll a message across the LCD display from left to right
void scrollMessage(const char* message) {
    int messageLength = strlen(message);
    int displayWidth = 16; // Width of the LCD display

    // Clear the display before scrolling new message
    lcd.clear();
    
    // Loop through each position of the message for scrolling effect
    for (int position = -displayWidth; position < messageLength; position++) {
        lcd.clear(); // Clear previous message
        
        // Print spaces before the actual message for scrolling effect
        for (int i = position; i < position + displayWidth; i++) {
            if (i >= 0 && i < messageLength) {
                lcd.write(message[i]); // Display character if within bounds
            } else {
                lcd.write(' '); // Print space if out of bounds
            }
        }
        
        delay(300); // Adjust speed of scrolling here (200 ms)
    }
}
