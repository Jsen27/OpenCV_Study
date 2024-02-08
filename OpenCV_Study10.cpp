#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 화소값 출력

int main()
{
	Mat img = imread("E:image.jpg");
	if (img.empty()) { cout << "error" << endl; return -1; }
	imshow("img", img);
	
	cout << img << endl;
	waitKey();
	
	return 0;
}
