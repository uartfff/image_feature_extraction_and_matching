//#include "gms_matcher.h"
//#include <iostream>
//#include "opencv2/opencv.hpp"
//#include "opencv2/core/core.hpp"  
//#include "opencv2/features2d/features2d.hpp"  
//#include "opencv2/highgui/highgui.hpp"  
//#include  "opencv2/legacy/legacy.hpp" // 暴力匹配的头文件
//#include  "opencv2/nonfree/nonfree.hpp"
//#include <iostream>  
//#include <vector> 
//#include <ctime>
//
////#define USE_GPU 
//#ifdef USE_GPU
//#include <opencv2/cudafeatures2d.hpp>
//using cuda::GpuMat;
//#endif
//
//void GmsMatch(Mat &img1, Mat &img2);
//Mat DrawInlier(Mat &src1, Mat &src2, vector<KeyPoint> &kpt1, vector<KeyPoint> &kpt2, vector<DMatch> &inlier, int type);
//
//void runImagePair() {
//	Mat img1 = imread("E:/biyesheji/Main/imagePairs/A1.png");
//	Mat img2 = imread("E:/biyesheji/Main/imagePairs/A2.png");
//
//	GmsMatch(img1, img2);
//}
//
//
//int main()
//{
//#ifdef USE_GPU
//	int flag = cuda::getCudaEnabledDeviceCount();
//	if (flag != 0) { cuda::setDevice(0); }
//#endif // USE_GPU
//
//	runImagePair();
//
//	return 0;
//}
//
//void GmsMatch(Mat &img1, Mat &img2) {
//	Rect re1((img1.cols) / 2, 0, (img1.cols) / 2, img1.rows);
//	Mat roi1 = img1(re1);
//	Rect re2(0, 0, (img1.cols) / 2, img1.rows);
//	Mat roi2 = img2(re2);
//
//	vector<KeyPoint> kp1, kp2;
//	vector<KeyPoint>keyPoints1, keyPoints2;
//	Mat d1, d2;
//	vector<DMatch> matches_all, matches_gms;
//
//	clock_t feature_find_time1, feature_find_time2;
//	feature_find_time1 = clock();
//
//	SIFT sift;//sift特征提取
//	sift(roi1, Mat(), kp1,d1);
//	sift(roi2, Mat(), kp2, d2);
//
//	//SURF surf;//surf特征提取
//	//surf(roi1, Mat(), kp1, d1);
//	//surf(roi2, Mat(), kp2, d2);
//
//	feature_find_time2 = clock();
//
//	for (int i = 0; i < kp1.size(); i++)
//	{
//		kp1[i].pt.x += (img1.cols) / 2; //只对重叠区域做特征提取，所以到原图里面坐标横坐标需要增加图像宽度的1/2
//	}
//
//	cout << "特征点检测耗时：" << (double)(feature_find_time2 - feature_find_time1) / CLOCKS_PER_SEC << "s" << endl;
//	cout << "图1的特征点数量kp1：" << kp1.size() << endl;
//	cout << "图2的特征点数量kp2：" << kp2.size() << endl;
//
//	Mat show1, show2;
//	drawKeypoints(img1, kp1, show1);
//	imshow("features1", show1);
//	//imwrite("IORBfeatures1.png", show1);
//	drawKeypoints(img2, kp2, show2);
//	imshow("features2", show2);
//	//imwrite("IORBfeatures2.png", show2);
//
//#ifdef USE_GPU
//	GpuMat gd1(d1), gd2(d2);
//	Ptr<cuda::DescriptorMatcher> matcher = cv::cuda::DescriptorMatcher::createBFMatcher(NORM_HAMMING);
//	matcher->match(gd1, gd2, matches_all);
//#else
//	clock_t t1, t2;
//	t1 = clock();
//	FlannBasedMatcher matcher;
//	matcher.match(d1, d2, matches_all);
//	t2 = clock();
//	cout << "暴力匹配耗时：" << (double)(t2 - t1) / CLOCKS_PER_SEC << "s" << endl;
//#endif
//
//	cout << "匹配总数："<<matches_all.size() << endl;
//	// GMS filter
//	std::vector<bool> vbInliers;
//	clock_t start, finish;
//	start = clock();
//	gms_matcher gms(kp1, img1.size(), kp2, img2.size(), matches_all);
//
//	int num_inliers = 0;
//	num_inliers=gms.GetInlierMask(vbInliers, false, false);
//	finish = clock();
//	cout << "GMS consumes：" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
//	cout << "Get total " << num_inliers << " matches." << endl;
//
//	// collect matches
//	for (size_t i = 0; i < vbInliers.size(); ++i)
//	{
//		if (vbInliers[i] == true)
//		{
//			matches_gms.push_back(matches_all[i]);
//		}
//	}
//
//	// draw matching
//	Mat show = DrawInlier(img1, img2, kp1, kp2, matches_gms, 1);
//	imshow("show", show);
//	imwrite("A_sift_GMS.png", show);
//	//imshow("showMatch", showMatch);
//	//imwrite("WithNCC.png", show);
//	waitKey();
//}
//
//Mat DrawInlier(Mat &src1, Mat &src2, vector<KeyPoint> &kpt1, vector<KeyPoint> &kpt2, vector<DMatch> &inlier, int type) {
//	const int height = max(src1.rows, src2.rows);
//	const int width = src1.cols + src2.cols;
//	Mat output(height, width, CV_8UC3, Scalar(0, 0, 0));
//	src1.copyTo(output(Rect(0, 0, src1.cols, src1.rows)));
//	src2.copyTo(output(Rect(src1.cols, 0, src2.cols, src2.rows)));
//
//	if (type == 1)
//	{
//		for (size_t i = 0; i < inlier.size(); i++)
//		{
//			Point2f left = kpt1[inlier[i].queryIdx].pt;
//			Point2f right = (kpt2[inlier[i].trainIdx].pt + Point2f((float)src1.cols, 0.f));
//			line(output, left, right, Scalar(0, 255, 255));
//		}
//	}
//	else if (type == 2)
//	{
//		for (size_t i = 0; i < inlier.size(); i++)
//		{
//			Point2f left = kpt1[inlier[i].queryIdx].pt;
//			Point2f right = (kpt2[inlier[i].trainIdx].pt + Point2f((float)src1.cols, 0.f));
//			line(output, left, right, Scalar(255, 0, 0));
//		}
//
//		for (size_t i = 0; i < inlier.size(); i++)
//		{
//			Point2f left = kpt1[inlier[i].queryIdx].pt;
//			Point2f right = (kpt2[inlier[i].trainIdx].pt + Point2f((float)src1.cols, 0.f));
//			circle(output, left, 1, Scalar(0, 255, 255), 2);
//			circle(output, right, 1, Scalar(0, 255, 0), 2);
//		}
//	}
//
//	return output;
//}
