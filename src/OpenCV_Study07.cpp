#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 트랙바로 RGB 조절

int main()
{
	
	img = imread("E:image.jpg");
	if (img.empty()) { cout << "error" << emdl; return -1; }
	
	namedWindow("img", 1);
	imshow("img", img);
	setMouseCallback("img", drawCircle);
	createTrackback("R", "img", &red, 255, on_trackbar);
	createTrackback("G", "img", &green, 255, on_trackbar);
	createTrackback("B", "img", &blue, 255, on_trackbar);
	waitKey(0);
	
	return 0;
}
