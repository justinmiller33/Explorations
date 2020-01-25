import argparse
import datetime
import imutils
import time
import cv2
import random
x=0


vc=cv2.VideoCapture(0)
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video", help="path to the video file")
ap.add_argument("-a", "--min-area", type=int, default=2000, help="minimum area size")
args = vars(ap.parse_args())

if vc.isOpened():
    rval, og=vc.read()
    ogg=cv2.cvtColor(og, cv2.COLOR_BGR2GRAY)

else:
    rval=False

while rval:

    rval, frame=vc.read()
    
    frameg=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    delta=cv2.absdiff(ogg,frameg)


    thresh = cv2.threshold(delta, 25, 255, cv2.THRESH_BINARY)[1]  
    thresh = cv2.dilate(thresh, None, iterations=2)
    cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)

    for c in cnts:
		# if the contour is too small, ignore it
        if cv2.contourArea(c) < args["min_area"]:
            continue
        x, y, w, h = cv2.boundingRect(c)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        print(w*h)
        
           
#Where the size of the rectangle is large enough


    #cv2.imshow('thresh',thresh)
    cv2.imshow('actual',frame)
#new from here
    rval, og=vc.read()
    ogg=cv2.cvtColor(og, cv2.COLOR_BGR2GRAY)

    cv2.imshow('thresh',thresh)

    #to cut
    key = cv2.waitKey(20)
    if key == 27:
        break
    if key == 32:
        rval, og=vc.read()
        ogg=cv2.cvtColor(og, cv2.COLOR_BGR2GRAY)
        key=0


