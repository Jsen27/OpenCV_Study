#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 키보드 이벤트 처리

int main()
{
	Mat src = imread("E:image.jpg", IMREAD_COLOR);
	if (src.empty()) { cout << "error" << endl; return -1; }
	imshow("src", src);
	
	int x = 50;
	int y = 50;
	
	while(true){
		int key = waitKey(100);
		if (key == 'q') break;
		else if (key == 'a')
			x -= 10;
		else if (key == 'w')
			y -= 10;
		else if (key == 'd')
			x += 10;
		else if (key == 's')
			y += 10;
		circle(img, Point(x, y), 50, Scalar(0, 255, 0), 5);
		imshow("img", img);
	}
	
	return 0;
}
