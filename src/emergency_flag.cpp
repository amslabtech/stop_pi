// 20181106 ypspur_rosにOPENを指示する仕様に変更
#include <ros/ros.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <std_msgs/Bool.h>

#include <ypspur_ros/ControlMode.h>

using namespace std;

ros::Publisher control_mode_pub;

int PIN = 13;

ypspur_ros::ControlMode control_mode;

int main(int argc, char** argv){
	
	ros::init(argc, argv, "emergency_flag");
	ros::NodeHandle n;

	control_mode_pub = n.advertise<ypspur_ros::ControlMode>("/t_frog/control_mode", 1);

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

		if(digitalRead(PIN) == 0){
			control_mode.vehicle_control_mode = ypspur_ros::ControlMode::OPEN;
			cout << "robot stop" << endl;
		}

		else{
			control_mode.vehicle_control_mode = ypspur_ros::ControlMode::VELOCITY;
			cout << "move" << endl;
		}
			control_mode_pub.publish(control_mode);

		loop_rate.sleep();
	}

	return 0;
}
