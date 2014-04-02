//============================================================================
// Name        : computebmi.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include "stasm_lib.h"
#include "stasm_landmarks.h"
#include <fstream>
#include <sstream>

using namespace std;

//BMI code**Lingyun Wen****
//*************************
void getBMIfeature(float* landmarksint, double *feature);
IplImage * GeometricalTransform(IplImage * src, float Leye_x, float Leye_y,
		float Reye_x, float Reye_y, float NewLeye_x, float NewLeye_y,
		float NewReye_x, float NewReye_y, CvSize newSize);

void BMIfunction(double* feature, cv::Mat img_rgb, char* argv[]) {
//cv::Mat img_rgb = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!img_rgb.data) {
		printf("Cannot load %s\n", argv[1]);
		exit(1);
	}
	//IplImage src=cvCloneImage(&(img_rgb));

	cv::Mat img_grey;
	cvtColor(img_rgb, img_grey, CV_BGR2GRAY);

	int foundface;
	float landmarks[2 * stasm_NLANDMARKS]; // x,y coords
	float newlandmarks[2 * stasm_NLANDMARKS]; // x,y coords

	if (!stasm_search_single(&foundface, landmarks, (char*) img_grey.data,
			img_grey.cols, img_grey.rows, argv[1], argv[2])) {
		printf("Error in stasm_search_single: %s\n", stasm_lasterr());
		exit(1);
	}

	if (!foundface)
		printf("No face found in %s\n", argv[1]);
	else {

		CvSize newSize; // newSize denotes the size of final image
		newSize.width = 400;
		newSize.height = 480;
		IplImage src = img_grey;
		//float(lanndmarks[(39-1)*2]), float(landmarks[(39-1)*2+1]),float(landmarks[(40-1)*2]),
		//		float(landmarks[(40-1)*2+1]), float(160), float(225), float(220), float(225), newSize);
		IplImage * newIm = GeometricalTransform(&src,
				float(landmarks[(39 - 1) * 2]),
				float(landmarks[(39 - 1) * 2 + 1]),
				float(landmarks[(40 - 1) * 2]),
				float(landmarks[(40 - 1) * 2 + 1]), float(160), float(225),
				float(220), float(225), newSize);

		cv::Mat newImMat = cv::Mat(newIm);
		stasm_search_single(&foundface, newlandmarks, (char*) newImMat.data,
				newImMat.cols, newImMat.rows, argv[1], argv[2]);
		getBMIfeature(newlandmarks, feature);

	}
}

float linesqr(float x1, float y1, float x2, float y2) {
	return (x2 - x1) * (y1 + y2) / 2.0;
}

float distance(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y1 - y2) * (y1 - y2));
}

//get 7 facial ratios
//input landmarksint
//output feature with 7 elements
void getBMIfeature(float* landmarks, double *feature) {
	//produce x--CJWR
	int p1_x = landmarks[(1 - 1) * 2];
	int p1_y = landmarks[(1 - 1) * 2 + 1];
	int p15_x = landmarks[12 * 2];
	int p15_y = landmarks[12 * 2 + 1];
	int p4_x = landmarks[(4 - 1) * 2];
	int p4_y = landmarks[(4 - 1) * 2 + 1];
	int p10_x = landmarks[(10 - 1) * 2];
	int p10_y = landmarks[(10 - 1) * 2 + 1];
	double CJWR = double(distance(p1_x, p1_y, p15_x, p15_y))
			/ double((distance(p4_x, p4_y, p10_x, p10_y)));
	//produce x--WHR
	int p71_x = landmarks[(71 - 1) * 2];
	int p71_y = landmarks[(71 - 1) * 2 + 1];

	double N1_x = (landmarks[(33 - 1) * 2] + landmarks[(43 - 1) * 2]) / 2.0;
	double N1_y = (landmarks[(33 - 1) * 2 + 1] + landmarks[(43 - 1) * 2 + 1])
			/ 2.0;
	double WHR = double(distance(p1_x, p1_y, p15_x, p15_y))
			/ double((distance(p71_x, p71_y, N1_x, N1_y)));
	//produce x--PAR??

	int px = p15_x;
	int py = p15_y;

	//perimeter
	int sp = 0;
	for (int pari = 0; pari < 12; pari++)
		sp = sp
				+ distance(landmarks[pari * 2], landmarks[pari * 2 + 1],
						landmarks[(pari + 1) * 2],
						landmarks[(pari + 1) * 2 + 1]);
	sp = sp
			+ distance(landmarks[12 * 2], landmarks[12 * 2 + 1],
					landmarks[0 * 2], landmarks[0 * 2 + 1]);
	//area
	double parea = 0;
	for (int pari = 0; pari < 12; pari++)
		parea = parea
				+ linesqr(landmarks[pari * 2], landmarks[pari * 2 + 1],
						landmarks[(pari + 1) * 2],
						landmarks[(pari + 1) * 2 + 1]);
	parea = parea
			+ linesqr(landmarks[12 * 2], landmarks[12 * 2 + 1],
					landmarks[0 * 2], landmarks[0 * 2 + 1]);
	//par
	double PAR = sp / parea;
	//produce x--eyesize
	int p35_x = landmarks[(35 - 1) * 2];
	int p35_y = landmarks[(35 - 1) * 2 + 1];

	int p45_x = landmarks[(45 - 1) * 2];
	int p45_y = landmarks[(45 - 1) * 2 + 1];

	int p31_x = landmarks[(31 - 1) * 2];
	int p31_y = landmarks[(31 - 1) * 2 + 1];

	int p41_x = landmarks[(41 - 1) * 2];
	int p41_y = landmarks[(41 - 1) * 2 + 1];
	int p7_x = landmarks[(7 - 1) * 2];
	int p7_y = landmarks[(7 - 1) * 2 + 1];

	double EYESIZE = double(
			distance(p35_x, p35_y, p45_x, p45_y)
					- distance(p31_x, p31_y, p41_x, p41_y)) / double(2);
	//produce a
	double a = p7_y
			- (landmarks[(39 - 1) * 2 + 1] + landmarks[(40 - 1) * 2 + 1]) / 2.0;

	//produce x--LF_FH??

	//produce point P78--the highest point on the face
	double N3_x = (landmarks[(20 - 1) * 2] + landmarks[(21 - 1) * 2]) / 2.0;
	double N3_y = (landmarks[(20 - 1) * 2 + 1] + landmarks[(21 - 1) * 2 + 1])
			/ 2.0;

	double N4_x = (landmarks[(27 - 1) * 2] + landmarks[(28 - 1) * 2]) / 2.0;
	double N4_y = (landmarks[(27 - 1) * 2 + 1] + landmarks[(28 - 1) * 2 + 1])
			/ 2.0;

	double a1 = double(p35_y - N3_y) / double(p35_x - N3_x);
	double a2 = double(p45_y - N4_y) / double(p45_x - N4_x);
	double b1 = N3_y - a1 * N3_x;
	double b2 = p45_y - a2 * p45_x;
	double x0 = double(b2 - b1) / double(a1 - a2);
	double y0 = a1 * x0 + b1;

	double LF_FH = double(a) / double(distance(x0, y0, p7_x, p7_y));
	//produce x--FW_LFH
	double FW_LFW = double(distance(p1_x, p1_y, p15_x, p15_y)) / double(a);

	//produce x--EYEBROW

	double EYEBROW = (distance(landmarks[(19 - 1) * 2],
			landmarks[(19 - 1) * 2 + 1], landmarks[(35 - 1) * 2],
			landmarks[(35 - 1) * 2 + 1])
			+ distance(landmarks[(20 - 1) * 2], landmarks[(20 - 1) * 2 + 1],
					landmarks[(33 - 1) * 2], landmarks[(33 - 1) * 2 + 1])
			+ distance(landmarks[(22 - 1) * 2], landmarks[(22 - 1) * 2 + 1],
					landmarks[(31 - 1) * 2], landmarks[(31 - 1) * 2 + 1])
			+ distance(landmarks[(23 - 1) * 2], landmarks[(23 - 1) * 2 + 1],
					landmarks[(41 - 1) * 2], landmarks[(41 - 1) * 2 + 1])
			+ distance(landmarks[(43 - 1) * 2], landmarks[(43 - 1) * 2 + 1],
					landmarks[(28 - 1) * 2], landmarks[(28 - 1) * 2 + 1])
			+ distance(landmarks[(45 - 1) * 2], landmarks[(45 - 1) * 2 + 1],
					landmarks[(26 - 1) * 2], landmarks[(26 - 1) * 2 + 1]))
			/ 6.0;

	feature[0] = (CJWR - 1.1381) / 0.0067;
	feature[1] = (WHR - 1.8865) / 0.0259;
	feature[2] = (PAR - 0.0372) / 7.6028e-006;
	feature[3] = (EYESIZE - 22.4014) / 2.9949;
	feature[4] = (LF_FH - 0.5964) / 0.0070;
	feature[5] = (FW_LFW - 1.2139) / 0.0067;
	feature[6] = (EYEBROW - 13.7902) / 8.3765;
	//[CJWR, WHR, PAR, EYESIZE, LF_FH, FW_LFH, EYEBROW];
}

//face alignment
IplImage * GeometricalTransform(IplImage * src, float Leye_x, float Leye_y,
		float Reye_x, float Reye_y, float NewLeye_x, float NewLeye_y,
		float NewReye_x, float NewReye_y, CvSize newSize) {

	float scale;
	scale = (float) (NewReye_x - NewLeye_x)
			/ sqrt(
					(Leye_x - Reye_x) * (Leye_x - Reye_x)
							+ (Leye_y - Reye_y) * (Leye_y - Reye_y));
	IplImage *dst = 0;
	//first resize the src image
	CvSize dstSize;
	dstSize.width = (int) src->width * scale;
	dstSize.height = (int) src->height * ((float) dstSize.width / src->width);
	/*if (dstSize.width < newSize.width || dstSize.height < newSize.height)
	 return src;
	 else
	 {*/
	dst = ::cvCreateImage(dstSize, src->depth, src->nChannels);
	cvResize(src, dst, CV_INTER_LINEAR);
	//cvReleaseImage(&src);

	src = NULL;
	src = ::cvCloneImage(dst);
	/*cvNamedWindow ("zoom in", 1);
	 cvShowImage ("zoom in", src);*/
	float angle;
	angle = atan2(Reye_y - Leye_y, Reye_x - Leye_x);
	/*begin image rotation */
	float m[6];
	// Matrix m looks like:
	// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
	// [ m3  m4  m5 ]       [ A21  A22   b2 ]
	CvMat M = cvMat(2, 3, CV_32F, m);
	int w = src->width;
	int h = src->height;
	m[0] = (float) cos(-angle);
	m[1] = (float) sin(-angle);
	m[3] = -m[1];
	m[4] = m[0];
	m[2] = w * 0.5f;
	m[5] = h * 0.5f;
	//  dst(x,y) = A * src(x,y) + b
	cvZero(dst);
	cvGetQuadrangleSubPix(src, dst, &M);
	/*cvNamedWindow("dst",1);
	 cvShowImage ("dst", dst);*/
	/*end image rotation */
	/*get the position of left eye in dst image*/
	float temp_x, temp_y;//denote the position of left eye in resized src image
	float dstLeye_x, dstLeye_y;	  //denote the position of left eye in dst image
	temp_x = Leye_x * scale;
	temp_y = Leye_y * scale;
	float Leyeangle, tempangle;
	Leyeangle = atan2(temp_y - dst->height / 2, temp_x - dst->width / 2);
	tempangle = Leyeangle - angle;
	dstLeye_x = (temp_x - dst->width / 2) * cos(tempangle) / cos(Leyeangle)
			+ dst->width / 2;
	dstLeye_y = (temp_y - dst->height / 2) * sin(tempangle) / sin(Leyeangle)
			+ dst->height / 2;
	/*  printf("the tempx is %f, the tempy is %f",temp_x,temp_y);
	 printf("the x is %f, the y is %f, the angle is %f, the angle of left eye is %f",dstLeye_x,dstLeye_y,angle,Leyeangle);*/
	float dx, dy;
	dx = NewLeye_x - dstLeye_x;
	dy = NewLeye_y - dstLeye_y;
	IplImage * movedst;
	//new
	movedst = cvCreateImage(newSize, src->depth, src->nChannels);
	//new
	/*CvPoint2D32f center;
	 center.x = movedst->width/2 -dx;
	 center.y = movedst->height/2 -dy;
	 cvGetRectSubPix( dst,movedst,center );*/
	m[0] = 1;
	m[1] = 0;
	m[3] = 0;
	m[4] = 1;
	m[2] = movedst->width / 2 - dx;
	m[5] = movedst->height / 2 - dy;
	cvGetQuadrangleSubPix(dst, movedst, &M);
	/*cvNamedWindow("movedst",1);
	 cvShowImage ("movedst", movedst);
	 ::cvWaitKey(0);*/
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return movedst;
	/*}*/
}

int main(int argc, char * argv[]) {

	if (argc != 3) {
		std::cout
				<< " Usage: computeBMI image_path model_path"
				<< std::endl;
		return -1;
	}

	//static const char* path = "../data/testface.jpg";
	static const char* path = argv[1];

	//printf("Path: %s\n",path);

	//cv::Mat_<unsigned char> img(cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE)); //read grayscale image

	cv::Mat img_rgb = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR); // Read the file
	if (!img_rgb.data) {
		printf("Cannot load %s\n", path);
		exit(1);
	}

	double bmifeature[7];
	BMIfunction(bmifeature, img_rgb, argv);

	for (int i = 0; i < 7; i++)
		printf(" %d:%f ",i+1,bmifeature[i]);
	printf("\n");

	return 0;
}

