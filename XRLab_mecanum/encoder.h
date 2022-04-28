#ifndef ENCODER_H
#define ENCODER_H
#include "Arduino.h"
typedef struct ENCODER
{
    char encoder_a;
    char encoder_b;
    volatile int count;
    volatile int last_count;
    volatile int cmd_vel; // (mm/s)
} ENCODERDEF;

extern ENCODERDEF ENCODER_1, ENCODER_2, ENCODER_3, ENCODER_4;
extern void Encoder_Init(void);
void Encoder_1_Count(void);
void Encoder_2_Count(void);
void Encoder_3_Count(void);
void Encoder_4_Count(void);

#endif
