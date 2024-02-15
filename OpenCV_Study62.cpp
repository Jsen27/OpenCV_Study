#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// BGR -> HSV

int main()
{
	Mat image, hsv, dst;
	image = imread("E:lenna.jpg");
	cvtColor(image, hsv, COLOR_BGR2HSV);

	Mat array[3];
	split(image, array);
	imshow("image", image);
	imshow("hue", array[0]);
	imshow("saturation", array[1]);
	imshow("value", array[2]);

	waitKey();
	return 0;
}
