#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 컨볼루션

int main()
{
	Mat image = imread("E:lenna.jpg", IMREAD_GRAYSCALE);

	float weights[] = {
		1 / 9.0f, 1 / 9.0f, 1 / 9.0f,
		1 / 9.0f, 1 / 9.0f, 1 / 9.0f,
		1 / 9.0f, 1 / 9.0f, 1 / 9.0f
	};

	Mat mask(3, 3, CV_32F, weights);
	Mat blur;
	filter2D(image, blur, -1, mask);
	blur.convertTo(blur, CV_8U);
	imshow("image", image);
	imshow("blur", blur);

	waitKey();
	return 0;
}
