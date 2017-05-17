#include <Arduino.h>
#define MOTOR_NUM 2

const int E1Pin = 10;
const int E2Pin = 11;
const int M1Pin = 12;
const int M2Pin = 13;
const int LEDPin = 3;
const int collidePin = 11;
int cds = A1;
int switch_val = 0;

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
  Serial.begin(9600);

  pinMode(collidePin, INPUT);

  for(i = 0;i < MOTOR_NUM;i++){
    pinMode(Motors[i].enPin, OUTPUT);
    pinMode(Motors[i].directionPin, OUTPUT);
  }
  go(120);
}

void go(int velocity){
  int i;
  for(i = 0;i < MOTOR_NUM;i++){
    digitalWrite(Motors[i].enPin, LOW);
  }
  digitalWrite(Motors[0].directionPin, HIGH);
  digitalWrite(Motors[1].directionPin, LOW);
  analogWrite(Motors[0].enPin, velocity);
  analogWrite(Motors[1].enPin, velocity);
}

void stop(){
  digitalWrite(Motors[0].enPin, LOW);
  digitalWrite(Motors[0].directionPin, HIGH);
  digitalWrite(Motors[1].enPin, LOW);
  digitalWrite(Motors[1].directionPin, LOW);
}

void loop(){
//  int cds_val = analogRead(cds);
//  int collide_val = digitalRead(collidePin); 
//Serial.println(collide_val);
//  if (collide_val == LOW) {
//    stop();
//   
//     
//  }
////  else if (collide_val == LOW) {
////    go(150);
////   
////    
////  }
// 
//
////  if (cds_val > 300){
////    stop();
////  } 
}

