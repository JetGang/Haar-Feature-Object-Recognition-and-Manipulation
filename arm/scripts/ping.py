#!/usr/bin/env python
# license removed for brevity
import time  
import RPi.GPIO as GPIO
import rospy 
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Vector3

GPIO.setmode(GPIO.BOARD)

def ping():
    pub = rospy.Publisher('/RosAria/cmd_vel', Twist, queue_size=10)
    rospy.init_node('ping')
    rate = rospy.Rate(1) # 10hz
    while not rospy.is_shutdown():
        pub.publish(Twist(Vector3(-0.15,0.0,0.0),Vector3(0.0,0.0,0.0)))
        rospy.loginfo(Twist(Vector3(-0.15,0.0,0.0),Vector3(0.0,0.0,0.0)))
        rate.sleep()
        rate.sleep()
        pub.publish(Twist(Vector3(0.0,0.0,0.0),Vector3(0.0,0.0,0.0)))
        rospy.loginfo(Twist(Vector3(0.0,0.0,0.0),Vector3(0.0,0.0,0.0)))
        break
def ReadDistance(pin):  
   GPIO.setup(pin, GPIO.OUT)  
   GPIO.output(pin, 0)  
  
   time.sleep(0.000002)  
  
  
   #send trigger signal  
   GPIO.output(pin, 1)  
  
  
   time.sleep(0.000005)  
  
  
   GPIO.output(pin, 0)  
  
  
   GPIO.setup(pin, GPIO.IN)  
  
  
   while GPIO.input(pin)==0:  
      starttime=time.time()  
  
  
   while GPIO.input(pin)==1:  
      endtime=time.time()  
        
   duration=endtime-starttime  
   # Distance is defined as time/2 (there and back) * speed of sound 34000 cm/s   
   distance=duration*34000/2  
   return distance  

if __name__ == '__main__':
    try:
        while True:
            distance = ReadDistance(11)
            print "Distance to object is ",distance," cm or ",distance*.3937, " inches"
            time.sleep(0.1)
            if distance<30:
                ping()
                print "stop"
    except rospy.ROSInterruptException:
        pass

