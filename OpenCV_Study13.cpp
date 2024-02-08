#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 얕은 복사와 깊은 복사 테스트

int main()
{
	Mat A = imread("E:image.jpg");
	Mat B = A;
	imshow("window 1", A);
	
	flip(B, B, 0);
	cout << "B만 반사시킴" << endl;
	imshow("window 2", A);
	
	waitKey();

	return 0;
}
