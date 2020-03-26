#include "benewake_ros.h"
#include "benewake_ros/benewake_msg.h"

bool Benewake_ros::WriteToUart(unsigned char*)
{
	return true;
}
Benewake_ros::Benewake_ros()
{
    
    /* Get Luncher file define value */
    ros::NodeHandle nh_private("~");
   
    nh_private.param<std::string>("serial_port", m_strUsart_ports, "/dev/benewake_ros");
    nh_private.param<int>("serial_baudrate", m_nBaud_rate, 115200); 
   

    m_pbenewake_pub = m_hNodebenewake.advertise<benewake_ros::benewake_msg>("/benewake_report_date", 1000);
}
bool Benewake_ros::OpenSerial(void)
{
    try
    {           
        m_Robot_Serial.setPort(m_strUsart_ports);
        m_Robot_Serial.setBaudrate(m_nBaud_rate);
        serial::Timeout to = serial::Timeout::simpleTimeout(2000);
        m_Robot_Serial.setTimeout(to);
        m_Robot_Serial.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("[OpenSerial] Unable to open port ");
        return false;
    }

    if(m_Robot_Serial.isOpen())
    {
        ROS_INFO_STREAM("[OpenSerial] Serial Port opened");
        return true;
    }
    else
    {
        ROS_INFO_STREAM("[OpenSerial] Serial Port open fail");
        return false;
    }
}
bool Benewake_ros::ReadFromUart(void)
{
    benewake_Serial_Data_Union Reciver_data;
    //Reciver_data.clear();
    memset(&Reciver_data,0,sizeof(benewake_Serial_Data_Union));
    unsigned char RosReadSerialBuffer[1];
    benewake_ros::benewake_msg benewake_data;

    
    if(m_Robot_Serial.available())
    { 
        //ROS_INFO_STREAM("Reading from serial port\n"); 
        m_Robot_Serial.read(Reciver_data.buffer,sizeof(Reciver_data.buffer));

        if (Reciver_data.benewake_report_date.title.start0 == 0x59
        && Reciver_data.benewake_report_date.title.start1 == 0x59
//        && Reciver_data.benewake_report_date.end.end == 0x47
        )
        {
            //check key
            benewake_data.dist = Reciver_data.benewake_report_date.dist;
            benewake_data.strength = Reciver_data.benewake_report_date.strength;
            benewake_data.temp = Reciver_data.benewake_report_date.temp;

            m_pbenewake_pub.publish(benewake_data);
                    
        }
        else
        {
            m_Robot_Serial.read(RosReadSerialBuffer,sizeof(RosReadSerialBuffer));
            ROS_INFO_STREAM("[ReadFromUart] data is illegle !!!\n");
        }
    }
    else
    {
        //ROS_INFO_STREAM("serial is unavailable !!!\n");
    }

    return false;
}
bool Benewake_ros::LoopProcess(void)
{
	
	ros::Rate loop_rate(100);

	while (ros::ok())
	{
		//main logic

		//read urat
		ReadFromUart();

		ros::spinOnce();
		loop_rate.sleep();
	}

	return true;
}
Benewake_ros::~Benewake_ros()
{
	//do nothing
}
int main(int argc, char *argv[])
{
	//init
	ros::init(argc, argv, "benewake_ros");
	
	//creater
    Benewake_ros Benewake_ros_control;
	
	//open serial
	if (!Benewake_ros_control.OpenSerial())
	{
		return false;
	}
	
	//go to main loop
    Benewake_ros_control.LoopProcess();



	return 0;

}






