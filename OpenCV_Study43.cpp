#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Laplacian() 에지 검출

int main()
{
	Mat src, src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	src = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) return -1;

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Mat abs_dst;
	Laplacian(src, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);

	imshow("Image", src);
	imshow("Laplacian", abs_dst);
	
	waitKey();
	return 0;
}
