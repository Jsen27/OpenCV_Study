#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// blur() 함수를 이용한 블러처리

int main()
{
	Mat image = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	Mat dst;

	blur(image, dst, Size(11, 11));
	imshow("source", image);
	imshow("result", dst);

	waitKey();
	return 0;
}
