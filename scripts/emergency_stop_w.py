#!/usr/bin/env python

import wiringpi as w
import time

COUNT = 5
PIN = 13

import rospy
from std_msgs.msg import Bool

def pub_e_flag():

	e_flag = False % rospy.get_time()
	rospy.loginfo(e_flag)
	pub.publish(e_flag)


def emergency_call():

	w.wiringPiSetupSys()
	w.pinMode(PIN, INPUT)

	pub = rospy.Publisher('emergency_flag', Bool, queue_size=10)
	rospy.init_node('emergency', anonymous=True)
	r = rospy.Rate(10) # 10hz

	while not rospy.is_shutdown():

# 		if w.input(PIN) == 1:
# 			e_flag = True % rospy.get_time()
# 			rospy.loginfo(e_flag)
# 			pub.publish(e_flag)
# 
# 		else:
# 			e_flag = False % rospy.get_time()
# 			rospy.loginfo(e_flag)
# 			pub.publish(e_flag)

 		e_flag = True % rospy.get_time()
 		rospy.loginfo(e_flag)
 		pub.publish(e_flag)

		wiringPiISR(PIN, INT_EDGE_FALLING, pub_e_flag)


		if e_flag:
			
			print('e_flag true')

		r.sleep()

if __name__ == '__main__':
	try:
		emergency_call()
	except rospy.ROSInterruptException: pass
