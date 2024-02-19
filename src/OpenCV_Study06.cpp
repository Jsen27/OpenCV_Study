#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 마우스로 페인트 브러쉬

Mat img;
int drawing = false;

void drawCircle(int event, int x, int y, int, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN) // 마우스를 누르면
		drawing = true;
	else if (event == CV_EVENT_MOVE) { // 마우스를 웁직이면
		if (drawing == true)
			circle(img, Point(x, y), 3, Scalar(0, 0, 255), 10);
	} else if (event == CV_EVENT_LBUTTONUP) // 마우스 떼면
		drawing = false;
	imshow("Image", img);
}

int main()
{
	
	img = imread("E:image.jpg");
	if (img.empty()) { cout << "error" << emdl; return -1; }
	
	imshow("Image", img);
	setMouseCallback("Image", drawCircle);
	waitKey(0);
	imwrite("E:image22.jpg", img);
	
	
	return 0;
}
