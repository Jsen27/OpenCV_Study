#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// resize() 를 이용한 크기 조절

int main()
{
	Mat src = imread("E:lenna.jpg");
	Mat dst = Mat();

	resize(src, dst, Size(), 2.0, 2.0);

	imshow("Image", src);
	imshow("Scaled", dst);

	waitKey();
	return 0;
}
