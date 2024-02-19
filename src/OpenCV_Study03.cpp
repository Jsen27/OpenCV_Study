#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 마우스 이벤트 처리

void onMouse(int event, int x, int y, int flags, void* param)
{
	if (event == EVENT_LBUTTONDOWN){
		Mat& img = *(Mat*)param;
		circle(img, Point(x, y), 50, Scalar(0, 255, 0), 10);
		putText(img, "Hi", Point(x, y + 70), FONT_HERSHEY_PLAIN, 2.0, 255, 2);
		imshow("src", src);
	}
}

int main()
{
	Mat src = imread("E:image.jpg", IMREAD_COLOR);
	if (src.empty()) { cout << "error" << endl; return -1; }
	imshow("src", src);
	
	setMouseCallback("src", onMouse, &src);
	waitKey(0);
	
	return 0;
}
