#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;

// void messageCb(const geometry_msgs::Twist& input_msg){
//     float linear_x = input_msg.linear.x;
//     float linear_y = input_msg.linear.y;
//     float angular_z = input_msg.angular.z;
//     char linearx[8];
//     char lineary[8];
//     char angularz[8];
//     dtostrf(linear_x,6,3,linearx);
//     dtostrf(linear_y,6,3,lineary);
//     dtostrf(angular_z,6,3,angularz);
//     nh.loginfo(linearx);
//     nh.loginfo(lineary);
//     nh.loginfo(angularz);
//     digitalWrite(13,HIGH-digitalRead(13));
// }

void motor_fr(const std_msgs::Float32& input_msg){
    char drive_fr[8];
    dtostrf(input_msg.data,6,3,drive_fr);
    nh.loginfo(drive_fr);
    digitalWrite(13,HIGH-digitalRead(13));
}

void motor_fl(const std_msgs::Float32& input_msg){
    char drive_fl[8];
    dtostrf(input_msg.data,6,3,drive_fl);
    nh.loginfo(drive_fl);
    digitalWrite(13,HIGH-digitalRead(13));
}

// ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel",&messageCb);
ros::Subscriber<std_msgs::Float32> subfr("motor/front/right",&motor_fr);
ros::Subscriber<std_msgs::Float32> subfl("motor/front/left",&motor_fl);

void setup(){
    pinMode(13,OUTPUT);
    nh.initNode();
    // nh.subscribe(sub);
    nh.subscribe(subfr);
    nh.subscribe(subfl);
}


void loop(){
    nh.spinOnce();
    delay(1);
}