#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 해리스 코너 검출

int main()
{
    Mat src, gray;
    int thresh = 150;
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;

    src = imread("data/left01.jpg");
    cvtColor(src, gray, COLOR_BGR2GRAY);
    imshow("src", src);

    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros(src.size(), CV_32FC1);

    cornerHarris(gray, dst, blockSize, apertureSize, k);

    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);

    for (int j = 0; j < dst_norm.rows; j++){
        for (int i = 0; i < dst_norm.cols; i++){
            if ((int)dst_norm.at<float>(j, i) > thresh)
                circle(src, Point(i, j), 5, Scalar(0, 0, 255), 2, 8, 0);
        }
    }
    imshow("corners_window", src);
    waitKey();
    return 0;
}
