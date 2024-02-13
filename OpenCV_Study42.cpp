#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Sobel() 에지 검출

int main()
{
	Mat src;
	Mat grad;
	int scale = 1;
	int delta = 0;
	src = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) { cout << "error" << endl; return -1; }

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	Sobel(src, grad_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	Sobel(src, grad_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);

	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	imshow("Image", src);
	imshow("Sobel", grad);
	
	waitKey();
	return 0;
}
