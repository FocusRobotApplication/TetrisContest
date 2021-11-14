/*
一个关于使用aubo_driver内提供的逆解函数包的demo
目标:给予一个xyz与rpy,输出一个waypoint
Written by GHR
*/


#include "aubo_driver/aubo_driver.h"
#include "aubo_driver.cpp"

#include <string>
#include <cstdlib>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <fstream>

using namespace aubo_driver;

void printRoadPoint(const aubo_robot_namespace::wayPoint_S *waypoint)
{
    ROS_INFO("pos.x = %.4f",waypoint->cartPos.position.x);
    ROS_INFO("pos.y = %.4f",waypoint->cartPos.position.y);
    ROS_INFO("pos.z = %.4f",waypoint->cartPos.position.z);
    ROS_INFO("ori.w = %.4f",waypoint->orientation.w);
    ROS_INFO("ori.x = %.4f",waypoint->orientation.x);
    ROS_INFO("ori.y = %.4f",waypoint->orientation.y);
    ROS_INFO("ori.z = %.4f",waypoint->orientation.z);
    ROS_INFO("joint_1 = %.6f",waypoint->jointpos[0] * 180 / M_PI);
    ROS_INFO("joint_2 = %.6f",waypoint->jointpos[1] * 180 / M_PI);
    ROS_INFO("joint_3 = %.6f",waypoint->jointpos[2] * 180 / M_PI);
    ROS_INFO("joint_4 = %.6f",waypoint->jointpos[3] * 180 / M_PI);
    ROS_INFO("joint_5 = %.6f",waypoint->jointpos[4] * 180 / M_PI);
    ROS_INFO("joint_6 = %.6f",waypoint->jointpos[6] * 180 / M_PI);
}


void example_ik(AuboDriver &robot_driver)
{
    aubo_robot_namespace::wayPoint_S waypoint;

    double startjoint[ARM_DOF] = {0};

    aubo_robot_namespace::Pos targetPos = {.x = -0.4000, .y = -0.1215, .z = 0.5476};

    aubo_robot_namespace::Rpy targetRpy = {.rx = M_PI, .ry = 0, .rz = -90 / 180 * M_PI};

    aubo_robot_namespace::Ori targetOri;

    robot_driver.robot_send_service_.RPYToQuaternion(targetRpy, targetOri);

    int ret = robot_driver.robot_send_service_.robotServiceRobotIk(startjoint, targetPos, targetOri, waypoint);

    if(ret == aubo_robot_namespace::InterfaceCallSuccCode)
    {
        printRoadPoint(&waypoint);
    }
    else ROS_ERROR("Failed to get ik, error code: %d", ret);
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "ik_demo");

    ros::NodeHandle n;

    AuboDriver robot_driver;


    example_ik(robot_driver);

    return 0;
}