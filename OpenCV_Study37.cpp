#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 히스토그램 전경과 배경 분리

int main()
{
	Mat src, dst;

	src = imread("E:image.jpg", IMREAD_GRAYSCALE);
	imshow("Image", src);
	if (!src.data)
		return -1;
	
	Mat threshold_image;
	threshold(src, threshold_image, 100, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("Thresholded", threshold_image);

	waitKey();
	return 0;
}
