#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 색상 채널 분리

int main()
{
	Mat image;
	image = imread("E:lenna.jpg");

	Mat bgr[3];
	split(image, bgr);

	imshow("image", image);
	imshow("blue", bgr[0]);
	imshow("green", bgr[1]);
	imshow("red", bgr[2]);

	waitKey();
	return 0;
}
