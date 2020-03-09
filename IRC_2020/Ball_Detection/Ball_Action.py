#!/usr/bin/env python
import rospy

from geometry_msgs.msg import Twist
from stage2.msg import ball_msg
from stage2.msg import Decider


count=0
flag_reached=0
out = Decider()
out.status=0

rate=0

def stop():
	global out
	out.twist.linear.x = 0
	out.twist.angular.z = 0
	out.status = 1
	print("ball reached!!!!!")

def find_ball():
	global out
	out.twist.linear.x = 0
	out.twist.angular.z = 3
	out.status = 0
	print("Finding ball")


def callback(msg,pub):
	global out
	global count,rate
	global flag_reached
	error=msg.x
	if(flag_reached == 1):
		stop()
		print("goal reached BY BALL detection!!!!!")

	elif(msg.detect == 1):
		count=0
		if(error > 80):
			
			out.twist.linear.x = 0
			out.twist.angular.z = -3
			out.status = 1
			if(msg.distance==1):
				out.twist.linear.x = 0
				out.twist.angular.z = 0
				out.status = 1
				print("goal reached!!!!!")
				flag_reached=1
			print("setting angle right")
		elif(error < -80):
			out.twist.linear.x = 0
			out.twist.angular.z = 3
			out.status = 1
			if(msg.distance==1):
				out.twist.linear.x = 0
				out.twist.angular.z = 0
				out.status = 1
				print("goal reached!!!!!")
				flag_reached=1
			print("setting angle left")
			
		else:
			if(msg.distance==1):
				out.twist.linear.x = 0
				out.twist.angular.z = 0
				out.status = 1
				print("goal reached!!!!!")
				flag_reached=1
			
			elif(msg.distance == 1.5):
				out.twist.linear.x = 6 ## set forward
				out.twist.angular.z = 0
				out.status = 1
				flag_reached = 0 
				print("going forward(1.5):")

			else:
				out.twist.linear.x = 6 ## set forward
				out.status = 1
				out.twist.angular.z = 0
				flag_reached = 0
				print("going forward:")

	else:
		#count=0
		if(count == 50):
			find_ball()
		else:
			count = count + 1
	
	pub.publish(out)


if __name__ == "__main__":
	rospy.init_node('ball_follower')
	rate = rospy.Rate(10)
	pub = rospy.Publisher('/path_by_ball', Decider, queue_size=1)
	sub=rospy.Subscriber('/ball_publisher', ball_msg,callback,pub)
	rospy.spin()
