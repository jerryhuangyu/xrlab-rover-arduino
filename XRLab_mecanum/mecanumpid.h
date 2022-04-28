#ifndef MECAUNMPID_H
#define MECAUNMPID_H
#include "encoder.h"
#include "motor.h"

typedef struct PID
{
    float    p;
    float    i;
    float    d;
    int     limit;
}PIDDEF;
extern PIDDEF V_PID;
extern void Mecaunm_Pid_Init(void);
extern void Set_Aim_Speed(MOTOR* motor,int aim_speed);
extern void Set_Mecaunm_Position(int distance,int t);
void Pid_Increase(ENCODERDEF* ENCODER,MOTORDEF* MOTOR);
void PID_IRQHandler(void);
#endif
