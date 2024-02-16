#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 트랙바를 이용한 임계값 변경

int threshold_value = 128;
int threshold_type = 0;
const int max_value = 255;
const int max_binary_value = 255;
Mat src, src_gray, dst;

static void MyThreshold(int, void*)
{
    threshold(src, dst, threshold_value, max_binary_value, threshold_type);
    imshow("result", dst);
}

int main()
{
    src = imread("lenna.jpg", IMREAD_GRAYSCALE);
    namedWindow("result", WINDOW_AUTOSIZE);
    createTrackbar("임계값", "result", &threshold_value, max_value, MyThreshold, NULL);
    MyThreshold(0, 0);
    waitKey();
    return 0;
}
