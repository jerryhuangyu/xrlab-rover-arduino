#include <ros.h>
#include <std_msgs/Bool.h>

void messageCb( const std_msgs::Bool& power_state){
  if(power_state.data)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

ros::NodeHandle  nh;
ros::Subscriber<std_msgs::Bool> sub("nozzle/power_state", &messageCb );

void setup()
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
}
