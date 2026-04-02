//CONTROL YOUR SCREEN SCROLLING USING ONE ULTRASONIC SENSOR

#include <NewPing.h>

#define trigPin 9

#define echoPin 10

void setup() {
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    long duration, distance;
    
    // Clear the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Set the trigPin HIGH for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Read the echoPin, return time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate distance in cm
    distance = duration * 0.034 / 2; // Speed of sound is 0.034 cm/µs
    
    // Check distance and send commands based on thresholds
    if (distance < 10) {
        Serial.println("Swipe Left"); // Hand is very close
    } else if (distance >= 10 && distance < 20) {
        Serial.println("Swipe Right"); // Hand is moderately close
    } else if (distance >= 20 && distance < 30) {
        Serial.println("Scroll Up"); // Hand is further away
    } else if (distance >= 30) {
        Serial.println("Scroll Down"); // Hand is at a safe distance
    }
    
    delay(500); // Delay for stability
}
