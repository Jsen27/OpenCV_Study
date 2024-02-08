#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 영상의 일부를 숫자로 출력

int main()
{
	Mat img = imread("E:image.jpg");
	imshow("img", img);
	Mat roi(img, Rect(10, 10, 2, 2));
	
	cout << "행의 수 = " << roi.rows << endl;
	cout << "열의 수 = " << roi.cols << endl;
	cout << "roi = " << endl << roi << endl;
	waitKey();
	return 0;
}
