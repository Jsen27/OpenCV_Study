#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 영상 두개 붙이기

int main()
{
	Mat img1 = imread("E:image.jpg");
	Mat img2 = imread("E:image.jpg");
	imshow("Original Image", img1);

	img1.push_back(img2);
	imshow("New Image", img1);
	waitKey();
	return 0;
}
