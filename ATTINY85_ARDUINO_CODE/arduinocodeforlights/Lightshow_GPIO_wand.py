# Welcome to the Elarm Lighting Script
# This script Drives Beaglebone GPIO pins to trigger a pattern switch on an
# ATTINY85 microprocessor that is driving the display LEDs
# it uses 4 pins to provide up to 16 patterns
# The code running on the attiny is located in this repository 
# its called lighting_state_machine_1_16_states
# Written by RISKNC on 7-16-2014
# last updated 7-16-2014
# ==================================SCRIPT USEAGE==============================
# Plug pins P9_16, P9_27, P9_23 and P8_11 to their corresponding pins on the 
# ATTINY85. (use a 4.7k resistor in series between the GPIO and beaglebone pins)
# Bridge the beaglebone ground to the attiny ground
# Plug in power on the beaglebone and ATTINY. The lights should be off (state 0)
# 
# Run The script (likely need to be root) by using the python interpreter e.g. 
# root@beaglebone ~$ python Lightshow.py 1
# The script expects a single argument (an interger between 0-15) that
# represents the requested pattern. 
#
# As soon as the running pattern finishes it should run the pattern you sent
# if there is a previous version of the script runnign  you'll need to kill it
# before a new pattern can be sent. 
#
#
#
# ======================Current Patterns=====================
# Pattern 0 - off
# Pattern 1 - Low White fade in/out
# Pattern 2 - Low Green fade in/out
# Pattern 3 - Low Red fade in/out
# Pattern 4 - Low Red Flashfade
# Pattern 5 - Slow Orange Blinking
# Pattern 6 - Teal fade in/out
# Pattern 7 - Blue Flashfade
# Pattern 8 -
# Pattern 9 - 
# Pattern10 -
# Pattern11 -
# Pattern12 -
# Pattern13 -
# Pattern14 -
# Pattern15 -


#sets up Pass in arguments
import sys

#sets up delays
import time

#GPIO Library
import Adafruit_BBIO.GPIO as GPIO

#Sets pins as GPIO output
GPIO.setup("P9_16", GPIO.OUT)
GPIO.setup("P9_27", GPIO.OUT)
GPIO.setup("P9_23", GPIO.OUT)
GPIO.setup("P8_11", GPIO.OUT)

# Main Loop, breaks on q, otherwise holds pins in whichever state is passed in.
while True:
	# throws an error if the argument isn't valid
	try:
		#inputs argument as userarg
		#userarg= raw_input('Enter desired pattern or q to quit')
		userarg= sys.argv[1]
		# following conditionals send correct pin logic for pattern num
		if userarg == '0':
			GPIO.output("P9_16", GPIO.LOW)
			GPIO.output("P9_27", GPIO.LOW)
			GPIO.output("P9_23", GPIO.LOW)
			GPIO.output("P8_11", GPIO.LOW)
			# Old features for cleaning up pins and debug
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '1':
			GPIO.output("P9_16", GPIO.HIGH)
			GPIO.output("P9_27", GPIO.LOW)
			GPIO.output("P9_23", GPIO.LOW)
			GPIO.output("P8_11", GPIO.LOW)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '2':	
			GPIO.output("P9_16", GPIO.LOW)
			GPIO.output("P9_27", GPIO.HIGH)
			GPIO.output("P9_23", GPIO.LOW)
			GPIO.output("P8_11", GPIO.LOW)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '3':	
			GPIO.output("P9_16", GPIO.HIGH)
			GPIO.output("P9_27", GPIO.HIGH)
			GPIO.output("P9_23", GPIO.LOW)
			GPIO.output("P8_11", GPIO.LOW)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '4':	
			GPIO.output("P9_16", GPIO.LOW)
			GPIO.output("P9_27", GPIO.LOW)
			GPIO.output("P9_23", GPIO.HIGH)
			GPIO.output("P8_11", GPIO.LOW)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '5':	
			GPIO.output("P9_16", GPIO.HIGH)
			GPIO.output("P9_27", GPIO.LOW)
			GPIO.output("P9_23", GPIO.HIGH)
			GPIO.output("P8_11", GPIO.LOW)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '6':	
			GPIO.output("P9_16", GPIO.LOW)
			GPIO.output("P9_27", GPIO.HIGH)
			GPIO.output("P9_23", GPIO.HIGH)
			GPIO.output("P8_11", GPIO.LOW)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		if userarg == '7':
			GPIO.output("P9_16", GPIO.HIGH)
			GPIO.output("P9_27", GPIO.HIGH)
			GPIO.output("P9_23", GPIO.HIGH)
			GPIO.output("P8_11", GPIO.LOW)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '8':
			GPIO.output("P9_16", GPIO.LOW)
			GPIO.output("P9_27", GPIO.LOW)
			GPIO.output("P9_23", GPIO.LOW)
			GPIO.output("P8_11", GPIO.HIGH)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '9':	
			GPIO.output("P9_16", GPIO.HIGH)
			GPIO.output("P9_27", GPIO.LOW)
			GPIO.output("P9_23", GPIO.LOW)
			GPIO.output("P8_11", GPIO.HIGH)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '10':	
			GPIO.output("P9_16", GPIO.LOW)
			GPIO.output("P9_27", GPIO.HIGH)
			GPIO.output("P9_23", GPIO.LOW)
			GPIO.output("P8_11", GPIO.HIGH)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '11':	
			GPIO.output("P9_16", GPIO.HIGH)
			GPIO.output("P9_27", GPIO.HIGH)
			GPIO.output("P9_23", GPIO.LOW)
			GPIO.output("P8_11", GPIO.HIGH)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '12':	
			GPIO.output("P9_16", GPIO.LOW)
			GPIO.output("P9_27", GPIO.LOW)
			GPIO.output("P9_23", GPIO.HIGH)
			GPIO.output("P8_11", GPIO.HIGH)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '13':	
			GPIO.output("P9_16", GPIO.HIGH)
			GPIO.output("P9_27", GPIO.LOW)
			GPIO.output("P9_23", GPIO.HIGH)
			GPIO.output("P8_11", GPIO.HIGH)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '14':	
			GPIO.output("P9_16", GPIO.LOW)
			GPIO.output("P9_27", GPIO.HIGH)
			GPIO.output("P9_23", GPIO.HIGH)
			GPIO.output("P8_11", GPIO.HIGH)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
		elif userarg == '15':	
			GPIO.output("P9_16", GPIO.HIGH)
			GPIO.output("P9_27", GPIO.HIGH)
			GPIO.output("P9_23", GPIO.HIGH)
			GPIO.output("P8_11", GPIO.HIGH)
			#time.sleep(.5)
			#print 'patter 0 triggered (off)'
			#GPIO.output("P9_16", GPIO.LOW)
			#GPIO.cleanup()
	# this condtional breaks the while loop, useful if using raw input
		elif userarg == 'q':
			break
	# error handling (not very great)
	except ValueError:
		print 'Please supply interger arguments between 1 and 4'
