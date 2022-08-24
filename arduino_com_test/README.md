## upload subscriber.ino to the UNO
## make sure to chmod usb
## roscore
## rosrun rosserial_python serial_node.py /dev/ttyUSB0 
### (after callback here will nh.loginfo hello)
## rostopic pub toggle_led std_msgs/String hello --once 