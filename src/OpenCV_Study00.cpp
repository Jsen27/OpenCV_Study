#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 이미지 출력하기
int main()
{
	Mat image;
	image = imread("E:image.jpg", IMREAD_COLOR);

	if (image.empty()) {cout << "error" << endl;  return -1; }
	imshow("출력 영상", image);
	return 0;
}
