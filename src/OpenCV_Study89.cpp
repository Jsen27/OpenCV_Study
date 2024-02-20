#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/trace.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace cv;
using namespace cv::dnn;
using namespace std;

// Caffe 영상 인식

// 영상에 대하여 최적의 클래스를 찾는다
static void getMaxClass(const Mat &probBlob, int *classId, double *classProb)
{
    Mat probMat = probBlob.reshape(1, 1); // 영상을 1X1000 행렬로 바꾼다
    Point classNumber;
    minMaxLoc(probMat, NULL, classProb, NULL, &classNumber);
    *classId = classNumber.x;
}

static vector<String> readClassNames(const char *filename = "data/synset_words.txt")
{
    vector<String> classNames;
    ifstream fp(filename);
    if (!fp.is_open()){
        cerr << "클래스 레이블이 들어 있는 파일이 없음" << filename << endl;
        exit(-1);
    }
    string name;
    while (!fp.eof()){
        getline(fp, name);
        if (name.length())
            classNames.push_back(name.substr(name.find(' ') + 1));
    }
    fp.close();
    return classNames;
}

int main()
{
    CV_TRACE_FUNCTION();
    String modelTxt = "data/bvlc_googlenet.prototxt";
    String modelBin = "data/bvlc_googlenet.caffemodel";
    String imageFile = "data/space_shuttle.jpg";
    Net net = dnn::readNetFromCaffe(modelTxt, modelBin);
    if (net.empty())
        exit(-1);
    Mat img = imread(imageFile);
    if (img.empty()){
        cerr << "입력 영상을 읽을 수 없음" << imageFile << endl;
        exit(-1);
    }
    // GoogleNet은 224x224 크기의 RGB영상만 인식할 수 있음
    Mat inputBlob = blobFromImage(img, 1, Size(224, 224), Scalar(104, 117, 123)); // 영상에서 일부를 추출
    Mat prob;
    TickMeter t;
    for (int i = 0; i < 10; i++){
        CV_TRACE_REGION("forward");
        net.setInput(inputBlob, "data"); // 신경회로망의 입력 설정
        t.start();
        prob = net.forward("prob");
        t.stop();
    }
    int classId;
    double classProb;
    getMaxClass(prob, &classId, &classProb); // 최적의 클래스를 찾는다
    vector<String> classNames = readClassNames();
    cout << "최적의 클래스: #" << classId << " '" << classNames.at(classId) << "'" << endl;
    cout << "확률: " << classProb * 100 << "%" << endl;
    cout << "소요시간: " << (double)t.getTimeMilli() / t.getCounter() <<
        " ms (average from " << t.getCounter() << " iterations)" << endl;
    return 0;
}
