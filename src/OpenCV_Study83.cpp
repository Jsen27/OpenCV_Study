#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

// kNN 숫자인식

int main()
{
    Mat img;
    img = imread("data/digits.png", IMREAD_GRAYSCALE);
    namedWindow("original", WINDOW_AUTOSIZE);
    imshow("original", img);
    waitKey();

    Mat train_features(5000, 400, CV_32FC1);
    Mat labels(5000, 1, CV_32FC1);

    // 각 숫자 영상을 행 벡터로 만들어서 train_feature에 저장
    for (int r = 0; r < 50; r++){
        for (int c = 0; c < 100; c++){
            int i = 0;
            for (int y = 0; y < 20; y++){
                for (int x = 0; x < 20; x++){
                    train_features.at<float>(r * 100 + c, i++) = img.at<uchar>(r * 20 + y, c * 20 + x);
                }
            }
        }
    }

    // 각 숫자 영상에 대한 레이블 저장
    for (int i = 0; i < 5000; i++)
        labels.at<float>(i, 0) = i / 500;

    // 학습 과정
    Ptr<ml::KNearest> knn = ml::KNearest::create();
    Ptr<ml::TrainData> trainData = ml::TrainData::create(train_features, ROW_SAMPLE, labels);

    knn->train(trainData);

    // 테스트 과정
    Mat predictedLabels;
    for (int i = 0; i < 5000; i++){
        Mat test = train_features.row(i);
        knn->findNearest(test, 3, predictedLabels);
        float prediction = predictedLabels.at<float>(0);
        cout << "테스트 샘플" << i << "의 라벨" << prediction << '\n';
    }
    

    return 0;
}
