#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 히스토그램 그리기

void drawHist(int histogram[])
{
	int hist_w = 512; // 히스토그램 영상의 폭
	int hist_h = 400; // 히스토그램 영상의 높이
	int bin_w = cvRound((double)hist_w / 256); // 빈의 폭

	// 히스토그램이 그려지는 영상(컬러)
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	// 히스토그램에서 최대값을 찾는다.
	int max = histogram[0];
	for (int i = 0; i < 256; i++){
		if (max < histogram[i])
			max = histogram[i];
	}

	// 히스토그램 배열을 최대값으로 정규화
	for (int i = 0; i < 256; i++){
		histogram[i] = floor(((double)histogram[i] / max) * histImage.rows);
	}

	// 히스토그램의 값을 빨간색 막대로 그림
	for (int i = 0; i < 256; i++){
		line(histImage, Point(bin_w * i, hist_h), 
			Point(bin_w * i, hist_h - histogram[i]),
			Scalar(0, 0, 255));
	}
	imshow("histogram", histImage);
}

int main()
{
	Mat src = imread("E:lenna.jpg", IMREAD_GRAYSCALE);
	imshow("Input Image", src);
	int histogram[256] = {0};

	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			histogram[(int)src.at<uchar>(y, x)]++;

	drawHist(histogram);
	waitKey();
	return 0;
}
