#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 명시적으로 만든 Mat 객체 표시

int main()
{
	Mat M(600, 800, CV_8UC3, Scalar(0, 255, 0));
	if (M.empty()) { cout << "error" << endl; return -1; }
	imshow("img", M);
	
	waitKey();
	return 0;
}
