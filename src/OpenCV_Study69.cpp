#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// dft 역 변환 idft()

int main()
{
	Mat img = imread("lenna.jpg", IMREAD_GRAYSCALE);

	Mat img_float, dft1, inversedft, inversedft1;
	img.convertTo(img_float, CV_32F);
	dft(img_float, dft1, DFT_COMPLEX_OUTPUT);

	// 역변환을 수행
	idft(dft1, inversedft, DFT_SCALE | DFT_REAL_OUTPUT);

	inversedft.convertTo(inversedft1, CV_8U);
	imshow("invertedft", inversedft1);

	imshow("original", img);
	waitKey();
	return 0;
}
