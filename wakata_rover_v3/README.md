# XRLab Rover Arduino code -- version3.0
## Introduction
![rqt_graph](../images/rover_v3.png)
In this version we accomplish the communication from ROS to Arduino. Receive 4 rostopic /motor/front/left, /motor/front/right, /motor/rear/left, /motor/rear/right, to control each wheel's speed through PID control.
## XRLab_mecanum.zip is an own Arduino library containing 4 part:
### encoder
### motor
### mecanum
### mecanumpid