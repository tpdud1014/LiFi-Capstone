#include <Arduino.h>
#define MOTOR_NUM 2

const int E1Pin = 10;
const int E2Pin = 11;
const int M1Pin = 12;
const int M2Pin = 13;
const int LEDPin = 3;

typedef struct {
  byte enPin;
  byte directionPin;
} MotorControl;

const MotorControl Motors[] = {{E1Pin, M1Pin}, {E2Pin, M2Pin}};

// void init(){
//   int i;
//   pinMode(LEDPin, OUTPUT);
//   digitalWrite(LEDPin, LOW);
//
//   for(i = 0;i < MOTOR_NUM;i++){
//     pinMode(Motors[i].enPin, OUTPUT);
//     pinMode(Motors[i].directionPin, OUTPUT);
//   }
// }

void setup(){
  // init();
  int i;
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);

  for(i = 0;i < MOTOR_NUM;i++){
    pinMode(Motors[i].enPin, OUTPUT);
    pinMode(Motors[i].directionPin, OUTPUT);
  }
}

void go(int velocity){
  int i;
  for(i = 0;i < MOTOR_NUM;i++){
    digitalWrite(Motors[i].enPin, LOW);
  }
  digitalWrite(Motors[0].directionPin, LOW);
  digitalWrite(Motors[1].directionPin, HIGH);
  analogWrite(Motors[0].enPin, velocity);
  analogWrite(Motors[1].enPin, velocity);
  delay(1000);
}

void stop(){
  int i;
  for(i = 0;i < MOTOR_NUM;i++){
    digitalWrite(Motors[i].enPin, LOW);
    digitalWrite(Motors[i].directionPin, LOW);
  }
  delay(1000);
}

void loop(){
  go(10);
  stop();
  go(50);
  stop();
  go(100);
  stop();
  go(255);
  stop();
}
