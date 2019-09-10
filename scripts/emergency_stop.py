#!/usr/bin/env python

import RPi.GPIO as GPIO
import time

COUNT = 5
PIN = 17

import rospy
from std_msgs.msg import Bool

# GPIO.setmode(GPIO.BCM)

# GPIO.setup(PIN, GPIO.OUT)
# GPIO.setup(18, GPIO.IN)

# for x in xrange(COUNT):
# while True:
# 
# 	GPIO.output(PIN, True)
# 	time.sleep(2)
# 	GPIO.output(PIN, False)
# 	time.sleep(2)
# 
# GPIO.cleanup()

def talker():

	GPIO.setmode(GPIO.BCM)
	GPIO.setup(PIN,GPIO.IN)

	pub = rospy.Publisher('emergency_flag', Bool, queue_size=10)
	rospy.init_node('talker', anonymous=True)
	r = rospy.Rate(10) # 10hz

	while not rospy.is_shutdown():

# 		if GPIO.input(PIN) == 1:
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

		r.sleep()

if __name__ == '__main__':
	try:
		talker()
	except rospy.ROSInterruptException: pass
