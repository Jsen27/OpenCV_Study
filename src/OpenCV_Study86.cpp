#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace ml;

// XOR 학습

int main()
{
    const int hiddenLayerSize = 4;
    float trainingInput[4][2] = {
        { 0.0, 0.0 }, 
        { 0.0, 1.0 },
        { 1.0, 0.0 }, 
        { 1.0, 1.0 }
    };
    Mat trainingInputData = Mat(4, 2, CV_32F, trainingInput);

    float trainingOutput[4][1] = {
        { 0.0 },
        { 1.0 },
        { 1.0 },
        { 0.0 }
    };
    Mat trainingOutputData = Mat(4, 1, CV_32F, trainingOutput);
    
    Ptr<ANN_MLP> mlp = ANN_MLP::create();

    Mat layersSize = Mat(3, 1, CV_16U);
    layersSize.row(0) = Scalar(trainingInputData.cols);
    layersSize.row(1) = Scalar(hiddenLayerSize);
    layersSize.row(2) = Scalar(trainingOutputData.cols);

    mlp->setLayerSizes(layersSize);
    mlp->setActivationFunction(ANN_MLP::ActivationFunctions::SIGMOID_SYM);

    TermCriteria term = TermCriteria(
        TermCriteria::Type::COUNT + TermCriteria::Type::EPS,
        100000000,
        0.0000000000000001
    );
    mlp->setTermCriteria(term);
    mlp->setTrainMethod(ANN_MLP::TrainingMethods::BACKPROP);

    Ptr<TrainData> trainingData = TrainData::create(
        trainingInputData,
        SampleTypes::ROW_SAMPLE,
        trainingOutputData
    );

    mlp->train(trainingData);

    for (int i = 0; i < trainingInputData.rows; i++){
        Mat sample = Mat(1, trainingInputData.cols, CV_32F, trainingInput[i]);
        Mat result;
        mlp->predict(sample, result);
        cout << sample << " -> ";
        cout << result << endl;
    }

    return 0;
}
