#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define MOTOR_NUM 2
#define SENSING_COUNT 5
#define THRESHOLD 50
LiquidCrystal_I2C lcd(0x27,16,2);
const int E1Pin = 10;
const int E2Pin = 11;
const int M1Pin = 12;
const int M2Pin = 13;
const int LEDPin = 3;
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

const MotorControl Motors[] = {{E1Pin, M1Pin}, {E2Pin, M2Pin}};







/*-----------------Setup AND Loop Function-----------------*/
////////////////////////////////////////////////////////////////
void setup(){
  lcd.begin();
  lcd.backlight();
  lcd.print("hell");
  lcd.setCursor(0,1);
  lcd.print("V");
  delay(10000);
  lcd.noBacklight();
  lcd.clear();
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
//    wait_for_push_button(); 
//    delay(5000);
//    digitalWrite(LEDPin,HIGH);
//    go(speedo);
//    check_danger();
//    halt();
    send_signal();
//    flag = 0;
}
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
  while(true)
  {
    pre_cds_val = cds_val;
    delay(50);
    cds_val = analogRead(cds);
    Serial.println(cds_val);
    if(pre_cds_val == -1)
    {}
    else
    {
      cds_diff = cds_val - pre_cds_val;
//      Serial.println(cds_diff);
      if(cds_diff<0)
      {
        cds_diff *=-1;
      }
//      Serial.println(cds_diff);
      if(cds_diff>50)
      {
//        Serial.println(cds_val);
      }
    }
//    Serial.println(cds_val);
    int collide_val = digitalRead(collidePin);
    if(cds_diff>=THRESHOLD)
    {
      blink_count++;
//      Serial.println(blink_count++);
    }
    if(blink_count == SENSING_COUNT)
    {
//      break;
    }
    if(collide_val == LOW)
    {
//      break;
    }
  }
  return;
}
////////////////////////////////////////////////////////////////
void send_signal()
{
  digitalWrite(LEDPin, HIGH);
//  while(true){
//    digitalWrite(LEDPin, LOW);
//    delay(20);
//    digitalWrite(LEDPin, HIGH);
//    delay(20);
//  }
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

