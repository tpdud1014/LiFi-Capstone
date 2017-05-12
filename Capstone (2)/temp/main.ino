#include <Arduino.h>
#define DETECT 1
#define RECEIVE 1
#define FORWARD LOW
#define BACKWARD HIGH
#define MOTOR_NUM 2
#define TRUE 1
#define FALSE 0

/*
 * Enable : enable/disable the power
 * PWM : regulate the speed
 */
const int E1Pin = 10;      // Motor-1 Enable
const int E2Pin = 11;      // Motor-2 Enable
const int M1Pin = 12;      // Motor-1 PWM
const int M2Pin = 13;      // Motor-2 PWM
const int LEDPin = 3;      // LED for testing photoresistor

typedef struct {
  byte enPin;
  byte directionPin;
} MotorControl;

const MotorControl Motors[] = {{E1Pin, M1Pin}, {E2Pin, M2Pin}};

// const int Forward = LOW;
// const int Backward = HIGH;

/*
 * Detect the collision.
 * If sensor detect the collision, return DETECT.
 */
int sensingCollision(){
  return DETECT;
}

/*
 * Send the light signal to backward car.
 * If the sensingCollision function returns DETECT, send the light signal.
 * This function has the light signal generation algorithm.
 */
void sendSignal(){

}

/*
 * Receive the light signal from forward car.
 * If the light signal is received and correct signal, return RECEIVE.
 * This function has the light signal interpret algorithm.
 */
int receiveSignal(){

  return RECEIVE;
}

/*
 * Stop the motor.
 * If the receiveSignal function returns the RECEIVE, motor stop immediately.
 */
void stop(){
  int i;
  for(i = 0;i < MOTOR_NUM;i++){
    digitalWrite(Motors[i].enPin, LOW);
    digitalWrite(Motors[i].directionPin, LOW);
  }
  delay(1000);
}

/*
 * Running the motor on input velocity.
 * If sensor detect the collision, return DETECT.
 */
void go(int speed){
  int i;
  for(i = 0;i < MOTOR_NUM;i++){
    digitalWrite(Motors[i].enPin, LOW);
  }
  digitalWrite(Motors[0].directionPin, LOW);
  digitalWrite(Motors[1].directionPin, HIGH);
  analogWrite(Motors[0].enPin, speed);
  analogWrite(Motors[1].enPin, speed);
  delay(1000);
}

/***************************************************
 ******************** MAIN PART ********************
 ***************************************************/
/*
 * initial setting
 * Motors, photoresistor, receive LED, test LED, collision detection sensor.
 */
void setup(){
  int i;
  /* Test LED */
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
  /* Motors */
  for(i = 0;i < MOTOR_NUM; i++){
    pinMode(Motors[i].enPin, OUTPUT);
    pinMode(Motors[i].directionPin, OUTPUT);
    digitalWrite(Motors[i].enPin, LOW);
  }
  go(255);
}

void loop(){
  while(TRUE){
    if(sensingCollision() == DETECT){
      stop();
      sendSignal();
      break;
    }
    if(receiveSignal() == RECEIVE){
      stop();
      break;
    }
  }
  /*
  go(10);
  stop();
  go(50);
  stop();
  go(100);
  stop();
  go(255);
  stop();
  */
}
