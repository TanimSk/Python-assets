from gpiozero import Servo
from time import sleep

servo = Servo(25)
val = -1

try:
	while True:
        #servo.min(), mid(), max()
    	servo.value = val
    	sleep(0.1)
    	val = val + 0.1
    	if val > 1:
        	val = -1
except KeyboardInterrupt:
	print("Program stopped")
  
  
  
  
  ##############################################
  
  
  import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

TRIG = 16
ECHO = 18
stat = 0

GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)

GPIO.output(TRIG, False)
print "Calibrating....."
time.sleep(2)

print "Place the object......"


try:
    while True:
       GPIO.output(TRIG, True)
       time.sleep(0.00001)
       GPIO.output(TRIG, False)

       while GPIO.input(ECHO)==0:
          pulse_start = time.time()

       while GPIO.input(ECHO)==1:
          pulse_end = time.time()

       pulse_duration = pulse_end - pulse_start

       distance = pulse_duration * 17150

       distance = round(distance+1.15, 2)
  
       if distance<=20 and distance>=5:
          print "distance:",distance,"cm"
          stat=1
          
       if distance>20 and stat==1:
          print "place the object...."
          stat = 0
       time.sleep(2)

except KeyboardInterrupt:
     GPIO.cleanup()
  
  
  
  
  
  
  
  
  
  
