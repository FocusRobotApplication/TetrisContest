# 俄罗斯方块项目组
## 项目目标
完成俄罗斯方块比赛的机器控制、轨迹规划方面的任务
### 机器控制
1. 学习Aubo机械臂的控制代码，并能够熟练应用
2. 制作吸盘装置，并且能够接入ROS
3. 制作法兰盘并将吸盘装在Aubo机械臂上，并设置工具坐标
#### 最终成果输出
1. 代码：给定多个点和一个固定点的坐标，使之能够在两点之间移动，并在合适的时候开关吸盘
2. 视频：在Aubo实机上运行代码并录制视频
### 轨迹规划
1. 学习Dancing Links算法，了解原理思路
2. 将算法应用于求解俄罗斯方块的游戏上，并且进行可视化展示
3. 将代码移植进ROS当中，与机器控制方面协同操作
#### 最终成果展示
1. 代码：最终结合了机器控制和轨迹规划两方面的成品代码
2. 视频：可视化求解过程的视频
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
### 2021-11-21
1. 已完成：了解了Dancing Links算法的原理
2. 未完成：其他成员尚未连接吸盘并完成程序
#### 下周任务
复习准备考试
### 2021-11-14
1. 将项目上传到了项目库中
2. 初步判断吸盘无法顺利启动的原因是单片机的供电不足
3. 更换其他的思路修复了吸盘无法顺利开启的BUG
#### 目前整体进度
郭皓冉已基本完成机器控制方面的任务，其他成员正在了解吸盘的工作原理
#### 下周任务
1. 其他成员：连接吸盘并完成控制操作
2. 其他成员：理解吸盘工作原理并写一个ros程序来实现吸起物体并在两秒后释放的操作
3. 全体成员：学习Dancing Links的算法
4. 预计成果输出：上述程序的代码与视频
