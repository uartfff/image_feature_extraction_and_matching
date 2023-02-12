//#include "opencv2/opencv.hpp"
//#include <opencv2/nonfree/nonfree.hpp>//SIFT
//#include <vector>
//#include<iostream>
//#include<ctime>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat srcImg1 = imread("E:/biyesheji/Main/imagePairs/A1.png");
//	Mat srcImg2 = imread("E:/biyesheji/Main/imagePairs/A2.png");
//	//定义SIFT特征检测类对象
//	SiftFeatureDetector detector;//sift特征提取//SIFT=SiftFeatureDetector=SiftDescriptorExtractor    别名//定义KeyPoint变量
//	//SURF detector;//surf特征提取
//	//ORB detector;//orb特征提取
//
//	clock_t feature_find_time1, feature_find_time2;
//	vector<KeyPoint>keyPoints1;
//	vector<KeyPoint>keyPoints2;
//	Mat descp1, descp2;
//
//	feature_find_time1 = clock();
//
//	//特征点检测
//	detector.detect(srcImg1, keyPoints1);
//	detector.detect(srcImg2, keyPoints2);
//
//	feature_find_time2 = clock();//特征提取计算耗时
//
//	cout << "特征点检测耗时：" << (double)(feature_find_time2 - feature_find_time1) / CLOCKS_PER_SEC << "s" << endl;
//	cout << "图1的特征点数量：" << keyPoints1.size() << endl;
//	cout << "图2的特征点数量：" << keyPoints2.size() << endl;
//
//	//绘制特征点(关键点)
//	Mat feature_pic1, feature_pic2;
//	drawKeypoints(srcImg1, keyPoints1, feature_pic1, Scalar(0, 0, 255));
//	drawKeypoints(srcImg2, keyPoints2, feature_pic2, Scalar(0, 0, 255));
//	//drawKeypoints(srcImg1, keyPoints1, feature_pic1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);//颜色随机，带有方向
//	//drawKeypoints(srcImg2, keyPoints2, feature_pic2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
//	//显示原图
//	imshow("src1", srcImg1);
//	imshow("src2", srcImg2);
//	//显示结果
//	imshow("feature1", feature_pic1);
//	imwrite("Asiftfeature1.png", feature_pic1);
//	imshow("feature2", feature_pic2);
//	imwrite("Asiftfeature2.png", feature_pic2);
//
//	waitKey(0);
//	return 0;
//}