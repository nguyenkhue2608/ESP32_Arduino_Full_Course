#include <Arduino.h>
const int buttonPin = 16;  // the number of the pushbutton pin
const int ledPin =  17;    // the number of the LED pin

// variable for storing the pushbutton status 
int buttonState = 0;

void setup() {
  Serial.begin(115200);  
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the state of the pushbutton value
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  digitalWrite(ledPin, buttonState);
}