#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// convertTo() 함수를 이용한 밝기 조정

int main()
{
	Mat img = imread("E:lenna.jpg");
	imshow("Original image", img);
	
	Mat oimage;
	img.convertTo(oimage, -1, 1, 30);

	imshow("New image", oimage);
	waitKey();
	return 0;
}
