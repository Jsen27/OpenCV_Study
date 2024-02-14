#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 밀림 변환

int main()
{
	Mat src = imread("E:lenna.jpg");
	Mat dst = Mat();
	Size dsize = Size(src.cols, src.rows);

	Mat M(2, 3, CV_32F);

	M.at<float>(0, 0) = 1;
	M.at<float>(0, 1) = 0.1;
	M.at<float>(0, 2) = 0;

	M.at<float>(1, 0) = 0;
	M.at<float>(1, 1) = 1;
	M.at<float>(1, 2) = 0;

	warpAffine(src, dst, M, dsize, INTER_LINEAR);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	return 0;
}
