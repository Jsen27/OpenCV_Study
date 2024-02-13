#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 감마 보정

int main()
{
	Mat src1, dst;
	double gamma = 0.5;

	src1 = imread("E:lenna.jpg");
	if (src1.empty()) { cout << "error" << endl; return -1; }

	Mat table(1, 256, CV_8U);
	uchar *p = table.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(pow(i / 255, gamma) * 255);
	
	LUT(src1, table, dst);
	imshow("src1", src1);
	imshow("dst", dst);
	
	waitKey();
	return 0;
}
