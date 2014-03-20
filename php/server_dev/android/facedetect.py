#!/usr/bin/python
 
# face_detect.py
# Detect face in image print face loacations and save the cropped face
# Usage: python face_detect.py <image_file> <output_file>
 
import sys, os
import cv2
import numpy
import os.path


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


 
if __name__ == "__main__":
  main()
