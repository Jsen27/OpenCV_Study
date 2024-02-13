#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 로고 삽입하기

int main()
{
	Mat A = imread("E:lenna.jpg");
	Mat B = imread("E:image.jpg");
	Mat roi(A, Rect(A.cols - B.cols, A.rows - B.rows, B.cols, B.rows));
	B.copyTo(roi);
	
	imshow("img", A);
	waitKey();
	return 0;
}
