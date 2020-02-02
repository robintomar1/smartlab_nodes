
#include <ESP8266WiFi.h>


void setup() {

// configure GPIO's and Servo
  pinMode(D1, OUTPUT); // 1,2EN aka D1 pwm left
  pinMode(D2, OUTPUT); // 3,4EN aka D2 pwm right
  pinMode(D3, OUTPUT); // 1A,2A aka D3
  pinMode(D4, OUTPUT); // 3A,4A aka D4
  pinMode(D5, OUTPUT); //  Left encoder
  pinMode(D6, OUTPUT); //  Right encoder
  pinMode(D7, OUTPUT); //  Ultrasonic Echo. D0 with 1k,2k voltage divisor
  pinMode(D0, OUTPUT); // Ultrasonic Trigger. D8 . Power Ultrasonic board with 5v.
}


void loop() {
  digitalWrite(D1, HIGH);
  delay(1000);
  digitalWrite(D2, HIGH);
  delay(1000);
  digitalWrite(D3, HIGH);
  delay(1000);
  digitalWrite(D4, HIGH);
  delay(1000);
  digitalWrite(D5, HIGH);
  delay(1000);
  digitalWrite(D6, HIGH);
  delay(1000);
  digitalWrite(D7, HIGH);
  delay(1000);
  digitalWrite(D0, HIGH);
  delay(1000);
  digitalWrite(D1, LOW);
  delay(1000);
  digitalWrite(D2, LOW);
  delay(1000);
  digitalWrite(D3, LOW);
  delay(1000);
  digitalWrite(D4, LOW);
  delay(1000);
  digitalWrite(D5, LOW);
  delay(1000);
  digitalWrite(D6, LOW);
  delay(1000);
  digitalWrite(D7, LOW);
  delay(1000);
  digitalWrite(D0, LOW);
    //Serial.print("inside loop");
 
  delay(1000);  // milliseconds
}
