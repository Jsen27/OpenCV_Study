#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 직선, 원, 사각형 출력
int main()
{
	// 검정색으로 초기화 된 600x400 크기의 검정색 영상 생성
	Mat image = Mat(400, 600, CV_8UC3, Scalar(0, 0, 0,));
	
	line(image, Point(100, 100), Point(300, 300), Scalar(0, 0, 255), 7); // 선 그리기
	rectangle(image, Point(250, 30), Point(450, 200), Scalar(0, 255, 0), 5); // 사각형 그리기
	circle(image, Point(100, 300), 60, Scalar(255, 0, 0), 3); // 원 그리기
	ecllipse(image, Point(300, 350), Point(100, 60), 45, 130, 270, Scalar(255, 255, 255), 5); // 타원 그리기
	
	imshow("image", image);
	waitKey(0);
	
	return 0;
}
