#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 현재 프레임의 모든 화소에 파란색을 더한다

int main()
{
	VideoCapture cap("E:trailer.mp4");
	if (!cap.isOpened())
		return -1;
	
	namedWindow("frame", 1);
	while(true){
		Mat frame;
		cap >> frame;
		frame += Scalar 100, 0, 0; // 현재 프레임의 모든 화소에 파란색을 더한다.
		imshow("frame", frame);
		if (waitKey(30) >= 0) 
			5break;
	}
	
	return 0;
}
