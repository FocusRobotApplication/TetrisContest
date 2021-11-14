/*
学习如何操作aubo_driver中的命令
Wriiten by GHR
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

#define MAX_JOINT_ACC 100.0/180.0*M_PI  //定义最大关节加速度 单位：弧度/s^2 最大为:M_PI,即180度/s^2
#define MAX_JOINT_VEL 50.0/180.0*M_PI   //定义最大关节速度 单位：弧度/s 最大为:M_PI,即180度/s
#define MAX_END_ACC    0.4                //定义机械臂末端最大加速度 单位：m/s^2 最大为：2
#define MAX_END_VEL    0.2                //定义机械臂末端最大速度 单位：m/s 最大为：2

double init_position[ARM_DOF] = {0};    //设置初始关节位置，全为0即初始姿态

double postion1[ARM_DOF] = {0.0/180.0*M_PI,  0.0/180.0*M_PI,  90.0/180.0*M_PI, 0.0/180.0*M_PI, 90.0/180.0*M_PI,   0.0/180.0*M_PI};
double postion2[ARM_DOF] = {15.0/180.0*M_PI,  0.0/180.0*M_PI,  90.0/180.0*M_PI, 0.0/180.0*M_PI, 90.0/180.0*M_PI,   0.0/180.0*M_PI};

aubo_robot_namespace::Pos position = {.x = 0.45, .y = -0.065, .z = 0.33};
aubo_robot_namespace::cartesianPos_U cartPos = {.position = position};
aubo_robot_namespace::wayPoint_S position3 = {.cartPos = cartPos};

//wayPoint_S
//第一种方式给定xyz，执行（存在问题）
/*
aubo_robot_namespace::wayPoint_S position1;
aubo_robot_namespace::cartesianPos_U position1.cartPos.position;
aubo_robot_namespace::wayPoint_S position1.cartPos.position.y = 0.5100;
aubo_robot_namespace::wayPoint_S position1.cartPos.position.z = 0.2000;
aubo_robot_namespace::wayPoint_S position1.cartPos.positionVector[0] = M_PI;
position1.cartPos.positionVector[1] = 0;
position1.cartPos.positionVector[2] = 0;
*/

/*
aubo_robot_namespace::Pos position = {.x = -0.03, .y = -0.24, .z = 0.73};
aubo_robot_namespace::cartesianPos_U cartPos = {.positionVector={-0.22, -0.24, 0.72}};
aubo_robot_namespace::wayPoint_S position1 = {.cartPos = cartPos};
*/

//四元数
aubo_robot_namespace::Ori ori;
aubo_robot_namespace::Rpy rpy = {.rx = M_PI,.ry = 0,.rz = 0};

//关节角
//double jointposition[ARM_DOF] = {0.0/180.0*M_PI,  0.0/180.0*M_PI,  90.0/180.0*M_PI, 0.0/180.0*M_PI, 90.0/180.0*M_PI, 0.0/180.0*M_PI};


/*
//定义MoveLine运动类型，即机械臂末端移动方式
void AuboMoveLine(AuboDriver &robot_driver)
{
    

    //同理操作，换成末端控制
    robot_driver.robot_send_service_.robotServiceInitGlobalMoveProfile();

    robot_driver.robot_send_service_.robotServiceSetGlobalMoveEndMaxLineAcc(MAX_END_ACC);
    robot_driver.robot_send_service_.robotServiceSetGlobalMoveEndMaxAngleAcc(MAX_END_ACC);
    robot_driver.robot_send_service_.robotServiceSetGlobalMoveEndMaxLineVelc(MAX_END_VEL);
    robot_driver.robot_send_service_.robotServiceSetGlobalMoveEndMaxAngleVelc(MAX_END_VEL);

    robot_driver.robot_send_service_.RPYToQuaternion(rpy, ori);
    aubo_robot_namespace::wayPoint_S position1;
    //position1.orientation = ori;
    //aubo_robot_namespace::cartesianPos_U cartPos = {.positionVector={-0.286364, -0.118942, 0.52}};
    //aubo_robot_namespace::Pos position = {.x = 0.286364, .y = 0.118942, .z = 0.52};
    //aubo_robot_namespace::cartesianPos_U cartPos = {.position = position};
    //position1.cartPos = cartPos;

    ROS_INFO("Now move to position1(wayPoint_S)!");
    int ret = robot_driver.robot_send_service_.robotServiceLineMove(position1, true);
    if(ret != aubo_robot_namespace::InterfaceCallSuccCode)
    {
        ROS_ERROR("Failed to move to postion1, error code:%d", ret);
    }
    /*
    //复位初始位置
    robot_driver.robot_send_service_.robotServiceInitGlobalMoveProfile();

    robot_driver.robot_send_service_.robotServiceSetGlobalMoveJointMaxAcc(jointMaxAcc);
    robot_driver.robot_send_service_.robotServiceSetGlobalMoveJointMaxVelc(jointMaxVelc);
    ROS_INFO("Now move to init_position!");
    ret = robot_driver.robot_send_service_.robotServiceJointMove(init_position, true);
    if(ret != aubo_robot_namespace::InterfaceCallSuccCode)
    {
        ROS_ERROR("Failed to move to initial postion, error code:%d", ret);
    }
    */
   /*
   //初始化移动策略
    robot_driver.robot_send_service_.robotServiceInitGlobalMoveProfile();

    //设置关节的最大移动速度
    aubo_robot_namespace::JointVelcAccParam jointMaxAcc;
    aubo_robot_namespace::JointVelcAccParam jointMaxVelc;
    for(int i = 0; i < ARM_DOF; i++)
    {
        jointMaxAcc.jointPara[i] = MAX_JOINT_ACC;
        jointMaxVelc.jointPara[i] = MAX_JOINT_VEL;
    }
    robot_driver.robot_send_service_.robotServiceSetGlobalMoveJointMaxAcc(jointMaxAcc);
    robot_driver.robot_send_service_.robotServiceSetGlobalMoveJointMaxVelc(jointMaxVelc);

    ROS_INFO("Now move to init_position!");
    //先移动到初始位置
    ret = robot_driver.robot_send_service_.robotServiceJointMove(init_position, true);
    //如果不能执行就报错
    if(ret != aubo_robot_namespace::InterfaceCallSuccCode)
    {
        ROS_ERROR("Failed to move to initial postion, error code:%d", ret);
    }
    
}
*/

void AuboMoveJoint(AuboDriver robot_driver)
{
    /** Initialize move properties ***/
    robot_driver.robot_send_service_.robotServiceInitGlobalMoveProfile();

    /** Set Max joint acc and vel***/
    aubo_robot_namespace::JointVelcAccParam jointMaxAcc;
    aubo_robot_namespace::JointVelcAccParam jointMaxVelc;
    for(int i = 0; i < ARM_DOF; i++)
    {
        jointMaxAcc.jointPara[i] = MAX_JOINT_ACC;
        jointMaxVelc.jointPara[i] = MAX_JOINT_VEL;
    }
    robot_driver.robot_send_service_.robotServiceSetGlobalMoveJointMaxAcc(jointMaxAcc);
    robot_driver.robot_send_service_.robotServiceSetGlobalMoveJointMaxVelc(jointMaxVelc);

    int ret = robot_driver.robot_send_service_.robotServiceJointMove(postion1, true);
    if(ret != aubo_robot_namespace::InterfaceCallSuccCode)
    {
        ROS_ERROR("Failed to move to postion1, error code:%d", ret);
    }

    ret = robot_driver.robot_send_service_.robotServiceJointMove(postion2, true);
    if(ret != aubo_robot_namespace::InterfaceCallSuccCode)
    {
        ROS_ERROR("Failed to move to postion2, error code:%d", ret);
    }

    ret = robot_driver.robot_send_service_.robotServiceJointMove(position3, true);
    if(ret != aubo_robot_namespace::InterfaceCallSuccCode)
    {
        ROS_ERROR("Failed to move to  postion3, error code:%d", ret);
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "learn_to_operate");
    ros::NodeHandle n;
    AuboDriver robot_driver;
    bool ret = robot_driver.connectToRobotController();

    aubo_robot_namespace::ROBOT_SERVICE_STATE result;
    aubo_robot_namespace::ToolDynamicsParam toolDynamicsParam;
    memset(&toolDynamicsParam, 0, sizeof(toolDynamicsParam));

    robot_driver.robot_send_service_.rootServiceRobotStartup(toolDynamicsParam/**tool dynamics paramters**/,
                                             6        /*collision class*/,
                                             true     /* Is allowed to read robot pose*/,
                                             true,    /*default */
                                             1000,    /*default */
                                             result); /*initialize*/

    if(ret)
  {
   // AuboMoveLine(robot_driver);
   AuboMoveJoint(robot_driver);
  }
  else
      ROS_INFO("Failed to connect to the robot controller");

  return 0;
}