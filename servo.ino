#include <Servo.h>

Servo myServo;  // Create a Servo object
const int servoPin = 2;
//const int button=8;// Pin for the servo
//const int ledPin = 19;   // Pin for the LED (usually pin 13 is built-in on Arduino boards)
//const int ledPin = 10;   // Pin for the LED (usually pin 13 is built-in on Arduino boards)

void setup() {
  myServo.attach(servoPin);  // Attach the servo to the defined pin
  ////pinMode(ledPin, OUTPUT);    // Set the LED pin as an OUTPUT
}

void loop() {
 // if(button==1){
  myServo.write(180);        // Move servo to 180 degrees
 // digitalWrite(ledPin, HIGH); // Turn the LED on
  delay(1000);               // Wait for 1 second
  
/*  else{
  myServo.write(0);          // Move servo back to 0 degrees
  //digitalWrite(ledPin, LOW); // Turn the LED off
  delay(1000);               // Wait for 1 second
}*/
}
