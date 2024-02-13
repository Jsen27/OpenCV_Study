#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 영상 합성

int main()
{
	Mat src1 = imread("E:image.jps");
	Mat src2 = imread("E:lenna.jpg");
	Mat dst;
	dst = src1 + src2;
	imshow("Original Image1", src1);
	imshow("Original Image2", src2);
	imshow("New Image", dst);

	
	waitKey();
	return 0;
}
