# benewake_ros test by tf_mini_plu
安装串口包
```
sudo apt install ros-kinetic-serial
```
设置串口连接

这边使用的是CH340
```
sudo ./creat_benewake_ros_udev.sh
```

启动launch

```
roslaunch benewake_ros benewake_ros.launch
```

msg_type
```
std_msgs/Header header
int32 dist
int32 strength
int32 temp
```
topicname
```
/benewake_report_date
```a

结果：
```
---
header: 
  seq: 8163
  stamp: 
    secs: 0
    nsecs:         0
  frame_id: ''
dist: 36
strength: 1555
temp: 2440
---
header: 
  seq: 8164
  stamp: 
    secs: 0
    nsecs:         0
  frame_id: ''
dist: 38
strength: 1485
temp: 2440
---
header: 
  seq: 8165
  stamp: 
    secs: 0
    nsecs:         0
  frame_id: ''
dist: 43
strength: 1626
temp: 2440
---
header: 
  seq: 8166
  stamp: 
    secs: 0
    nsecs:         0
  frame_id: ''
dist: 51
strength: 2480
temp: 2440

```
