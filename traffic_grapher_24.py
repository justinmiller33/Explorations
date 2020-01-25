'''
Spot test traffic analysis Version 3.
Precursor to dining density project.
Designed to allow for a comprehensive designation and testing for changes
at various spots on MA DOT traffic cams to estimate traffic density.
07/14/2019
'''

###BUG INFO:###
#TEST POINTS CAN NOT TRANSGRESS THE WINDOWS COORDINATE SCALE (1580,800ish)#
#Must test cam in center of screen!

#Number of Spots Tested (IMPORTANT)
spots=2

#Gathering modules (No particular order)

import numpy as np
import matplotlib.pyplot as plt
from PIL import ImageGrab
import win32gui
import time
import math
import pyautogui

'''Identifying and Assigning points for testing'''
#time.sleep(5)

#Total Coordinate Arrays for x and y
xcoords=np.array([])
ycoords=np.array([])

#Adjusters to account for discrepancy in Windows Coords and computer pixels
#Actually might not need these
"""xadj=1920/1535
yadj=1080/863"""

#Begin Collecting
print('Starting point retrievals in:')
time.sleep(1)

#Will do seperate countdown for each to allow mouse placement
for i in range (spots):
    print('3')
    time.sleep(1)
    print('2')
    time.sleep(1)
    print('1')
    time.sleep(1)

    #Temporary Position
    position=win32gui.GetCursorPos()
    xcoords=np.append(xcoords,[position[0]])
    ycoords=np.append(ycoords,[position[1]])
    print(position[0],position[1])

    pyautogui.moveTo(position[0],position[1])

    
    print('Completed '+str(i+1))
    time.sleep(1)
    

'''Beginning of Actual Testing'''

print('Testing underway...')

#Testing variables in order of appearance

#Full array of RGB Values
colors=np.zeros((spots,3))
previous=np.zeros((spots,3))

#Counting runs
runs=0
ran=0

#Variable for changing image
change=0

#Organizing flags and hitpoints
flags=np.zeros((spots))
prevflags=np.zeros((spots))
hits=0
hitpoints=np.array([])


#Mark starting time to create stopwatch
stime=time.time()
watch=np.array([])

while (time.time()-stime<3600):


    #Load Screenshot
    px=ImageGrab.grab().load()
            
    for i in range (spots):

        #Temporary Variable
        rgb=px[xcoords[i],ycoords[i]]

        #Loading new colors
        for j in range (3):
            colors[i,j]=rgb[j]

    

    #Checking to see if the image has changed
    if ran==1:
        for i in range(spots):
            for j in range (3):
                if colors[i,j]!=previous[i,j]:
                    change=1
                    

        if change==1:
            runs=runs+1
            print ('Run ' + str(runs))
            
            #Testing disparity between previous and current colors


                    
            print(prevflags)
            print(flags)
            print(previous)
            print(colors)
            
            for k in range (len(flags)):
                if flags[k]==prevflags[k]==1:
                    hits=hits+1
                    

            print(hits)
            
            hitpoints=np.append(hitpoints,[hits])


            #Copying the previous runs flags
            for l in range (len(flags)):
                prevflags[l]=flags[l]
            
            #Taking time
            watch=np.append(watch,[time.time()-stime])

            #Zeroing temporary flags and hits
            flags=np.zeros((spots))
            hits=0

            change=0

        #Copying previous colors
    for l in range (spots):
        for m in range(3):
            previous[l,m]=colors[l,m]

    ran=1

    
