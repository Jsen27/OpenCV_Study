#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 영상 회전

int main()
{
	Mat src = imread("E:lenna.jpg");
	Mat dst = Mat();
	Size dsize = Size(src.cols, src.rows);

	Point center = Point(src.cols / 2, src.rows / 2);
	Mat M = getRotationMatrix2D(center, 45, 1.0);
	warpAffine(src, dst, M, dsize, INTER_LINEAR);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	return 0;
}
