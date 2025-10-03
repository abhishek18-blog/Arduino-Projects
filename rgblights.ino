// Define pins for RGB LED
#define RED_PIN 2
#define GREEN_PIN 3
#define BLUE_PIN 5

void setup() {
    // Set the RGB pins as outputs
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
    // Cycle through colors
    setColor(255, 0, 0); // Red
    delay(1000);
    setColor(0, 255, 0); // Green
    delay(1000);
    setColor(0, 0, 255); // Blue
    delay(1000);
    setColor(255, 255, 0); // Yellow
    delay(1000);
    setColor(0, 255, 255); // Cyan
    delay(1000);
    setColor(255, 0, 255); // Magenta
    delay(1000);
    setColor(255, 255, 255); // White
    delay(1000);
}

// Function to set color
void setColor(int redValue, int greenValue, int blueValue) {
    analogWrite(RED_PIN, redValue);
    analogWrite(GREEN_PIN, greenValue);
    analogWrite(BLUE_PIN, blueValue);
}
