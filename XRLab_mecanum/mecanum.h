#ifndef MECAUNM_H
#define MECAUNM_H
#include "mecanumpid.h"

#define MOTOR_SPEED 20

extern void ADVANCE(void);
extern void BACK(void);
extern void LEFT_1(void);
extern void LEFT_2(void);
extern void LEFT_3(void);
extern void RIGHT_1(void);
extern void RIGHT_2(void);
extern void RIGHT_3(void);
extern void STOP(void);
extern void CW(void);
extern void CCW(void);
extern void Follow_Ros(float pwm_A, float pwm_B, float pwm_C, float pwm_D);
extern void Follow_ADVANCE(uint8_t pwm_A, uint8_t pwm_B, uint8_t pwm_C, uint8_t pwm_D);
extern void Follow_CW(uint8_t pwm_A, uint8_t pwm_B, uint8_t pwm_C, uint8_t pwm_D);
extern void Follow_CCW(uint8_t pwm_A, uint8_t pwm_B, uint8_t pwm_C, uint8_t pwm_D);
extern void GoFor300mm(void);

#endif
