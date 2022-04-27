#include "mecanum.h"
//#include "encoder.h"
unsigned long previousMillis;
unsigned long currentMillis;
long interval = 100;

void setup()
{
  Serial.begin(115200);
  Serial3.begin(115200);
  Serial.println("Ready");
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
  Serial.print(ENCODER_3.last_count);
  Serial.print(",輪4:");
  Serial.print(ENCODER_4.last_count);
  Serial.println();
}

void taking_command()
{
  while (Serial3.available())
  {
    char x = Serial3.read();
    switch (x)
    {
    case 's':
      STOP();
      break;
    case 'w':
      ADVANCE();
      break;
    case 'x':
      BACK();
      break;
    case 'a':
      LEFT_2();
      break;
    case 'd':
      RIGHT_2();
      break;
    case 'q':
      LEFT_1();
      break;
    case 'z':
      LEFT_3();
      break;
    case 'e':
      RIGHT_1();
      break;
    case 'c':
      RIGHT_3();
      break;
    case 'v':
      CCW();
      break;
    case 'b':
      CW();
      break;
    default:
      break;
    }
  }
}
