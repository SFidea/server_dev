#!/usr/bin/python
 
# face_detect.py
<<<<<<< HEAD
# Detect face in image print face loacations and save the cropped face
# Usage: python face_detect.py <image_file> <output_file>
 
import sys, os
=======
 
# Face Detection using OpenCV. Based on sample code from:
# http://python.pastebin.com/m76db1d6b
 
# Usage: python face_detect.py <image_file>
 
import sys, os
from opencv.cv import *
from opencv.highgui import *
>>>>>>> cedfa432ede6f40ea9e943409ec0502900abc26f
import cv2
import numpy
import os.path


<<<<<<< HEAD
def detectObjects(image,face_o,crop_o): 
  gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) 
#  cv2.imshow('img',gray)
#  cv2.waitKey(0)
  face_cascade = cv2.CascadeClassifier('/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml')
  eye_cascade = cv2.CascadeClassifier('/usr/share/opencv/haarcascades/haarcascade_eye.xml')

  faces = face_cascade.detectMultiScale(gray, 1.3, 4)
  s = "["
  if len(faces)!=0:
    #print "face detected"
    for (x,y,w,h) in faces:
      s =s+ '{"x":%i,"y":%i,"w":%i,"h":%i}' %(x,y,w,h)
      cv2.rectangle(image,(x,y),(x+w,y+h),(255,0,0),2)
      roi_gray = gray[y:y+h, x:x+w]
      roi_color = image[y:y+h, x:x+w]
      #eyes = eye_cascade.detectMultiScale(roi_gray)
      #for (ex,ey,ew,eh) in eyes:
      #    cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)
      img_crop = image[y:y+h,x:x+w]
      #cv2.imshow('img',img_crop)
      #cv2.waitKey(0)
      cv2.imwrite(crop_o,img_crop) # may have multiple faces problem
      #cv2.imshow('img',image)
      #cv2.waitKey(0)
      #cv2.imwrite(face_o,image) 
  s = s+ "]"
  print s
def main():
  image = cv2.imread(sys.argv[1])
  detectObjects(image,sys.argv[2],sys.argv[3])
=======
def detectObjects(image,face_o,crop_o,w): # w=crop (only store cropped image) w=det(only store image with rect)
  """Converts an image to grayscale and prints the locations of any 
     faces found"""
  grayscale = cvCreateImage(cvSize(image.width, image.height), 8, 1)
  cvCvtColor(image, grayscale, CV_BGR2GRAY)
 
  storage = cvCreateMemStorage(0)
  cvClearMemStorage(storage)
  cvEqualizeHist(grayscale, grayscale)
  cascade = cvLoadHaarClassifierCascade(
    '/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml',
    cvSize(1,1))
  faces = cvHaarDetectObjects(grayscale, cascade, storage, 1.2, 2,
                             CV_HAAR_DO_CANNY_PRUNING, cvSize(50,50))

  if faces:
    for f in faces:
        print("[(%d,%d) -> (%d,%d)]" % (f.x, f.y, f.x+f.width, f.y+f.height))
        img_a = numpy.asarray(image)
        if w=="crop":
                img_crop = img_a[f.y:f.y+f.height,f.x:f.x+f.width]
                cv2.imwrite(crop_o,img_crop) # may have multiple faces problem
        cv2.rectangle(img_a,(f.x, f.y), (f.x+f.width, f.y+f.height),(0,255,0),2)
    if w=="det":
        cv2.imwrite(face_o,img_a)
    

def main():
  image = cvLoadImage(sys.argv[1])
  detectObjects(image,sys.argv[2],sys.argv[3],sys.argv[4])
>>>>>>> cedfa432ede6f40ea9e943409ec0502900abc26f


 
if __name__ == "__main__":
  main()
