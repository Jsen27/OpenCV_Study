#include "stdafx.h"
#include "PuddleVolksImgFunc.h"

void dispImage(Mat src, String name_window, float scale)
{
	if ((src.depth() == CV_32F) || (src.depth() == CV_64F))
	{
		src.convertTo(src, CV_8U, 256);
		//src = src * 256;
	}
	resize(src, src, Size(), scale, scale, INTER_CUBIC);
	imshow(name_window, src);
}

void matScaleFloat(Mat src, float scale)
{
	float* data = (float*)src.data;
	for (int idy = 0; idy < src.rows; idy++)
	{
		for (int idx = 0; idx < src.cols; idx++)
		{
			data[idy*src.cols + idx] *= scale;
		}
	}
}

Mat matSobelOperation(Mat src, E_SOBEL_DIR dir)
{
	Mat kernel(3, 3, CV_32F, Scalar(0));
	Mat dst;

	switch (dir)
	{
	case SOBEL_HOR:
		kernel.at<float>(0, 0) = -1;
		kernel.at<float>(1, 0) = -1;
		kernel.at<float>(2, 0) = -1;
		kernel.at<float>(0, 2) = 1;
		kernel.at<float>(1, 2) = 1;
		kernel.at<float>(2, 2) = 1;
		break;
	case SOBEL_VER:
		kernel.at<float>(0, 0) = -1;
		kernel.at<float>(0, 1) = -1;
		kernel.at<float>(0, 2) = -1;
		kernel.at<float>(2, 0) = 1;
		kernel.at<float>(2, 1) = 1;
		kernel.at<float>(2, 2) = 1;
		break;
	case SOBEL_DIAG:
		kernel.at<float>(0, 1) = 1;
		kernel.at<float>(0, 2) = 2;
		kernel.at<float>(1, 2) = 1;
		kernel.at<float>(1, 0) = -1;
		kernel.at<float>(2, 0) = -2;
		kernel.at<float>(2, 1) = -1;
		break;
	case SOBEL_ADIAG:
		kernel.at<float>(1, 2) = 1;
		kernel.at<float>(2, 2) = 2;
		kernel.at<float>(2, 1) = 1;
		kernel.at<float>(0, 1) = -1;
		kernel.at<float>(0, 0) = -2;
		kernel.at<float>(1, 0) = -1;
		break;
	default:
		kernel.at<float>(0, 0) = -1;
		kernel.at<float>(1, 0) = -1;
		kernel.at<float>(2, 0) = -1;
		kernel.at<float>(0, 2) = 1;
		kernel.at<float>(1, 2) = 1;
		kernel.at<float>(2, 2) = 1;
		break;
	}
	filter2D(src, dst, src.depth(), kernel);
	return dst;
}

Rect getObjectRect(Mat src_bin, int margin)
{
	Rect roi_object;
	int startX, startY, endX, endY;
	uchar* data = (uchar*)src_bin.data;
	startX = src_bin.cols;
	startY = src_bin.rows;
	endX = 0;
	endY = 0;
	
	for (int idy = 0; idy < src_bin.rows; idy++)
	{
		for (int idx = 0; idx < src_bin.cols; idx++)
		{
			if (data[idy*src_bin.cols + idx] >= 1)
			{
				if (startX > idx)
					startX = idx;
				if (startY > idy)
					startY = idy;
				if (endX < idx)
					endX = idx;
				if (endY < idy)
					endY = idy;
			}
		}
	}

	startX -= margin;
	startY -= margin;
	endX += margin;
	endY += margin;

	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;
	if (endX >= src_bin.cols)
		endX = src_bin.cols - 1;
	if (endY >= src_bin.rows)
		endY = src_bin.rows - 1;

	roi_object.x = startX;
	roi_object.y = startY;
	roi_object.width = endX - startX;
	roi_object.height = endY - startY;

	return roi_object;
}

Rect fgetObjectRect(Mat src_bin,Mat src_ref, int margin)
{
	Rect roi_object;
	int startX, startY, endX, endY;
	float* data = (float*)src_bin.data;
	startX = src_bin.cols;
	startY = src_bin.rows;
	endX = 0;
	endY = 0;

	//-----------------------------------------
	// 로고 모양의 최외곽 좌표 검사
	//-----------------------------------------
	for (int idy = 0; idy < src_bin.rows; idy++)
	{
		for (int idx = 0; idx < src_bin.cols; idx++)
		{
			if (data[idy*src_bin.cols + idx] >= 1)
			{
				if (startX > idx)
					startX = idx;
				if (startY > idy)
					startY = idy;
				if (endX < idx)
					endX = idx;
				if (endY < idy)
					endY = idy;
			}
		}
	}
	
	
	//-----------------------------------------
	// Margin 적용
	//-----------------------------------------
	startX -= margin;
	startY -= margin;
	endX += margin;
	endY += margin;

	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;
	if (endX >= src_bin.cols)
		endX = src_bin.cols - 1;
	if (endY >= src_bin.rows)
		endY = src_bin.rows - 1;


	//-----------------------------------------
	// ROI 계산 
	//-----------------------------------------
	roi_object.x = startX;
	roi_object.y = startY;

	roi_object.width = endX - startX; //cols
	roi_object.height = endY - startY; //row


	if (src_ref.rows > roi_object.height)
	{
		roi_object.y = startY - ((src_ref.rows - roi_object.height) / 2);
		roi_object.height = src_ref.rows;
		
		roi_object.x = startX - ((src_ref.cols - roi_object.width) / 2);
		roi_object.width = src_ref.cols;
	}
	else
	{
		roi_object.y = startY + ((roi_object.height - src_ref.rows ) / 2);
		roi_object.height = src_ref.rows;
		
		roi_object.x = startX + ((roi_object.width - src_ref.cols ) / 2);
		roi_object.width = src_ref.cols;
	}
	
	/*if (src_ref.rows > roi_object.height)
	{
		roi_object.y -= ((src_ref.rows - roi_object.height) / 2)+1;
		roi_object.height = src_ref.rows;
	}

	if (src_ref.cols > roi_object.width)
	{
		roi_object.x -= (src_ref.cols - roi_object.width) / 2;
		roi_object.width = src_ref.cols;
	}*/

	return roi_object;
}


Rect VW310fgetObjectRect(Mat src_bin, Mat src_ref, int margin)
{
	Rect roi_object;
	int startX, startY, endX, endY;
	float* data = (float*)src_bin.data;
	startX = src_bin.cols;
	startY = src_bin.rows;
	endX = 0;
	endY = 0;

	for (int idy = 0; idy < src_bin.rows; idy++)
	{
		for (int idx = 0; idx < src_bin.cols; idx++)
		{
			if (data[idy * src_bin.cols + idx] >= 1)
			{
				if (startX > idx)
					startX = idx;
				if (startY > idy)
					startY = idy;
				if (endX < idx)
					endX = idx;
				if (endY < idy)
					endY = idy;
			}
		}
	}


	startX -= margin;
	startY -= margin;
	endX += margin;
	endY += margin;

	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;
	if (endX >= src_bin.cols)
		endX = src_bin.cols - 1;
	if (endY >= src_bin.rows)
		endY = src_bin.rows - 1;

	roi_object.x = startX;
	roi_object.y = startY;
	roi_object.width = endX - startX; //cols

	roi_object.height = endY - startY; //row


	//if (src_ref.rows > roi_object.height)
	//{
	//	roi_object.y = startY - ((src_ref.rows - roi_object.height) / 2);
	//	roi_object.height = src_ref.rows;
	//	roi_object.x = startX - ((src_ref.cols - roi_object.width) / 2);
	//	roi_object.width = src_ref.cols;
	//}
	//else
	//{
	//	roi_object.y = startY + ((roi_object.height - src_ref.rows) / 2);
	//	roi_object.height = src_ref.rows;
	//	roi_object.x = startX + ((roi_object.width - src_ref.cols) / 2);
	//	roi_object.width = src_ref.cols;
	//}

	/*if (src_ref.rows > roi_object.height)
	{
	roi_object.y -= ((src_ref.rows - roi_object.height) / 2)+1;
	roi_object.height = src_ref.rows;
	}

	if (src_ref.cols > roi_object.width)
	{
	roi_object.x -= (src_ref.cols - roi_object.width) / 2;
	roi_object.width = src_ref.cols;
	}*/

	return roi_object;
}

cv::Rect getObjImg(Mat src, int x, int y, int w, int h, int th)
{
	if (w == 0) {
		w = src.cols;
		h = src.rows;
	}

	Mat dst;
	cvtColor(src, dst, CV_BGR2GRAY);

	threshold(dst, dst, th, 255, 0);


	int margin = 50;
	cv::Rect roi_object;
	int startX, startY, endX, endY;

	uchar* data = (uchar*)dst.data;
	startX = dst.cols;
	startY = dst.rows;
	endX = 0;
	endY = 0;

	for (int idy = 0; idy < src.rows; idy++)
	{
		for (int idx = 0; idx < src.cols; idx++)
		{
			if (idx > x && idx < x + w && idy > y && idy < y + h) {
				if (data[idy * src.cols + idx] >= 1)
				{
					if (startX > idx)
						startX = idx;
					if (startY > idy)
						startY = idy;
					if (endX < idx)
						endX = idx;
					if (endY < idy)
						endY = idy;
				}
			}
		}
	}

	startX -= margin;
	startY -= margin;
	endX += margin;
	endY += margin;

	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;
	if (endX >= src.cols)
		endX = src.cols - 1;
	if (endY >= src.rows)
		endY = src.rows - 1;

	roi_object.x = startX;
	roi_object.y = startY;
	roi_object.width = endX - startX;
	roi_object.height = endY - startY;

	return roi_object;
}

cv::Rect VW276PAgetObjectRect(Mat src_bin, int margin)
{
	Rect roi_object;
	int startX, startY, endX, endY;
	float* data = (float*)src_bin.data;
	startX = src_bin.cols;
	startY = src_bin.rows;
	endX = 0;
	endY = 0;

	for (int idy = 0; idy < src_bin.rows; idy++)
	{
		for (int idx = 0; idx < src_bin.cols; idx++)
		{
			if (data[idy * src_bin.cols + idx] >= 1)
			{
				if (startX > idx)
					startX = idx;
				if (startY > idy)
					startY = idy;
				if (endX < idx)
					endX = idx;
				if (endY < idy)
					endY = idy;
			}
		}
	}

	startX -= margin;
	startY -= margin;
	endX += margin;
	endY += margin;

	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;
	if (endX >= src_bin.cols)
		endX = src_bin.cols - 1;
	if (endY >= src_bin.rows)
		endY = src_bin.rows - 1;

	roi_object.x = startX;
	roi_object.y = startY;
	roi_object.width = endX - startX;
	roi_object.height = endY - startY;

	return roi_object;
}


float getROiEdgeData(cv::Mat edge_data)
{
	Mat dst(edge_data.size(), CV_8UC1);

	uchar* dstData = (uchar*)dst.data;
	float* edgeData;
	//float srcData;

	float sum = 0;
	float mean = 0;
	int count = 0;
	float count2 = 0;
	for (int y = 0; y < edge_data.rows; y++)
	{
		for (int x = 0; x < edge_data.cols; x++)
		{
			//srcData = edgeData[y * edge_data.cols + x];
			edgeData = edge_data.ptr<float>(y);

			if (edgeData[x] > 0.09 && edgeData[x] < 2)
			{
				dstData[y * dst.cols + x] = 0;
				sum += edgeData[x];
				count++;
			}else
				dstData[y * dst.cols + x] = 255;

		}

	}

	if (count > 200)
		mean = sum / count;

	return mean;
}

int getROiEdgeData(cv::Mat edge_data, int x)
{
	Mat dd;
	Mat dst(edge_data.size(), CV_8UC1);
	threshold(edge_data, dd, 50, 255, 0);
	uchar* dstData;
	uchar* edgeData;
	//int srcData;
	
	Scalar ff = mean(edge_data);

	float sum = 0;
	float mean = 0;
	int count = 0;
	float count2 = 0;
	for (int y = 0; y < edge_data.rows; y++)
	{
		for (int x = 0; x < edge_data.cols; x++)
		{
			edgeData = edge_data.ptr<uchar>(y);
			dstData = dst.ptr<uchar>(y);

			if (edgeData[x] > 10 && edgeData[x] < 255)
			{
				dstData[x] = 0;
				sum += edgeData[x];
				count++;
			}
			else
				dstData[x] = 255;


			//if (srcData > 0.1)
			//	count2++;
		}

	}

	if (count > 15)
		mean = sum / count;

	//imshow("dd", dst);
	//imshow("22", dd);

	waitKey(0);

	return count;
}



Rect fgetObjectRect_test(Mat src_bin, Mat src_ref, int margin)
{
	Rect roi_object;
	int startX, startY, endX, endY;
	float* data = (float*)src_bin.data;
	startX = src_bin.cols;
	startY = src_bin.rows;
	endX = 0;
	endY = 0;

	for (int idy = 0; idy < src_bin.rows; idy++)
	{
		for (int idx = 0; idx < src_bin.cols; idx++)
		{
			if (data[idy * src_bin.cols + idx] >= 1)
			{
				if (startX > idx)
					startX = idx;
				if (startY > idy)
					startY = idy;
				if (endX < idx)
					endX = idx;
				if (endY < idy)
					endY = idy;
			}
		}
	}


	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;
	if (endX >= src_bin.cols)
		endX = src_bin.cols - 1;
	if (endY >= src_bin.rows)
		endY = src_bin.rows - 1;

	roi_object.x = startX;
	roi_object.y = startY;
	roi_object.width = endX - startX; //cols

	roi_object.height = endY - startY; //row



	return roi_object;
}



Mat maxFilter(Mat src, int size_kernel)
{
	Mat mat_max = Mat(src.rows, src.cols, CV_32F);
	int size_half = (int)((float)size_kernel / 2);
	Rect rect_roi;

	Mat roi;
	float* data = (float*)src.data;
	float* data_max = (float*)mat_max.data;

	float val_max;
	for (int idy = size_half + 1; idy < src.rows - size_half - 1; idy++)
	{
		for (int idx = size_half + 1; idx < src.cols - size_half - 1; idx++)
		{
			rect_roi.x = idx - size_half;
			rect_roi.y = idy - size_half;
			rect_roi.width = size_kernel;
			rect_roi.height = size_kernel;
			roi = src(rect_roi);
			val_max = 0;
			for (int idr = 0; idr < size_kernel; idr++)
			{
				for (int idc = 0; idc < size_kernel; idc++)
				{
					if (val_max < data[idr*src.cols + idc])
					{
						val_max = data[idr*src.cols + idc];
					}
				}
			}

			if ((data[idy*src.cols + idx] == val_max) && (val_max != 0))
				data_max[idy*src.cols + idx] = val_max;
		}
	}

	return mat_max;
}

Mat fabsMat(Mat src)
{
	Mat dst = Mat(src.rows, src.cols, CV_32F);
	float* data_src = (float*)src.data;
	float* data_dst = (float*)dst.data;
	for (int idy = 0; idy < src.rows; idy++)
	{
		for (int idx = 0; idx < src.cols; idx++)
		{
			data_dst[idy*src.cols + idx] = fabs(data_src[idy*src.cols + idx]);
		}
	}
	return dst;
}

float fmeanMat(Mat src)
{
	float* data = (float*)src.data;
	float mean = 0;
	for (int idy = 0; idy < src.rows; idy++)
	{
		for (int idx = 0; idx < src.cols; idx++)
		{
			mean += fabs(data[idy*src.cols + idx]);
		}
	}
	return mean / (src.rows*src.cols);
}

Mat getROIImageFromEdge(Mat src, Rect* roi_rect, E_GETROI_RETURN_IMG type_img, int size_kernel, float th_edge, int th_edgesum)
{
	Mat roi_image;
	Rect roi;

	Mat edge_hor, edge_ver, edge_diag, edge_adiag;
	Mat edge_horp, edge_verp, edge_diagp, edge_adiagp;
	Mat edge_mag, edge_bin, sum_edge, sum_edge_bin;

	edge_hor = matSobelOperation(src, SOBEL_HOR);
	edge_ver = matSobelOperation(src, SOBEL_VER);
	edge_diag = matSobelOperation(src, SOBEL_DIAG);
	edge_adiag = matSobelOperation(src, SOBEL_ADIAG);

	pow(edge_hor, 2, edge_horp);
	pow(edge_ver, 2, edge_verp);
	pow(edge_diag, 2, edge_diagp);
	pow(edge_adiag, 2, edge_adiagp);
	edge_mag = edge_horp + edge_verp + edge_diagp + edge_adiagp;
	sqrt(edge_mag, edge_mag);

	threshold(edge_mag, edge_bin, th_edge, 1, 0);

	Mat kernelSum(size_kernel, size_kernel, CV_32F, Scalar(1));
	filter2D(edge_bin, sum_edge, edge_bin.depth(), kernelSum);
	threshold(sum_edge, sum_edge_bin, th_edgesum - 1, 1, 0);

	roi = getObjectRect(sum_edge_bin, MARGIN_OBJECT);

	switch (type_img)
	{
	case RETURN_SRC:
		roi_image = src(roi);
		break;
	case RETURN_EDGE:
		roi_image = edge_mag(roi);
		break;
	case RETURN_EDGE_BIN:
		roi_image = edge_bin(roi);
		break;
	case RETURN_SUM:
		roi_image = sum_edge(roi);
		break;
	case RETURN_SUM_BIN:
		roi_image = sum_edge_bin(roi);
		break;
	default:
		roi_image = src(roi);
		break;
	}

	roi_rect->x = roi.x;
	roi_rect->y = roi.y;
	roi_rect->width = roi.width;
	roi_rect->height = roi.height;

	return roi_image;
}

Mat convertAbsNorm(Mat fsrc, int type)
{
	Mat tmp;
	Mat dst = Mat(Size(fsrc.cols, fsrc.rows), type);

	float val_max = 0;
	float* data = (float*)fsrc.data;

	tmp = fabsMat(fsrc);
	for (int idy = 0; idy < fsrc.rows; idy++)
	{
		for (int idx = 0; idx < fsrc.cols; idx++)
		{
			if (val_max < data[idy * fsrc.cols + idx])
				val_max = data[idy * fsrc.cols + idx];
		}
	}

	data = (float*)tmp.data;
	for (int idy = 0; idy < fsrc.rows; idy++)
	{
		for (int idx = 0; idx < fsrc.cols; idx++)
		{
			data[idy * fsrc.cols + idx] /= val_max;
		}
	}

	if (type == CV_32F)
	{
		tmp.copyTo(dst);
	}
	else if (type == CV_8U)
	{
		tmp.convertTo(dst, CV_8U, 256);
	}

	return dst;
}

Mat drawKeypoint(Mat src, vector<KeyPoint> keypoints, Scalar color)
{
	Mat dispImg;
	src.copyTo(dispImg);
	for (int i = 0; i < keypoints.size(); i++)
	{
		circle(dispImg, keypoints[i].pt, 5, color, 1, 8, 0);
	}
	return dispImg;
}

void getHist(Mat src, Mat* r_hist, Mat* g_hist, Mat* b_hist, int cut_low_hist)
{
	src.channels();
	vector<Mat> bgr_planes;
	vector<int> max_bin;
	split(src, bgr_planes);

	int hist_size = SIZE_HIST;

	/// Set the ranges ( for B,G,R) )
	float range[] = { (float)cut_low_hist, 256 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist_buf, g_hist_buf, r_hist_buf;

	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist_buf, 1, &hist_size, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist_buf, 1, &hist_size, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist_buf, 1, &hist_size, &histRange, uniform, accumulate);

	b_hist_buf.copyTo(b_hist[0]);
	g_hist_buf.copyTo(g_hist[0]);
	r_hist_buf.copyTo(r_hist[0]);

	//// Draw the histograms for B, G and R
	//int hist_w = 512; int hist_h = 400;
	//int bin_w = cvRound((double)hist_w / hist_size);

	//Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	///// Normalize the result to [ 0, histImage.rows ]
	//normalize(b_hist_buf, b_hist_buf, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//normalize(g_hist_buf, g_hist_buf, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//normalize(r_hist_buf, r_hist_buf, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	///// Draw for each channel
	//for (int i = 1; i < hist_size; i++)
	//{
	//	line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist_buf.at<float>(i - 1))),
	//		Point(bin_w*(i), hist_h - cvRound(b_hist_buf.at<float>(i))),
	//		Scalar(255, 0, 0), 2, 8, 0);
	//	line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist_buf.at<float>(i - 1))),
	//		Point(bin_w*(i), hist_h - cvRound(g_hist_buf.at<float>(i))),
	//		Scalar(0, 255, 0), 2, 8, 0);
	//	line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist_buf.at<float>(i - 1))),
	//		Point(bin_w*(i), hist_h - cvRound(r_hist_buf.at<float>(i))),
	//		Scalar(0, 0, 255), 2, 8, 0);
	//}

	//b_hist_buf.copyTo(b_hist[0]);
	//g_hist_buf.copyTo(g_hist[0]);
	//r_hist_buf.copyTo(r_hist[0]);

}

vector<float> getMeanRGB(Mat src)
{
	vector<Mat> bgr_planes;
	vector<float> mean_ch;
	if (src.channels() == 3)
		split(src, bgr_planes);
	else
		bgr_planes.push_back(src);

	Scalar mean_buf;


	if (src.channels() == 3)
	{
		mean_buf = cv::mean(bgr_planes[COLOR_B]);
		mean_ch.push_back((float)mean_buf[0]);
		mean_buf = cv::mean(bgr_planes[COLOR_G]);
		mean_ch.push_back((float)mean_buf[0]);
		mean_buf = cv::mean(bgr_planes[COLOR_R]);
		mean_ch.push_back((float)mean_buf[0]);
	}
	else
	{
		mean_buf = cv::mean(bgr_planes[0]);
		mean_ch.push_back((float)mean_buf[0]);
	}

	return mean_ch;
}


Mat avrFrameImg(vector<Mat> src)
{
	Mat dst = Mat::zeros(Size(src[0].cols, src[0].rows), CV_32F);
	Mat buf;

	for (int i = 0; i < src.size(); i++)
	{
		src[i].copyTo(buf);
		buf.convertTo(buf, CV_32F);
		add(dst, buf, dst);
	}
	dst = dst.mul(1 / (float)src.size());
	dst.convertTo(dst, src[0].depth());
	return dst;
}

float calcSADMat(Mat src1, Mat src2)
{
	Mat buf;
	cv::subtract(src1, src2, buf);
	double val_min, val_max;
	minMaxIdx(buf, &val_min, &val_max);
	buf = fabsMat(buf);
	return (float)cv::sum(buf)[0] / (float)(src1.rows*src1.cols);
}

float calcSSDMat(Mat src1, Mat src2)
{
	Mat buf;
	cv::subtract(src1, src2, buf);
	buf = buf.mul(buf);
	return (float)cv::sum(buf)[0] / (float)(src1.rows*src1.cols);
}

float calcCorrMat(Mat src1, Mat src2)
{
	Mat buf, buf1, buf2;
	Scalar mean_src1, mean_src2;
	mean_src1 = cv::mean(src1);
	mean_src2 = cv::mean(src2);
	buf1 = src1 - mean_src1;
	buf2 = src2 - mean_src2;
	buf = buf1.mul(buf2);
	return (float)cv::sum(buf)[0] / (float)(src1.rows*src1.cols);
}

float calcCorrMat(Mat src1, Mat src2, Scalar mean_src1)
{
	Mat buf, buf1, buf2;
	Scalar mean_src2;
	mean_src2 = cv::mean(src2);
	buf1 = src1 - mean_src1;
	buf2 = src2 - mean_src2;
	buf = buf1.mul(buf2);
	return (float)cv::sum(buf)[0] / (float)(src1.rows*src1.cols);
}
 
float calcNCCMat(Mat src1, Mat src2)
{
	Scalar mean_src1, mean_src2;
	Scalar stdv_src1, stdv_src2;
	Mat buf, buf1, buf2;

	meanStdDev(src1, mean_src1, stdv_src1); //Æò±Õ, Ç¥ÁØÆíÂ÷ 
	meanStdDev(src2, mean_src2, stdv_src2);

	buf1 = src1 - mean_src1;
	buf2 = src2 - mean_src2;
	buf = buf1.mul(buf2);
	buf = buf.mul(1 / (stdv_src1[0] * stdv_src2[0]));
	return (float)cv::sum(buf)[0] / (float)(src1.rows * src1.cols);

	////buf = src1 - mean_src1;

	//buf1 = src1 - mean_src1;
	//buf2 = src2 - mean_src2;
	//buf = buf1.mul(buf2);

	////float sum1 = cv::sum(buf)[0];

	//buf = buf.mul(1 / (stdv_src1[0] * stdv_src2[0]));
	//
	////buf = buf.mul((float)(1 / (stdv_src1[0])));

	//float sum = cv::sum(buf)[0];

	//return (float)cv::sum(buf)[0] / (float)(src1.rows*src1.cols);
}

float calcNCCMat(Mat src1, Mat src2, Scalar mean_src1, Scalar stdv_src1)
{
	Scalar mean_src2;
	Scalar stdv_src2;
	Mat buf, buf1, buf2;

	meanStdDev(src2, mean_src2, stdv_src2);

	buf1 = src1 - mean_src1;
	buf2 = src2 - mean_src2;
	buf = buf1.mul(buf2);
	buf = buf.mul(1 / (stdv_src1[0] * stdv_src2[0]));
	return (float)cv::sum(buf)[0] / (float)(src1.rows*src1.cols);
}

float calcNSSDMat(Mat src1, Mat src2)
{
	Scalar mean_src1, mean_src2;
	Scalar stdv_src1, stdv_src2;
	Mat buf, buf1, buf2;

	meanStdDev(src1, mean_src1, stdv_src1);
	meanStdDev(src2, mean_src2, stdv_src2);

	buf1 = src1 - mean_src1;
	buf2 = src2 - mean_src2;
	buf = buf1 - buf2;
	buf = buf.mul(buf);
	buf = buf.mul(1 / (stdv_src1[0] * stdv_src2[0]));
	return (float)cv::sum(buf)[0] / (float)(src1.rows*src1.cols);
}

Mat sharpImage(Mat src, int size_kernel)
{
	Mat edge_enhanced;
	Mat kernel_edge(size_kernel, size_kernel, CV_32F, Scalar(-1));
	kernel_edge.at<float>(Point(1, 1)) = (float)size_kernel*size_kernel;
	filter2D(src, edge_enhanced, src.depth(), kernel_edge);

	return edge_enhanced;
}

Mat getEdgeMag(Mat src)
{
	Mat g_src, f_src;
	Mat edge_hor, edge_ver, edge_diag, edge_adiag;
	Mat edge_mag;

	if (src.channels() != 1)
		cvtColor(src, g_src, CV_BGR2GRAY);
	else
		src.copyTo(g_src);
	
	if (src.depth() != CV_32FC1)
		g_src.convertTo(f_src, CV_32FC1, 1.0 / 255.0);
	else
		g_src.copyTo(f_src);

	edge_hor = matSobelOperation(f_src, SOBEL_HOR);
	edge_ver = matSobelOperation(f_src, SOBEL_VER);
	edge_diag = matSobelOperation(f_src, SOBEL_DIAG);
	edge_adiag = matSobelOperation(f_src, SOBEL_ADIAG);

	pow(edge_hor, 2, edge_hor);
	pow(edge_ver, 2, edge_ver);
	pow(edge_diag, 2, edge_diag);
	pow(edge_adiag, 2, edge_adiag);
	edge_mag = edge_hor + edge_ver +edge_diag + edge_adiag;
	sqrt(edge_mag, edge_mag);
	
	/*imwrite("edge_hor.jpg", edge_hor);
	imwrite("edge_ver.jpg", edge_ver);
	imwrite("edge_diag.jpg", edge_diag);
	imwrite("edge_adiag.jpg", edge_adiag);*/

	return edge_mag;
}

float gauss(float x, float sigma, bool norm)
{
	float gauss_val = exp(-(x*x)/(2*sigma*sigma));
	if (norm == true)
		gauss_val /= (float)(sigma * sqrt(2 * PI));

	return gauss_val;
}

float gauss2d(float x, float y, float sigma_x, float sigma_y, bool norm)
{
	float gauss_x, gauss_y, gauss_val;
	gauss_x = gauss(x, sigma_x, norm);
	gauss_y = gauss(y, sigma_y, norm);
	gauss_val = gauss_x*gauss_y;

	return gauss_val;
}

int countThreshold(Mat fsrc, float thLow, float thHigh)
{
	int x, y;
	int cnt = 0;

	float* data = (float*)fsrc.data;

	for (y = 0; y < fsrc.rows; y++)
	{
		for (x = 0; x < fsrc.cols; x++)
		{
			if ((data[y * fsrc.cols + x] > thLow) && (data[y * fsrc.cols + x] <= thHigh))
			{
				cnt++;
			}
		}
	}
	return cnt;
}

float intpBilinear(Point p, Point p1, Point p2, Point p3, Point p4, float v1, float v2, float v3, float v4)
{
	float xv1 = (float)((p.x - p1.x)*v2 + (p2.x - p.x)*v1) / (p2.x - p1.x);
	float xv2 = (float)((p.x - p1.x)*v4 + (p2.x - p.x)*v3) / (p2.x - p1.x);
	return (float)((p.y - p1.y)*xv2 + (p3.y - p.y)*xv1) / (p3.y - p1.y);
}