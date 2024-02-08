#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 이미지 흑백으로 만들어 다른 이름으로 저장
int main()
{
	Mat src;
	src = imread("E:image.jpg", IMREAD_COLOR);

	if (src.empty()) {cout << "error" << endl;  return -1; }
	imshow("src", src);
	Mat gray, edge, output;
	cvtColor(src, gray, CV_BGR2GRAY);
	
	imshow("gray", gray);
	imwrite("E:gray.jpg", gray);
	waitKey(0);
	
	return 0;
}
