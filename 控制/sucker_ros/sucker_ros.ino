
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <Servo.h>

ros::NodeHandle nh;
Servo myservo1;
Servo myservo2;

void messageCb(std_msgs::UInt16 servo_msg)
{
  myservo2.write(servo_msg.data);
 
}

ros::Subscriber<std_msgs::UInt16> sucker_sub("sucker_control", messageCb);

void setup()
{
  myservo1.attach(7);
  myservo2.attach(6);
  myservo1.write(180);
  nh.initNode();
  nh.subscribe(sucker_sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
