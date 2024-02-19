#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) { cout << "error" << endl; return -1; }

	Mat dst;
	equalizeHist(src, dst);

	imshow("Image", src);
	imshow("Equalized", dst);

	waitKey();
	return 0;
}
