#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 컬러를 이용한 객체 추적

int main()
{
	VideoCapture cap("E:tennis_ball.mp4");
	if (!cap.isOpened()) return -1;
	while(true){
		Mat imgHSV;
		Mat frame;
		cap >> frame;
		cvtColor(frame, imgHSV, COLOR_BGR2HSV);

		Mat imgThresholded;
		inRange(imgHSV, Scalar(30, 10, 10), Scalar(38, 255, 255), imgThresholded);
		imshow("frame", frame);
		imshow("dst", imgThresholded);
		if (waitKey(30) >= 0) break;
	}

	waitKey();
	return 0;
}
