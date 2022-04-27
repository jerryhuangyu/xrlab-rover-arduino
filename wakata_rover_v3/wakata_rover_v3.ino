#include "mecanum.h"
#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;

unsigned long previousMillis;
unsigned long currentMillis;
long interval = 100;

float aim_A = 0.0, aim_B = 0.0, aim_C = 0.0, aim_D = 0.0;

// convert angular velocity to the number that should be counted by the encoder_A every 50000ms
void motor_aima(const std_msgs::Float32 &input_msg)
{
  float aim = input_msg.data;
  aim_A = aim * 55 / 6.283;
}
// convert angular velocity to the number that should be counted by the encoder_B every 50000ms
void motor_aimb(const std_msgs::Float32 &input_msg)
{
  float aim = input_msg.data;
  aim_B = aim * 55 / 6.283;
}
// convert angular velocity to the number that should be counted by the encoder_C every 50000ms
void motor_aimc(const std_msgs::Float32 &input_msg)
{
  float aim = input_msg.data;
  aim_C = aim * 55 / 6.283;
}
// convert angular velocity to the number that should be counted by the encoder_D every 50000ms
void motor_aimd(const std_msgs::Float32 &input_msg)
{
  float aim = input_msg.data;
  aim_D = aim * 55 / 6.283;
}

ros::Subscriber<std_msgs::Float32> subfl("motor/front/left", &motor_aima);
ros::Subscriber<std_msgs::Float32> subfr("motor/front/right", &motor_aimb);
ros::Subscriber<std_msgs::Float32> subrl("motor/rear/left", &motor_aimc);
ros::Subscriber<std_msgs::Float32> subrr("motor/rear/right", &motor_aimd);

void setup()
{
  Serial.begin(115200);
  // Serial3.begin(115200);
  Serial.println("Ready");
  // Serial3.write("Ready");

  Mecaunm_Pid_Init();
  Motor_Init();
  Encoder_Init();
  // ros init
  nh.initNode();
  nh.subscribe(subfl);
  nh.subscribe(subfr);
  nh.subscribe(subrl);
  nh.subscribe(subrr);

  previousMillis = millis();
}

void loop()
{
  nh.spinOnce();

  // every 100 ms loop
  currentMillis = millis();
  if ((currentMillis - previousMillis) >= interval)
  {
    previousMillis = currentMillis;
    Follow_Ros(aim_A, aim_B, aim_C, aim_D);
    printencoder();
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
