#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// AND, OR 예제

int main()
{
	Mat img1 = Mat::zeros(Size(400, 200), CV_8UC1);
	Mat img2 = Mat::zeros(Size(400, 200), CV_8UC1);
	
	Mat t1 = img1(Range(20, 180), Range(50, 200));
	t1 = 255;
	imshow("img1", img1);
	Mat t2 = img2(Range(100, 150), Range(150, 350));
	t2 = 255;
	imshow("img2", img2);

	Mat result;
	bitwise_and(img1, img2, result);
	imshow("AND", result);
	bitwise_or(img1, img2, result);
	imshow("OR", result);

	waitKey();
	return 0;
}
