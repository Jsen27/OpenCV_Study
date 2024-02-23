#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("data/building.jpg", IMREAD_GRAYSCALE);
	if (src.empty()){
		cerr << "Image load failed" << endl;
		return -1;
	}

	Mat harris;
	cornerHarris(src, harris, 3, 3, 0.04);

	cout << harris;

	return 0;
}