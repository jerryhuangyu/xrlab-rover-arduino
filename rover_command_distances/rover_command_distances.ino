#include "mecaunm.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Mecaunm_Pid_Init();
  Motor_Init();
  Encoder_Init();
  
  //GoFor300mm();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()){
    char x = Serial.read();
    switch(x){
      case 'a': GoFor300mm();  break;
      case 's': STOP();        break;
      case 'd': BACK();        break;
      default: break;
    }
  }
}

void car_do(void)
{
  ADVANCE();
}
