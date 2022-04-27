// test for driving at various velocities
#include <PID_v1.h> //PID loop from http://playground.arduino.cc/Code/PIDLibrary
#include "encoder.h"

double kp1 = 4;
double ki1 = 4;
double kd1 = 0.3;

double Setpoint1, Input1, Output1, Output1a; //PID variables
PID PID1(&Input1, &Output1, &Setpoint1, kp1, ki1, kd1, DIRECT); //PID Setup

double kp2 = 4;
double ki2 = 4;
double kd2 = 0.3;

double Setpoint2, Input2, Output2, Output2a; //PID variables
PID PID2(&Input2, &Output2, &Setpoint2, kp2, ki2, kd2, DIRECT); //PID Setup

float demand1;
float demand2;

unsigned long currentMillis;
unsigned long previousMillis;

//wheel encoder interrupts
#define encoder0PinA 18  //encoder 1
#define encoder0PinB 31

#define encoder1PinA 19  //encoder 2
#define encoder1PinB 38

volatile long encoder0Pos = 0;  //encoder 1
volatile long encoder1Pos = 0;  //encoder 2

void setup() {
  // put your setup code here, to run once:
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(36, OUTPUT);

  pinMode(encoder0PinA, OUTPUT);
  pinMode(encoder0PinB, OUTPUT);

  pinMode(encoder1PinA, OUTPUT);
  pinMode(encoder1PinB, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(18), Encoder_1_Count, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), Encoder_2_Count, CHANGE);

  //attachInterrupt(4, doEncoderC, CHANGE);
  //attachInterrupt(5, doEncoderD, CHANGE);

  PID1.SetMode(AUTOMATIC);
  PID1.SetOutputLimits(-100,100);
  PID1.SetSampleTime(10);
  
  PID2.SetMode(AUTOMATIC);
  PID2.SetOutputLimits(-100,100);
  PID2.SetSampleTime(10);

  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();

  if(currentMillis - previousMillis >= 10){
    previousMillis = currentMillis;

    if(Serial.available()>0){
      char c = Serial.read();

      if(c=='a'){
        demand1 = 1350;
        demand2 = -1350;
      }
      else if(c=='z'){
        demand1 = 0;
        demand2 = 0;
      }
    }

    Serial.print(encoder0Pos);
    Serial.print(" , ");
    Serial.println(encoder1Pos);
  }
}
