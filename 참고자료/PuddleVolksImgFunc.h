#pragma once
#include "stdafx.h"

#include <math.h>

// Configuration
#define SCALE_DISPIMG	1.0f
#define SCALE_CONVERT	255
#define MARGIN_OBJECT	10
#define SIZE_HIST		256

// Parameters
#define TH_MAX_EDGE		0.8
#define TH_MIN_EDGE		0.4
#define SIZE_SUM_KERNEL 5
#define SIZE_MAX_KERNEL 9
#define TH_MIN_EDGESUM	18

#define CLIP(a,b,c)			(a<b?b:a>c?c:a)
//#define MAX(a,b)			(a>b?a:b)
//#define MIN(a,b)			(a<b?a:b)
#define INOUT(a,x,o)		(a<(x-o)?0:a>(x+o)?0:1)

#define PI				3.14159265359

/// Structures
enum E_SOBEL_DIR
{
	SOBEL_HOR = 0,
	SOBEL_VER,
	SOBEL_DIAG,
	SOBEL_ADIAG,
};

enum E_GETROI_RETURN_IMG
{
	RETURN_SRC = 0,
	RETURN_EDGE,
	RETURN_EDGE_BIN,
	RETURN_SUM,
	RETURN_SUM_BIN,
};

enum E_COLOR
{
	COLOR_B = 0,
	COLOR_G,
	COLOR_R,
	COLOR_NUM,
};

/// Functions
void dispImage(Mat src, String name_window, float scale);
void matScaleFloat(Mat src, float scale);
Mat matSobelOperation(Mat src, E_SOBEL_DIR dir);
cv::Rect getObjectRect(Mat src_bin, int margin);
cv::Rect fgetObjectRect(Mat src_bin,Mat src_ref, int margin);
cv::Rect VW310fgetObjectRect(Mat src_bin, Mat src_ref, int margin);
cv::Rect getObjImg(Mat src, int x, int y, int w, int h, int th);

cv::Rect VW276PAgetObjectRect(Mat src_bin, int margin);


float getROiEdgeData(cv::Mat edge_data);
int getROiEdgeData(cv::Mat edge_data,int x);

cv::Rect fgetObjectRect_test(Mat src_bin, Mat src_ref, int margin);

Mat maxFilter(Mat src, int size_kernel);
Mat fabsMat(Mat src);
float fmeanMat(Mat src);
Mat getROIImageFromEdge(Mat src, cv::Rect* roi_rect, E_GETROI_RETURN_IMG type_img, int size_kernel = SIZE_SUM_KERNEL, float th_edge = TH_MIN_EDGE, int th_edgesum = TH_MIN_EDGESUM);
Mat convertAbsNorm(Mat fsrc, int type);
Mat drawKeypoint(Mat src, vector<KeyPoint> keypoints, Scalar color = Scalar(0,0,255));
void getHist(Mat src, Mat* r_hist, Mat* g_hist, Mat* b_hist, int cut_low_hist);
vector<float> getMeanRGB(Mat src);
float calcSADMat(Mat src1, Mat src2);
float calcSSDMat(Mat src1, Mat src2);
float calcCorrMat(Mat src1, Mat src2);
float calcNCCMat(Mat src1, Mat src2);
float calcCorrMat(Mat src1, Mat src2, Scalar mean_src1);
float calcNCCMat(Mat src1, Mat src2, Scalar mean_src1, Scalar stdv_src1);
float calcNSSDMat(Mat src1, Mat src2);
Mat avrFrameImg(vector<Mat> src);
Mat sharpImage(Mat src, int size_kernel = 3);Mat getEdgeMag(Mat src);
float gauss(float x, float sigma, bool norm);
float gauss2d(float x, float y, float sigma_x, float sigma_y, bool norm);
int countThreshold(Mat src, float thLow, float thHigh);
float intpBilinear(cv::Point p, cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4, float v1, float v2, float v3, float v4);
