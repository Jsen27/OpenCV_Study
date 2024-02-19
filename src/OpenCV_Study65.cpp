#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 영상 배경 합성

int main()
{
	Mat img = imread("E:chroma.jpg");
	Mat img2 = imread("E:beach.png");

	Mat converted;
	cvtColor(img, converted, COLOR_BGR2HSV);
	Mat greenScreen = converted.clone();
	inRange(converted, Scalar(60-10, 100, 100), Scalar(60+10, 255, 255), greenScreen);

	Mat dst, dst1, inverted;
	bitwise_not(greenScreen, inverted);
	bitwise_and(img, img, dst, inverted);
	bitwise_or(dst, img2, dst1, greenScreen);
	bitwise_or(dst, dst1, dst1);

	imshow("img", img);
	imshow("green", greenScreen);
	imshow("dst", dst);
	imshow("dst1", dst1);

	waitKey();
	return 0;
}
