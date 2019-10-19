// 20181106 ypspur_rosにOPENを指示する仕様に変更
#include <ros/ros.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <std_msgs/Bool.h>

#include <cstdlib>
#include <string>

#include <ypspur_ros/ControlMode.h>

using namespace std;

ros::Publisher control_mode_pub;
ros::Publisher emergency_pub;

// use BCM number
//int PIN = 13;
int PIN = 21;
//int PIN = 29;

ypspur_ros::ControlMode control_mode;

int main(int argc, char** argv){
	
	std::string gpio_command = "gpio export " + std::to_string(PIN) + " in";
	std::cout << gpio_command << std::endl;
	std::system(gpio_command.c_str());

	ros::init(argc, argv, "emergency_flag");
	ros::NodeHandle n;

	control_mode_pub = n.advertise<ypspur_ros::ControlMode>("/t_frog/control_mode", 1);
	emergency_pub = n.advertise<std_msgs::Bool>("/emergency_stop", 1);

	control_mode.vehicle_control_mode = ypspur_ros::ControlMode::VELOCITY;

	ros::Rate loop_rate(100);

	// initialize wiringPi
	if(wiringPiSetupSys() == -1){
		cout << "wiringPi init error" << endl;
		return 1;
	}

	// set PIN mode
	pinMode(PIN, INPUT);
	
	while(ros::ok()){
		std_msgs::Bool emergency_stop;

		if(digitalRead(PIN) == 0){
			control_mode.vehicle_control_mode = ypspur_ros::ControlMode::OPEN;
			emergency_stop.data = true;
			cout << "robot stop" << endl;
		}

		else{
			control_mode.vehicle_control_mode = ypspur_ros::ControlMode::VELOCITY;
			emergency_stop.data = false;
			cout << "move" << endl;
		}
			control_mode_pub.publish(control_mode);
			emergency_pub.publish(emergency_stop);

		loop_rate.sleep();
	}

	return 0;
}
