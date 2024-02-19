#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 적응적 이진화

int main()
{
    Mat src = imread("chroma.jpg", IMREAD_GRAYSCALE);
    Mat img, th1, th2, th3, th4;
    medianBlur(src, img, 5);
    threshold(img, th1, 127, 255, THRESH_BINARY);
    adaptiveThreshold(img, th2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2);
    adaptiveThreshold(img, th3, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);
    
    imshow("Original", src);
    imshow("Global Thresholding", th1);
    imshow("Adaptive Mean", th2);
    imshow("Adaptive Gaussian", th3);

    waitKey();
    return 0;
}
