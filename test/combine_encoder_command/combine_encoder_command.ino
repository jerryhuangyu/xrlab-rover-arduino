#include "mecanum.h"
//#include "encoder.h"
unsigned long previousMillis;
unsigned long currentMillis;
long interval = 1000;

void setup()
{
  Serial.begin(115200);
  Serial3.begin(115200);
  Serial3.write("Ready");
  Mecaunm_Pid_Init();
  Motor_Init();
  Encoder_Init();

  previousMillis = millis();
}

void loop()
{
  // take command from serial
  taking_command();

  // print encoder info
  currentMillis = millis();
  if ((currentMillis - previousMillis) >= interval)
  {
    previousMillis = currentMillis;
    printencoder();
    //    Serial.print(currentMillis);
    //    Serial.print(" : ");
    //    Serial.print(previousMillis);
  }
}
void printencoder()
{
  Serial.print(",輪1:");
  Serial.print(ENCODER_1.last_count);
  Serial.print(",輪2:");
  Serial.print(ENCODER_2.last_count);
  Serial.print(",輪3:");
  Serial.print(ENCODER_3.cmd_vel);
  Serial.print(",輪4:");
  Serial.print(ENCODER_4.cmd_vel);
  Serial.println();
}

void taking_command()
{
  while (Serial3.available())
  {
    char x = Serial3.read();
    switch (x)
    {
    case 'a':
      Set_Mecaunm_Position(500, 50);
      Serial.print(" O ");
      break;
    case 's':
      STOP();
      break;
    case 'w':
      BACK();
      break;
    default:
      break;
    }
  }
}
