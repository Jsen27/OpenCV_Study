#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 침식 연산

int main()
{
	Mat src, dst, erosion_dst, dilation_dst;
	src = imread("E:test.png", IMREAD_GRAYSCALE);

	threshold(src, dst, 127, 255, THRESH_BINARY);
	imshow("dst", dst);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));

	erode(dst, erosion_dst, element);
	imshow("Erosion Demo", erosion_dst);
	waitKey();
	return 0;
}
