#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 특정한 행 떼어내기

int main()
{
	Mat A = imread("E:image.jpg");
	Mat Row = A.row(1);
	cout << "Row = " << endl << Row << endl;
	
	return 0;
}
