#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	// 이미지 읽기
	Mat src1 = imread("data/graf1.png", IMREAD_COLOR);
	Mat src2 = imread("data/graf3.png", IMREAD_COLOR);

	if (src1.empty() || src2.empty())
		cerr << "Image load failed" << endl;
	
	// feature 객체 생성
	Ptr<Feature2D> feature = KAZE::create();
	// keypoints 벡터
	vector<KeyPoint> keypoints1, keypoints2;
	// descriptor 행렬
	Mat desc1, desc2;

	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);

	// 특징점 매칭
	Ptr<DescriptorMatcher> matcher = BFMatcher::create();
	vector<DMatch> matches;

	matcher->match(desc1, desc2, matches);

	// Good 매칭 선택( 둘 간의 거리가 작다면 OK)
	sort(matches.begin(), matches.end());
	vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);

	cout << "number of keypoints1 : " << keypoints1.size() << std::endl;
	cout << "number of keypoints2 : " << keypoints2.size() << std::endl;
	cout << "number of good matches : " << good_matches.size() << std::endl;

	// 매칭 결과를  dst에 그린다
	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst,
		Scalar::all(-1), Scalar::all(-1), vector<char>());

	// 호모그래피를 구하기 위해 쿼리 특징점, 받는 특징점을 pts1, pts2에 옮긴다.
	vector<Point2f> pts1, pts2;
	for (size_t i = 0; i < good_matches.size(); i++)
	{
		pts1.push_back(keypoints1[good_matches[i].queryIdx].pt);
		pts2.push_back(keypoints2[good_matches[i].queryIdx].pt);
	}

	// 호모그래피 변환 행렬
	Mat H = findHomography(pts1, pts2, RANSAC);

	vector<Point2f> corners1, corners2;
	corners1.emplace_back(Point2f(0, 0));
	corners1.emplace_back(Point2f(src1.cols - 1.f, 0));
	corners1.emplace_back(Point2f(src1.cols - 1.f, src1.rows - 1.f));
	corners1.emplace_back(Point2f(0, src1.rows - 1.f));
	perspectiveTransform(corners1, corners2, H);

	// 호모그래피로 변환된 코너를 오른쪽 그림에 옮긴다.
	vector<Point> corners_dst;
	for (Point2f pt : corners2)
		corners_dst.emplace_back(Point(cvRound(pt.x + src1.cols), cvRound(pt.y)));
	// 호모그래피로 변환된 부분에 사각형을 그린다.
	polylines(dst, corners_dst, true, Scalar(0, 255, 0), 2, LINE_AA);
	// imshow
	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();

	return 0;
}