#include "mecanumpid.h"
#include <TimerFive.h>
PIDDEF V_PID;

void Mecaunm_Pid_Init(void)
{
    V_PID.p = 0.58;
    V_PID.i = 2.2;
    V_PID.d = 0.8;
    V_PID.limit = 250;
    Timer5.initialize(50000); // 50ms
    Timer5.attachInterrupt(PID_IRQHandler);
}

void PID_IRQHandler(void)
{
    Pid_Increase(&ENCODER_1, &MOTOR_1);
    Pid_Increase(&ENCODER_2, &MOTOR_2);
    Pid_Increase(&ENCODER_3, &MOTOR_3);
    Pid_Increase(&ENCODER_4, &MOTOR_4);
    //    Serial.println(ENCODER_1.last_count);
}

void Set_Aim_Speed(MOTOR *motor, int aim_speed)
{
    motor->aim_pwm = aim_speed;
}

void Pid_Increase(ENCODER *encoder, MOTOR *motor) // 增量式PID
{
    encoder->last_count = encoder->count;
    encoder->count = 0;
    if (motor->caculate_circle != 0) //如果设置了目标位置
    {
        motor->sum_count += abs(encoder->last_count);
        if (motor->sum_count >= REDUCTION_RATIO)
        {
            motor->sum_count = 0;
            motor->real_circle++;
        }
        //    if((motor->caculate_circle-motor->real_circle)*REDUCTION_RATIO<=(motor->sum_count-50)) //達到目标位置
        if ((motor->caculate_circle - motor->real_circle) <= 0.5) //達到目标位置
        {
            Set_Aim_Speed(&MOTOR_1, 0);
            Set_Aim_Speed(&MOTOR_2, 0);
            Set_Aim_Speed(&MOTOR_3, 0);
            Set_Aim_Speed(&MOTOR_4, 0);
        }
    }

    motor->current_error = abs(motor->aim_pwm) - abs(encoder->last_count);                                // 計算當前誤差
    motor->pwm_out += V_PID.p * (motor->current_error - motor->last_error)                                // 比例p
                      + V_PID.i * motor->current_error                                                    // 積分i
                      + V_PID.d * (motor->current_error - 2 * motor->last_error + motor->previous_error); // 微分d

    motor->previous_error = motor->last_error;
    motor->last_error = motor->current_error;

    if (motor->pwm_out < 0)
        motor->pwm_out = 0;
    if (motor->pwm_out > V_PID.limit)
        motor->pwm_out = V_PID.limit; // 設定輪子pwm輸出上限 (速度)
    analogWrite(motor->pwm_pin, motor->pwm_out);

    if (motor->aim_pwm > 0) // 設定轉向
    {
        digitalWrite(motor->dir1_pin, HIGH);
        digitalWrite(motor->dir2_pin, LOW);
    }
    else
    {
        digitalWrite(motor->dir1_pin, LOW);
        digitalWrite(motor->dir2_pin, HIGH);
    }
}

void Set_Mecaunm_Position(int distance, int average_speed)
{
    MOTOR_1.caculate_circle = abs(distance) / WHEEL;
    MOTOR_2.caculate_circle = MOTOR_1.caculate_circle;
    MOTOR_3.caculate_circle = MOTOR_1.caculate_circle;
    MOTOR_4.caculate_circle = MOTOR_1.caculate_circle;
    if (distance > 0)
    {
        Set_Aim_Speed(&MOTOR_1, 0 - average_speed);
        Set_Aim_Speed(&MOTOR_2, average_speed);
        Set_Aim_Speed(&MOTOR_3, 0 - average_speed);
        Set_Aim_Speed(&MOTOR_4, average_speed);
    }
    else
    {
        Set_Aim_Speed(&MOTOR_1, average_speed);
        Set_Aim_Speed(&MOTOR_2, 0 - average_speed);
        Set_Aim_Speed(&MOTOR_3, average_speed);
        Set_Aim_Speed(&MOTOR_4, 0 - average_speed);
    }
}
