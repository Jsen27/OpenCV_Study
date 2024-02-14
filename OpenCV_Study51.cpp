#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// << 연산자를 이용항 평행이동

int main()
{
	Mat src = imread("E:lenna.jpg");
	Mat dst = Mat();

	int tx = 100;
	int ty = 20;

	Mat tmat = (Mat_<double>(2, 3) << 1, 0, tx, 0, 1, ty);
	warpAffine(src, dst, tmat, src.size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	return 0;
}
