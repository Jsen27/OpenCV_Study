#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 함수 정의를 이용한 밝기 조정

void brighten(Mat& img, int value)
{
	for (int r = 0; r < img.rows; r++)
		for (int c = 0; c < img.cols; c++)
			img.at<uchar>(r, c) = saturate_cast<uchar>(img.at<uchar>(r, c) + value);
}

int main()
{
	Mat img = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	imshow("Original image", img);
	
	brighten(img, 30);

	imshow("New image", img);
	waitKey();
	return 0;
}
