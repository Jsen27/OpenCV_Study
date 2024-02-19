#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 컬러를 이용한 객체 분할

int main()
{
	Mat img = imread("E:chroma.jpg");
	if (img.empty()) return -1;

	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	Mat imgThresholded;
	inRange(imgHSV, Scalar(100, 0, 0), Scalar(120, 255, 255), imgThresholded);

	imshow("Original", img);
	imshow("Threshold", imgThresholded);

	waitKey();
	return 0;
}
