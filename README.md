# 俄罗斯方块项目组
## 项目说明
### 工作平台
#### Aubo i3机械臂
存放地点：`机械大楼E305`
#### 自制吸盘装置
存放地点：`东一楼Focus团队`
### 依赖包
#### Ubuntu 18.04
1. 建议下载地址：[网易开源镜像站](http://mirrors.163.com/ubuntu-releases/)
2. 建议安装双系统，不建议使用虚拟机，可能会出现奇奇怪怪的问题。
#### Ros Melodic
安装方法和问题的解决方法在网上都很详细，自行百度。
#### Aubo Melodic
资源下载：[队长的CSDN文章](https://blog.csdn.net/Zheng_Lin_Yu/article/details/113123195?spm=1001.2014.3001.5501)
#### Rosserial Melodic
文件较小，库内直接包含。
#### Arduino ros_lib
单片机代码上传工具，实际操作中不需要安装。
### 吸盘使用方法
0. 吸盘的Subscriber名称为：“sucker_control”，发送信息的类型为:std_msgs/UInt16
1. 连接单片机的USB线，查询单片机的端口（自行百度）
2. 运行 `roscore`
3. 建立通信 `rosrun rosserial_python serial_node.py /dev/ttyUSB0` 注意最后为端口的名称
#### rostopic控制 
1. 释放物体 `rostopic pub /sucker_control std_msgs/UInt16 180` 
2. 吸住物体 `rostopic pub /sucker_control std_msgs/UInt16 0` 
#### 代码控制
`Publisher的使用方法`

## 更新记录
### 2021-11-14
将项目上传到了项目库中
#### 目前完成部分：
1. 单片机与ros的通信
2. 吸盘部分的代码
3. aubo_driver中运动代码的学习使用
#### 下周任务：
1. 连接吸盘并完成控制操作
2. 理解吸盘工作原理并写一个ros程序来实现吸起物体并在两秒后释放的操作
3. 完成给定位姿进行轨迹运动的代码
