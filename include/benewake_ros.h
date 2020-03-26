#ifndef __BENEWAKE_ROS_H_
#define __BENEWAKE_ROS_H_

#include <serial/serial.h>
#include "ros/ros.h"

#define PROTOBUFLENGHT      9

#pragma pack(1)

__attribute__((aligned(1))) typedef struct
{
    uint8_t    end;
}frame_end_t;

__attribute__((aligned(1))) typedef struct
{
    uint8_t  start0;
    uint8_t  start1;
}frame_title_t;

__attribute__((aligned(1)))  typedef struct
{
    frame_title_t title;//帧头
    uint16_t dist;//标签ID
    uint16_t strength;//距离 单位 cm
    uint16_t  temp;//乘以 1000 以后的弧度
    frame_end_t  end;//帧尾
}benewake_report_t;


typedef union benewake_Serial_Data_Union
{
    unsigned char buffer[PROTOBUFLENGHT];

    benewake_report_t benewake_report_date;
    
}benewake_Serial_Data_Union;



#pragma pack(4)


using namespace std;

class Benewake_ros
{
public:
    Benewake_ros();
    ~Benewake_ros();

    /* Read/Write data from ttyUSB */
    bool ReadFromUart(void);
    bool WriteToUart(unsigned char*);
    bool LoopProcess(void);
    bool OpenSerial(void);
    
    //bool

    serial::Serial m_Robot_Serial; //声明串口对象 
    string m_strUsart_ports;
    int m_nBaud_rate;
    

private:  
    ros::NodeHandle m_hNodebenewake;
    ros::Publisher m_pbenewake_pub;
};


#endif
