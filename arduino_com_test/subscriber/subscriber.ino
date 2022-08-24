#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

void messageCb(const std_msgs::String &input_msg){
    nh.loginfo(input_msg.data);
    digitalWrite(13,HIGH-digitalRead(13));
}

ros::Subscriber<std_msgs::String> sub("toggle_led",&messageCb);

void setup(){
    pinMode(13,OUTPUT);
    nh.initNode();
    nh.subscribe(sub);
}


void loop(){
    nh.spinOnce();
    delay(1);
}