#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
// 방향키보드로 밝기 조절
int main()
{
	
	Mat src = imread("E:image.jpg", IMREAD_COLOR);
	if (src.empty()) { cout << "error" << emdl; return -1; }
	
	imshow("src", srd);
	
	while(true){
		int key = waitKeyEx(); // 사용자 키를 기다린다.
		cout << key << ' ';
		if (key == 'q')
			break;
		else if (key == 2424832)
			src -= 50; // 영상이 어두워진다
		else if (key == 2555904)
			src += 50; // 영상이 밝아진다
		imshow("src", src);
		
	}
	
	
	return 0;
}
