#include "encoder.h"
ENCODERDEF ENCODER_1,ENCODER_2,ENCODER_3,ENCODER_4;

void Encoder_Init(void)
{
    // 引腳定義
    ENCODER_1.encoder_a=18;
    ENCODER_1.encoder_b=31;
    ENCODER_2.encoder_a=19;
    ENCODER_2.encoder_b=38;  
    ENCODER_3.encoder_a=3;
    ENCODER_3.encoder_b=49;
    ENCODER_4.encoder_a=2;
    ENCODER_4.encoder_b=A1;
    // 引腳初始化
    pinMode(ENCODER_1.encoder_a,INPUT);pinMode(ENCODER_1.encoder_b,INPUT);
    pinMode(ENCODER_2.encoder_a,INPUT);pinMode(ENCODER_2.encoder_b,INPUT);
    pinMode(ENCODER_3.encoder_a,INPUT);pinMode(ENCODER_3.encoder_b,INPUT);
    pinMode(ENCODER_4.encoder_a,INPUT);pinMode(ENCODER_4.encoder_b,INPUT);
    attachInterrupt(digitalPinToInterrupt(18),Encoder_1_Count,CHANGE);
    attachInterrupt(digitalPinToInterrupt(19),Encoder_2_Count,CHANGE);
    attachInterrupt(digitalPinToInterrupt(3), Encoder_3_Count,CHANGE);
    attachInterrupt(digitalPinToInterrupt(2), Encoder_4_Count,CHANGE);
}
void Encoder_1_Count(void)
{
  if(digitalRead(ENCODER_1.encoder_a)==HIGH)
  {
    if(digitalRead(ENCODER_1.encoder_b)==HIGH)    ENCODER_1.count++;
    else if(digitalRead(ENCODER_1.encoder_b)==LOW)ENCODER_1.count--;
  }
  else 
  {
    if(digitalRead(ENCODER_1.encoder_b)==LOW)       ENCODER_1.count++;
    else if(digitalRead(ENCODER_1.encoder_b)==HIGH) ENCODER_1.count--; 
   }
}
void Encoder_2_Count(void)
{
  if(digitalRead(ENCODER_2.encoder_a)==HIGH)
  {
    if(digitalRead(ENCODER_2.encoder_b)==HIGH)    ENCODER_2.count++;
    else if(digitalRead(ENCODER_2.encoder_b)==LOW)ENCODER_2.count--;
  }
  else 
  {
    if(digitalRead(ENCODER_2.encoder_b)==LOW)       ENCODER_2.count++;
    else if(digitalRead(ENCODER_2.encoder_b)==HIGH) ENCODER_2.count--; 
   }
}
void Encoder_3_Count(void)
{
  if(digitalRead(ENCODER_3.encoder_a)==HIGH)
  {
    if(digitalRead(ENCODER_3.encoder_b)==HIGH)    ENCODER_3.count++;
    else if(digitalRead(ENCODER_3.encoder_b)==LOW)ENCODER_3.count--;
  }
  else 
  {
    if(digitalRead(ENCODER_3.encoder_b)==LOW)       ENCODER_3.count++;
    else if(digitalRead(ENCODER_3.encoder_b)==HIGH) ENCODER_3.count--; 
   }
}
void Encoder_4_Count(void)
{
  if(digitalRead(ENCODER_4.encoder_a)==HIGH)
  {
    if(digitalRead(ENCODER_4.encoder_b)==HIGH)    ENCODER_4.count++;
    else if(digitalRead(ENCODER_4.encoder_b)==LOW)ENCODER_4.count--;
  }
  else 
  {
    if(digitalRead(ENCODER_4.encoder_b)==LOW)       ENCODER_4.count++;
    else if(digitalRead(ENCODER_4.encoder_b)==HIGH) ENCODER_4.count--; 
   }
}
