#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 연결 성분 레이블링

int main()
{
    Mat img, img_edge, labels, centroids, img_color, stats;
    img = imread("data/smarties.png", IMREAD_GRAYSCALE);
    imshow("before", img);

    threshold(img, img_edge, 200, 255, THRESH_BINARY_INV);
    imshow("Image after threshold", img_edge);

    int n = connectedComponentsWithStats(img_edge, labels, stats, centroids);

    vector<Vec3b> colors(n + 1);
    colors[0] = Vec3b(0, 0, 0);
    for (int i = 1; i <= n; i++)
        colors[i] = Vec3b(rand() % 256, rand() % 256, rand() % 256);
    img_color = Mat::zeros(img.size(), CV_8UC3);
    for (int y = 0; y < img_color.rows; y++){
        for (int x = 0; x < img_color.cols; x++){
            int label = labels.at<int>(y, x);
            img_color.at<Vec3b>(y, x) = colors[label];
        }
    }

    imshow("Labeled map", img_color);
    waitKey();

    return 0;
}
