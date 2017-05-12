#include <Arduino.h>

const int LEDPin = 5;

void setup(){
  pinMode(LEDPin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int sensor = analogRead(A0);
  Serial.println(sensor);
  if(sensor > 600){
    digitalWrite(LEDPin, HIGH);
  } else {
    digitalWrite(LEDPin, LOW);
  }
}
