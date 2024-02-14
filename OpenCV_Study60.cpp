#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 골격화

int main()
{
	Mat img = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	threshold(img, img, 127, 255, THRESH_BINARY);

	imshow("src", img);

	Mat skel(img.size(), CV_8UC1, Scalar(0));
	Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
	Mat temp, eroded;

	do{
		erode(img, eroded, element);
		dilate(eroded, temp, element);
		subtract(img, temp, temp);
		bitwise_or(skel, temp, skel);
		eroded.copyTo(img);
	} while ((countNonZero(img) != 0));

	imshow("result", skel);
	waitKey();
	return 0;
}
