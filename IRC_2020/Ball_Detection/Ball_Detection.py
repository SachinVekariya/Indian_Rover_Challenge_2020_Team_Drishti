#!/usr/bin/env python


from __future__ import print_function
import rospy

from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.image import img_to_array
import cv2
import numpy as np
import argparse
import random as rng
import h5py
import yaml
from tensorflow.keras.backend import set_session
import tensorflow as tf
from stage2.msg import ball_msg

out = ball_msg()
rospy.init_node('ball_detection_node')
pub = rospy.Publisher('/ball_publisher', ball_msg, queue_size=1)

config = tf.compat.v1.ConfigProto()
config.gpu_options.per_process_gpu_memory_fraction=0.8
session = tf.compat.v1.Session(config=config)
session1 = tf.compat.v1.Session(config=tf.compat.v1.ConfigProto(log_device_placement=True))

sess = tf.compat.v1.Session(config=config)
tf.compat.v1.keras.backend.set_session (sess)
model = load_model("ball160c.h5")

rng.seed(12345)

def thresh_callback(val,gray):
    
    threshold = val
    ret,th = cv2.threshold(gray,127,255,cv2.THRESH_BINARY)
    canny_output = cv2.Canny(th, threshold, 255)
    contours, _ = cv2.findContours(canny_output, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    color = (rng.randint(0, 256), rng.randint(0, 256), rng.randint(0, 256))
    areas = [cv2.contourArea(c) for c in contours]
    max_index = np.argmax(areas)
    area = cv2.contourArea(contours[max_index])
    print (area)
    cnt = contours[max_index]
    x, y, w, h = cv2.boundingRect(cnt)
    cv2.rectangle(src1, (x, y), (x + w, y + h),color, 2)
    cv2.circle(src1,(x+int(w/2),y+int(h/2)),3,color,-1)
    

    cv2.imshow("souqwrhjkl", src1)
    return x,y,w,h

def color_detect(src):

    hsv=cv2.cvtColor(src,cv2.COLOR_BGR2HSV)
    #print ("Shayad Ball")
    
    low1=np.array([35,58,84])
    high1=np.array([55,255,255])
    h,w = src.shape[:2]
    img_mask1=cv2.inRange(hsv,low1,high1)
    blank_image = np.zeros((h,w,3), np.uint8)
    output1=cv2.bitwise_and(src,src,mask=img_mask1)
    blur = cv2.medianBlur(output1,9)
    gray = cv2.cvtColor(blur,cv2.COLOR_BGR2GRAY)
    thresh = 100
    x,y,w,h = thresh_callback(thresh,gray)
    h1,w1 = src.shape[:2]
    x1=int(w1/2)
    y1=int(h1/2)
    x=int(w/2)+x
    y=y+int(h/2)
    distance_x = int(x - x1)
    distance_y=int(y - y1)
    out.x = distance_x
    out.detect = 1
    area = w*h
    if area > 2500:
        out.distance = 1
    elif (area > 1400 and area < 2500) :
        out.distance = 1.5
    else:
        out.distance = 2 


    """
    edged1 = cv2.Canny(output1,50, 200)
    contours1, hierarchy = cv2.findContours(edged1, cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)
    h1,w1 = src.shape[:2]
    x1=int(w1/2)
    y1=int(h1/2)
    for c in contours1:
        area1 = cv2.contourArea(c)
        if (area1 > 500):
            x, y, w, h = cv2.boundingRect(c)
            cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)
            cv2.putText(frame,'Ball Detected',(x,y),cv2.FONT_HERSHEY_COMPLEX,0.5,(0,255,0),1,cv2.LINE_AA)
            x=int(w/2)+x
            y=y+int(h/2)
            distance_x = int(x - x1)
            distance_y=int(y - y1)
            out.x = distance_x
	    out.detection = 1
            area = w*h
            if area > 2500:
                out.distance = 1
            elif (area > 1400 and area < 2500) :
                out.distance = 1.5
            else:
                out.distance = 2 
	   
     """        
    cv2.imshow("Blanckkkkk",output1)
    cv2.imshow("source_window",src)
    #return src


cap= cv2.VideoCapture("http://192.168.0.104:8081/?action=stream")
counter =0
lcnt = 0
rcnt = 0

while True:
	out.detect = 0
	_,frame = cap.read()
	#print (frame.shape[:2])
	img = frame.copy()
	src = frame.copy()
	src1 = frame.copy()
	if src is None:
		exit(0)
	
	frame1 = frame/255
	frame1 = cv2.resize(frame1,(160,160))
	image = img_to_array(frame1)
	image = image.reshape((1, image.shape[0], image.shape[1], image.shape[2]))
	yhat = model.predict(image)
	thresh=100
	#print (np.argmax(yhat))
	if (np.argmax(yhat) == 0):
		counter = 0
		print("NHI DETECTED")
		out.detect = 0
		
	else:
	    counter += 1
	    if counter >=7:
             print ("BBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAALLLLLLLLLLLLLllllllllllllllllll")
             out.detect = 1			
             try:
		        color_detect(src)
             except ValueError or AttributeError:

	            pass


			    
	
			

	cv2.imshow("source_window", frame)
	pub.publish(out)

	if cv2.waitKey(1)==13:
			break


cap.release()
cv2.destroyAllWindows()
