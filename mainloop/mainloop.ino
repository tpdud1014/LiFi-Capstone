//made by 정현준형
/*Global variable*/

const int TSH = 325; // 쓰레숄드값
int dark = 0; // 1:어두움 0:밝음
int count = 0; // 어둠이 찾아온 횟수(green)
int state = 0; // 0:평소(사고 없음) 1:앞차 사고남 
int red_count = 0; // 깜박인 횟수(red)
const int led = 13; // led 넘버
const int del =15; // led 깜박이는 간격
const int blinkt = 5; // 깜박이는 횟수

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop()
{
  if(state == 0)
  {
    green();
  }
  else if(state == 1)
  {
    red();
  }
}


//평소
void green (void)
{
  digitalWrite(led, HIGH);
  while(true)
  {
    int data = analogRead(A0);
    Serial.print(data);
    Serial.print("\n");
  
    if(data>TSH && dark == 0)
    {
      dark = 1;
      Serial.print(data);
      Serial.print("\n");
    }
    else if(data<TSH && dark == 1&&count<2)
    {
      dark = 0;
      count++;
    }
    else if(data<TSH && dark == 1&&count == 2)
    {
      dark = 0;
      count = 0;
      state = 1;
      break;
    }
    delay(1);
  }
}

//위험
void red()
{ 
  blinkf();
  digitalWrite(led, HIGH);
  state = 0;
}

//위험일때 led 깜박이게 함
void blinkf()
{

  
  while(red_count < blinkt){
    blinking();
    red_count++;
  }

  if(red_count == blinkt)
  {
    red_count = 0;
  }
}

void blinking()
{
  digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(del);                            // wait for a second
  digitalWrite(led, HIGH);    // turn the LED off by making the voltage LOW
  delay(del);                       // wait for a second
}
