#include <termios.h>
#include <stdio.h>

#include <ros/ros.h>
#include <std_msgs/UInt16.h>



int scanKeyboard()
{
int in;
struct termios new_settings;
struct termios stored_settings;
tcgetattr(0,&stored_settings);
new_settings = stored_settings;
new_settings.c_lflag &= (~ICANON);
new_settings.c_cc[VTIME] = 0;
tcgetattr(0,&stored_settings);
new_settings.c_cc[VMIN] = 1;
tcsetattr(0,TCSANOW,&new_settings);
 
in = getchar();
 
tcsetattr(0,TCSANOW,&stored_settings);
return in;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "keyboard_demo");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::UInt16>("sucker_control", 1000);;
    std_msgs::UInt16 sucker;

    ROS_INFO("Press '2' to open the sucker");
    ROS_INFO("Press '1' to close the sucker");
    ROS_INFO("Press '0' to close the process");

    int ch;
	while (ros::ok())
    {
        /*
		int keyboard = scanKeyboard();
        switch(keyboard)
        {
            case 49:
                sucker.data = 0;
                break;
            case 51:
                sucker.data = 1;
                break;
            case 50:
                sucker.data = 2;
                break;
            case 48:
                return 0;
        }
        */

        int keyboard = scanKeyboard();
        switch(keyboard)
        {
            case 49:
                sucker.data = 0;
                break;
            case 50:
                sucker.data = 180;
                break;
            case 48:
                return 0;
        }
        pub.publish(sucker);

	}
   

    return 0;
}

