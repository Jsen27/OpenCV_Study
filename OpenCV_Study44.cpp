#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Canny() 에지 검출

Mat src, src_gray;
Mat dst, detected_edges;
int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio2 = 3;
int kernel_size = 3;

static void CannyThreshold(int, void*)
{
	blur(src, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, lowThreshold,
		lowThreshold * ratio2, kernel_size);
	
	dst = Scalar::all(0);
	src.copyTo(dst, detected_edges);
	imshow("Image", src);
	imshow("Canny", dst);
}

int main()
{
	src = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) return -1;
	dst.create(src.size(), src.type());
	namedWindow("Canny", WINDOW_AUTOSIZE);
	createTrackbar("Min Threshold:", "Canny", &lowThreshold,
		max_lowThreshold, CannyThreshold);
	CannyThreshold(0, 0);
	waitKey();
	return 0;
}
