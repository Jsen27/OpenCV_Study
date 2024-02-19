#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// Mat 객체를 난수로 초기화

int main()
{
	Mat R = Mat(3, 6, CV_8UC1);
	randu(R, Scalar::all(0), Scalar::all(255));
	cout << "R = " << endl << R << endl;
	return 0;
}
