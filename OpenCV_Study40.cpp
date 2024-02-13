#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 가우시안 스무딩

int main()
{
	Mat image = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	Mat dst;
	imshow("image", image);

	for (int i = 1; i < 61; i = i + 2){
		GaussianBlur(image, dst, Size(i, i), 0, 0);
		imshow("Gaussian filter", image);
		waitKey(1000);
	}

	waitKey();
	return 0;
}
