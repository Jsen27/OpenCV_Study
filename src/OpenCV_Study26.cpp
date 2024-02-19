#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 이진화

int main()
{
	Mat image = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	Mat dst;
	int threshold_value = 127;
	threshold(image, dst, threshold_value, 255, THRESH_BINARY); // 이진화
	imshow("Original Image", image);
	imshow("New Image", dst);
	
	waitKey();
	return 0;
}
