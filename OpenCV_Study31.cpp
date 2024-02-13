#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 선형 영상 합성

int main()
{
	double alpha = 0.5; double beta; double input;
	Mat src1, src2, dst;

	cout << "alpha[0.0-1.0]: ";
	cin >> input;

	src1 = imread("E:image.jpg");
	src2 = imread("E:lenna.jpg");
	if (src1.empty() || src2.empty()) { cout << "error" << endl; return -1; }

	resize(src1, src1, src2.size());

	beta = 1.0 - alpha;
	addWeighted(src1, alpha, src2, beta, 0.0, dst);

	imshow("Original Image1", src1);
	imshow("Original Image2", src2);
	imshow("New Image", dst);

	waitKey();
	return 0;
}
