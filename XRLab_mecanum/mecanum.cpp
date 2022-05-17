#include "mecanum.h"
WHEELVELDEF WheelVel;

//    ↑A-----B↑
//     |  ↑  |
//     |  |  |
//    ↑C-----D↑
// usePID默認為true，可使電機恆定轉動
void ADVANCE(void)
{
    Set_Aim_Speed(&MOTOR_1, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_2, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_3, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_4, MOTOR_SPEED);
}
//    ↓A-----B↓
//     |  |  |
//     |  ↓  |
//    ↓C-----D↓
void BACK(void)
{
    Set_Aim_Speed(&MOTOR_1, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_2, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_3, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_4, -MOTOR_SPEED);
}

//    =A-----B↑
//     |   ↖ |
//     | ↖   |
//    ↑C-----D=
void LEFT_1(void)
{
    Set_Aim_Speed(&MOTOR_1, 0);
    Set_Aim_Speed(&MOTOR_2, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_3, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_4, 0);
}

//    ↓A-----B↑
//     |  ←  |
//     |  ←  |
//    ↑C-----D↓
void LEFT_2(void)
{
    Set_Aim_Speed(&MOTOR_1, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_2, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_3, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_4, -MOTOR_SPEED);
}

//    ↓A-----B=
//     | ↙   |
//     |   ↙ |
//    =C-----D↓
void LEFT_3(void)
{
    Set_Aim_Speed(&MOTOR_1, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_2, 0);
    Set_Aim_Speed(&MOTOR_3, 0);
    Set_Aim_Speed(&MOTOR_4, -MOTOR_SPEED);
}

//    ↑A-----B=
//     | ↗   |
//     |   ↗ |
//    =C-----D↑
void RIGHT_1(void)
{
    Set_Aim_Speed(&MOTOR_1, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_2, 0);
    Set_Aim_Speed(&MOTOR_3, 0);
    Set_Aim_Speed(&MOTOR_4, MOTOR_SPEED);
}

//    ↑A-----B↓
//     |  →  |
//     |  →  |
//    ↓C-----D↑
void RIGHT_2(void)
{
    Set_Aim_Speed(&MOTOR_1, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_2, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_3, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_4, MOTOR_SPEED);
}

//    =A-----B↓
//     |   ↘ |
//     | ↘   |
//    ↓C-----D=
void RIGHT_3(void)
{
    Set_Aim_Speed(&MOTOR_1, 0);
    Set_Aim_Speed(&MOTOR_2, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_3, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_4, 0);
}
//    =A-----B=
//     |  =  |
//     |  =  |
//    =C-----D=
void STOP(void)
{
    Set_Aim_Speed(&MOTOR_1, 0);
    Set_Aim_Speed(&MOTOR_2, 0);
    Set_Aim_Speed(&MOTOR_3, 0);
    Set_Aim_Speed(&MOTOR_4, 0);
}

//    ↑A-----B↓
//     | ↗ ↘ |
//     | ↖ ↙ |
//    ↑C-----D↓
void CW(void)
{
    Set_Aim_Speed(&MOTOR_1, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_2, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_3, -MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_4, -MOTOR_SPEED);
}

//    ↓A-----B↑
//     | ↙ ↖ |
//     | ↘ ↗ |
//    ↓C-----D↑
void CCW(void)
{
    Set_Aim_Speed(&MOTOR_1, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_2, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_3, MOTOR_SPEED);
    Set_Aim_Speed(&MOTOR_4, MOTOR_SPEED);
}
/**************************************************************************************/
// receive rostopic, update each wheel's speed
// demand is between -255 and 255, using uint8_t causes overflow (uint8_t: 0-255)
// in order to coordinate ros pub topic is <std_msgs::Float32> use int32_t
void Follow_Ros(float pwm_A, float pwm_B, float pwm_C, float pwm_D)
{
    int aim_A = round(pwm_A);
    int aim_B = round(pwm_B);
    int aim_C = round(pwm_C);
    int aim_D = round(pwm_D);
    Set_Aim_Speed(&MOTOR_1, -aim_A); // input is int
    Set_Aim_Speed(&MOTOR_2, aim_B);
    Set_Aim_Speed(&MOTOR_3, -aim_C);
    Set_Aim_Speed(&MOTOR_4, aim_D);
}

velocity ComputeSingleWheelVel(void)
{
    // 4.35091 = (20*239.3/1100)/(50000/1000000)/1000
    float encoder_to_wheel_vel = 0.00435091f;
    WheelVel.a = ENCODER_1.last_count*encoder_to_wheel_vel;
    WheelVel.b = ENCODER_2.last_count*encoder_to_wheel_vel;
    WheelVel.c = ENCODER_3.last_count*encoder_to_wheel_vel;
    WheelVel.d = ENCODER_4.last_count*encoder_to_wheel_vel;
    return WheelVel;
}
//    ↑A-----B↑
//     |  ↑  |
//     |  |  |
//    ↑C-----D↑
// usePID默認為true，可使電機恆定轉動
void Follow_ADVANCE(uint8_t pwm_A, uint8_t pwm_B, uint8_t pwm_C, uint8_t pwm_D)
{
    Set_Aim_Speed(&MOTOR_1, -pwm_A);
    Set_Aim_Speed(&MOTOR_2, pwm_B);
    Set_Aim_Speed(&MOTOR_3, -pwm_C);
    Set_Aim_Speed(&MOTOR_4, pwm_D);
}
//    ↑A-----B↓
//     | ↗ ↘ |
//     | ↖ ↙ |
//    ↑C-----D↓
void Follow_CW(uint8_t pwm_A, uint8_t pwm_B, uint8_t pwm_C, uint8_t pwm_D)
{
    Set_Aim_Speed(&MOTOR_1, -pwm_A);
    Set_Aim_Speed(&MOTOR_2, -pwm_B);
    Set_Aim_Speed(&MOTOR_3, -pwm_C);
    Set_Aim_Speed(&MOTOR_4, -pwm_D);
}

//    ↓A-----B↑
//     | ↙ ↖ |
//     | ↘ ↗ |
//    ↓C-----D↑
void Follow_CCW(uint8_t pwm_A, uint8_t pwm_B, uint8_t pwm_C, uint8_t pwm_D)
{
    Set_Aim_Speed(&MOTOR_1, pwm_A);
    Set_Aim_Speed(&MOTOR_2, pwm_B);
    Set_Aim_Speed(&MOTOR_3, pwm_C);
    Set_Aim_Speed(&MOTOR_4, pwm_D);
}
// make rover advance 300 mm with MOTOR_SPEED
void GoFor300mm(void)
{
    Set_Mecaunm_Position(300, MOTOR_SPEED);
}