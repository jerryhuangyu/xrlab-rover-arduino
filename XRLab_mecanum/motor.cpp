#include "motor.h"
MOTORDEF MOTOR_1,MOTOR_2,MOTOR_3,MOTOR_4;

void Motor_Struct_Init(MOTOR* motor)
{
    motor->current_error=0;
    motor->last_error=0;
    motor->previous_error=0;
    motor->pwm_out=0;

    motor->sum_count=0;
    motor->real_circle=0;
    motor->caculate_circle=0;                     
}
void Motor_Init(void)
{
    // 引腳定義
    MOTOR_1.pwm_pin=12;
    MOTOR_1.dir1_pin=34;
    MOTOR_1.dir2_pin=35;
    MOTOR_2.pwm_pin=8;
    MOTOR_2.dir1_pin=37;
    MOTOR_2.dir2_pin=36;
    MOTOR_3.pwm_pin=9;
    MOTOR_3.dir1_pin=43;
    MOTOR_3.dir2_pin=42;
    MOTOR_4.pwm_pin=5;
    MOTOR_4.dir1_pin=A4;
    MOTOR_4.dir2_pin=A5;
    // PID相關誤差初始化
    Motor_Struct_Init(&MOTOR_1);
    Motor_Struct_Init(&MOTOR_2);
    Motor_Struct_Init(&MOTOR_3);
    Motor_Struct_Init(&MOTOR_4);
    // 引腳初始化
    pinMode(MOTOR_1.dir1_pin,OUTPUT);pinMode(MOTOR_1.dir2_pin,OUTPUT);pinMode(MOTOR_1.pwm_pin,OUTPUT);
    pinMode(MOTOR_2.dir1_pin,OUTPUT);pinMode(MOTOR_2.dir2_pin,OUTPUT);pinMode(MOTOR_2.pwm_pin,OUTPUT);
    pinMode(MOTOR_3.dir1_pin,OUTPUT);pinMode(MOTOR_3.dir2_pin,OUTPUT);pinMode(MOTOR_3.pwm_pin,OUTPUT);
    pinMode(MOTOR_4.dir1_pin,OUTPUT);pinMode(MOTOR_4.dir2_pin,OUTPUT);pinMode(MOTOR_4.pwm_pin,OUTPUT);  
}
void Drive_Motor(MOTORDEF motor,int velocity,int dir)
{
      if(dir){digitalWrite(motor.dir1_pin,LOW);digitalWrite(motor.dir2_pin,HIGH);}
      else   {digitalWrite(motor.dir1_pin,HIGH);digitalWrite(motor.dir2_pin,LOW);}
      analogWrite(motor.pwm_pin,velocity);
 }
 
