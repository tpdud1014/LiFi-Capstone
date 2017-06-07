#include <Arduino.h>
#include <stdlib.h>
#define MOTOR_NUM 2
#define SENSING_COUNT 2
#define THRESHOLD 80

const int E1Pin = 10;
const int E2Pin = 11;
const int M1Pin = 12;
const int M2Pin = 13;
const int LEDPin = 6;
const int collidePin = 8;
const int btnPin = 5;
const int speedo = 100;
int cds = A1;
int switch_val = 0;
int flag = 0;
int isReceived = 0;
int loopgo = 0;
int isBright = 1;

typedef struct {
  byte enPin;
  byte directionPin;
} MotorControl;

char tempChar[10];
char tempChar2[10];
const MotorControl Motors[] = {{E1Pin, M1Pin}, {E2Pin, M2Pin}};







/*-----------------Setup AND Loop Function-----------------*/
////////////////////////////////////////////////////////////////
void setup(){
  

  int i;
  pinMode(LEDPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  digitalWrite(LEDPin, HIGH);
  Serial.begin(9600);


  pinMode(collidePin, INPUT);

  for(i = 0;i < MOTOR_NUM;i++){
    pinMode(Motors[i].enPin, OUTPUT);
    pinMode(Motors[i].directionPin, OUTPUT);
  }
//  go(120);
}
////////////////////////////////////////////////////////////////
void loop(){
    wait_for_push_button();
//    THRESHOLD += 25;
    delay(5000);
    digitalWrite(LEDPin,HIGH);
    go(speedo);
    delay(1000);
    check_danger();
    halt();
    send_signal();
    flag = 0;
}
//void loop()
//{
//  go(150);
//  delay(10000);
//}
////////////////////////////////////////////////////////////////
/*-----------------END-----------------*/









/*-----------------Basic Car Action Function-----------------*/
////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////
void halt(){
  digitalWrite(Motors[0].enPin, LOW);
  digitalWrite(Motors[0].directionPin, HIGH);
  digitalWrite(Motors[1].enPin, LOW);
  digitalWrite(Motors[1].directionPin, LOW);
}
////////////////////////////////////////////////////////////////
/*-----------------END-----------------*/









/*-----------------Advanced Car Action Function-----------------*/
////////////////////////////////////////////////////////////////    
void check_danger()
{
  int isBright = 1;
  int blink_count = 0;
  int cds_val = -1;
  int pre_cds_val = -1;
  int cds_diff = -1;
  int loop_count = 0;
  int count_start = 0;
  while(true)
  {
    for(int k = 0;k < 10;k++){
      tempChar[k] = 0;
      tempChar2[k] = 0;
    }
    pre_cds_val = cds_val;
    delay(31);
    cds_val = analogRead(cds);
    
    if(count_start == 1)
    {
      if(loop_count == 60)
      {
        count_start = 0;
        loop_count = 0;
        blink_count = 0;
      }
      else
        loop_count++;
    }
    if(pre_cds_val == -1)
    {}
    else
    {
      cds_diff = cds_val - pre_cds_val;
      
//      Serial.println(cds_diff);
      if(cds_diff < 0)
      {
        cds_diff *= -1;
      }
    
//      Serial.println(cds_diff);
      
      
    }
//    Serial.println(cds_val);
    int collide_val = digitalRead(collidePin);
    Serial.println(collide_val);
    if(cds_diff >= THRESHOLD)
    {
      if(count_start == 0)
        {
          count_start = 1;
        }
      
      blink_count++;
//          Serial.println(blink_count);
//          Serial.println(THRESHOLD);
     
      
   
      
    }
    if(blink_count == SENSING_COUNT)
    {
      Serial.print("bkink count: ");
      Serial.println(blink_count);
      break;
    }
    if(collide_val == LOW)
    {
      
      break;
    }
  }
  return;
}
////////////////////////////////////////////////////////////////
void send_signal()
{
  for(int i=0;i<30;i++){
    digitalWrite(LEDPin, LOW);
    delay(25);
    digitalWrite(LEDPin, HIGH);
    delay(25);
  }
}
////////////////////////////////////////////////////////////////
void wait_for_push_button()
{
  while(true)
  {
    int a = digitalRead(btnPin);
//    Serial.println(a);
    if(a == 0)
    break; 
  }
}
/*-----------------END-----------------*/

