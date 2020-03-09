#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from stage2.msg import Decider


out=Twist()

obstacle_status=0
gps_status=0
goal_status=0
ball_status=0
arrow_status=0

gps_linear=0
gps_angular=0

obstacle_linear=0
obstacle_angular=0

ball_linear=0
ball_angular=0

arrow_linear=0
arrow_angular=0


def cmd_vel_selected():
	global obstacle_status
	global gps_status
	global ball_status
	global gps_linear
	global gps_angular
	global obstacle_linear
	global obstacle_angular
	global ball_linear
	global ball_angular
	global arrow_status
	global arrow_linear
	global arrow_angular

	if (ball_status ==  0):

		if(obstacle_status==0):
			out.linear.x=gps_linear
			out.angular.z=gps_angular
			print("avoiding_obstacle")

		elif(obstacle_status==1):
			out.linear.x=obstacle_linear
			out.angular.z=obstacle_angular
			print("avoiding_obstacle_fwd")
		elif(obstacle_status==2):
			if(arrow ==0):
				out.linear.x=arrow_linear
				out.angular.z=arrow_angular
			else:
				out.linear.x=gps_linear
				out.angular.z=gps_angular 
			print("following goal")
		else :
			out.linear.x=gps_linear
			out.angular.z=gps_angular 
	else:
		out.linear.x=ball_linear
		out.angular.z=ball_angular
		print("Following Ball")
	pub.publish(out)

def callback_obstacle(msg,pub):
	global obstacle_status
	global gps_status
	global ball_status
	global gps_linear
	global gps_angular
	global obstacle_linear
	global obstacle_angular
	global ball_linear
	global ball_angular
	global arrow_status
	global arrow_linear
	global arrow_angular


	obstacle_status=msg.status
	obstacle_linear=msg.twist.linear.x
	obstacle_angular=msg.twist.angular.z

	cmd_vel_selected()


def callback_gps(msg,pub):
	global obstacle_status
	global gps_status
	global ball_status
	global gps_linear
	global gps_angular
	global obstacle_linear
	global obstacle_angular
	global ball_linear
	global ball_angular
	global arrow_status
	global arrow_linear
	global arrow_angular

	gps_status=msg.status
	gps_linear=msg.twist.linear.x
	gps_angular=msg.twist.angular.z



	cmd_vel_selected()


def callback_ball(msg,pub):
	global obstacle_status
	global gps_status
	global ball_status
	global gps_linear
	global gps_angular
	global obstacle_linear
	global obstacle_angular
	global ball_linear
	global ball_angular
	global arrow_status
	global arrow_linear
	global arrow_angular

	ball_status = msg.status
	ball_linear = msg.twist.linear.x
	ball_angular = msg.twist.angular.z

	cmd_vel_selected()

def arrow_callback(msg,pub):
	global obstacle_status
	global gps_status
	global ball_status
	global gps_linear
	global gps_angular
	global obstacle_linear
	global obstacle_angular
	global ball_linear
	global ball_angular
	global arrow_status
	global arrow_linear
	global arrow_angular


	arrow_status = msg.flag
	arrow_linear = msg.x
	arrow_angular = msg.z

	cmd_vel_selected()

if __name__ == '__main__':
	rospy.init_node('path_decider')
	pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)
	sub = rospy.Subscriber('/path_by_obstacle',Decider,callback_obstacle,pub)
	sub1 = rospy.Subscriber('/arrow',Arrow_feedback,arrow_callback,pub)
	sub2 = rospy.Subscriber('/path_by_gps',Decider,callback_gps,pub)
	sub3 = rospy.Subscriber('/path_by_ball',Decider,callback_ball,pub)
	rospy.spin()
