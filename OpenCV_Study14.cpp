#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 관심 영역 지정하기

int main()
{
	Mat A = imread("E:image.jpg");
	Rect r(10, 10, 100, 100);
	Mat D = A(r); // 사각형을 이용하여 관심 영역을 지정
	D = Scalar(0, 0, 0); //관심 영역의 모든 화소 0,0,0
	imshow("src", A);
	
	waitKey();
	return 0;
}
