#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 트랙바를 이용한 이진화

Mat src, src_gray, dst;
int threshold_value = 0;
int threshold_type = 0;

void Threshold_Demo(int, void*)
{
	threshold(src_gray, dst, threshold_value, 255, threshold_type);
	imshow("결과 영상", dst);
}

int main()
{
	src = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow("결과 영상", WINDOW_AUTOSIZE);

	createTrackbar("임계값", "결과 영상",
	&threshold_value, 255, Threshold_Demo);

	Threshold_Demo(0, 0);

	while(true){ // ESC 키가 입력되면 종료
		int c;
		c = waitKey(20);
		if ((char)c == 27)
			break;
	}
	return 0;
}
