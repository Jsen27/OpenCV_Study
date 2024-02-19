#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// at함수를 이용하여 밝기 조정

int main()
{
	Mat img = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	imshow("image", img);
	
	for(int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			img.at<uchar>(i, j) = saturate_cast<uchar>(img.at<uchar>(i, j) + 30);

	imshow("new image", img);
	waitKey();
	return 0;
}
