#!/usr/bin/python
 
# face_detect.py
 
# Face Detection using OpenCV. Based on sample code from:
# http://python.pastebin.com/m76db1d6b
 
# Usage: python face_detect.py <image_file>
 
import sys, os
from opencv.cv import *
from opencv.highgui import *
import cv2
import numpy
import os.path


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


 
if __name__ == "__main__":
  main()
