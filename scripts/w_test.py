#!/usr/bin/env python

import time
import wiringpi as w 


COUNT = 5
PIN = 13

w.wiringPiSetupSys()
w.pinMode(PIN,1)

for x in xrange(COUNT):
	w.digitalWrite(PIN,1)
	time.sleep(1)
	w.digitalWrite(PIN,0)
	time.sleep(1)
