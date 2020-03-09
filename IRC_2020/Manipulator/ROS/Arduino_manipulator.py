#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from msg_pkg.msg import manipulator
import serial


class driver:
    def __init__(self):
        # init ros
        rospy.init_node('manipulator_driver', anonymous=True)
        rospy.Subscriber('manipulator_length',manipulator, self.get_cmd_vel)
        self.ser = serial.Serial('/dev/ttyACM0',9600)
        self.get_arduino_message()

    # get cmd_vel message, and get linear velocity and angular velocity
    def get_cmd_vel(self,msg):
        m1 = msg.motor_1_pwm
        m2 = msg.motor_2_pwm
        m3 = msg.motor_3_pwm
        m4 = msg.motor_4_pwm
        m5 = msg.motor_5_pwm
        m6 = msg.motor_6_pwm
	
        self.send_cmd_to_arduino(m1,m2,m3,m4,m5,m6)

    # translate x, and angular velocity to PWM signal of each wheels, and send to arduino
    def send_cmd_to_arduino(self,m1,m2,m3,m4,m5,m6):
        # calculate actuator 1 feed back resistor signal
    	motor1=m1
    	motor2=m2
    	motor3=m3
    	motor4=m4
    	motor5=m5
    	motor6=m6
    	

        # format for arduino
        message = "{},{},{},{},{},{}*".format(motor1,motor2,motor3,motor4,motor5,motor6)
    	print message
        self.ser.write(message)

    # receive serial text from arduino and publish it to '/arduino' message
    def get_arduino_message(self):
        pub = rospy.Publisher('manuplator_arduino', String, queue_size=50)
        r = rospy.Rate(10)
        while not rospy.is_shutdown():
            message = self.ser.readline()
            pub.publish(message)
            r.sleep()

if __name__ == '__main__':
    try:
        d = driver()
    except rospy.ROSInterruptException:
        pass
