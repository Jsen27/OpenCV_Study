#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 히스토그램 스트레칭

int stretch(int x, int r1, int s1, int r2, int s2)
{
	float result;
	if (0 <= x && x <= r1)
		result = s1 / r1 * x;
	else if (r1 < x && x <= r2)
		result = ((s2 - s1) / (r2 - r1)) * (x - r1) + s1;
	else if (r2 < x && x <= 255)
		result = ((255 - s2) / (255 - r2)) * (x - r2) + s2;
	return (int)result;
}

int main()
{
	Mat image = imread("E:lenna.jpg");
	Mat new_image = image.clone();

	int r1, s1, r2, s2;
	cout << "r1: "; cin >> r1;
	cout << "r2: "; cin >> r2;
	cout << "s1: "; cin >> s1;
	cout << "s2: "; cin >> s2;
	
	for (int y = 0; y < image.rows; y++)
		for (int x = 0; x < image.cols; x++)
			for(int c = 0; c < 3; c++){
				int output = stretch(image.at<Vec3b>(y, x)[c], r1, s1, r2, s2);
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(output);
			}
	imshow("Input Image", image);
	imshow("Output Image", new_image);

	waitKey();
	return 0;
}
