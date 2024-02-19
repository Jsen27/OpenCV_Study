#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 컬러 매핑

int main()
{
	Mat img = imread("E:lenna.jpg");
	Mat img_color;
	applyColorMap(img, img_color, COLORMAP_HOT);
	imshow("img_color", img_color);
	waitKey();
	return 0;
}
