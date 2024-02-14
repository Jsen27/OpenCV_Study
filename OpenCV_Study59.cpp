#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 형태학적 그라디언트

int main()
{
	Mat src, dst, open, close;
	src = imread("E:lenna.jpg", IMREAD_GRAYSCALE);

	imshow("src", src);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(src, open, MORPH_GRADIENT, element);
	imshow("Gradient Demo", open);	
	waitKey();
	return 0;
}
