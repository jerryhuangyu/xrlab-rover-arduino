#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"
#define REDUCTION_RATIO 1100  // 50*11*2(interupt於A，其方波high、low變化紀錄一次脈衝,因此2倍)  
                              // 11(電機編碼器基礎脈衝數：11PPR) * 2 * 50(減速比為1:50 = 輸入轉速:輸出轉速)
#define WHEEL 239.3           // 輪子周常 (mm)

typedef struct MOTOR
{
  int pwm_pin;
  int dir1_pin;
  int dir2_pin;
  volatile int aim_pwm;
  volatile int current_error;
  volatile int last_error;
  volatile int previous_error;
  volatile float pwm_out;
  int sum_count;         // 脈衝個數
  float real_circle;     // 實際的圈數
  float caculate_circle; // 计算的圈数
  int average_speed;     // 平均速度
} MOTORDEF;

extern MOTORDEF MOTOR_1, MOTOR_2, MOTOR_3, MOTOR_4;
extern void Motor_Init(void);
extern void Drive_Motor(MOTORDEF motor, int velocity, int dir);
void Motor_Struct_Init(MOTOR *motor);

#endif
