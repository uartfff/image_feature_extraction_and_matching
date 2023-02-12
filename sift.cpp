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
//	//����SIFT������������
//	SiftFeatureDetector detector;//sift������ȡ//SIFT=SiftFeatureDetector=SiftDescriptorExtractor    ����//����KeyPoint����
//	//SURF detector;//surf������ȡ
//	//ORB detector;//orb������ȡ
//
//	clock_t feature_find_time1, feature_find_time2;
//	vector<KeyPoint>keyPoints1;
//	vector<KeyPoint>keyPoints2;
//	Mat descp1, descp2;
//
//	feature_find_time1 = clock();
//
//	//��������
//	detector.detect(srcImg1, keyPoints1);
//	detector.detect(srcImg2, keyPoints2);
//
//	feature_find_time2 = clock();//������ȡ�����ʱ
//
//	cout << "���������ʱ��" << (double)(feature_find_time2 - feature_find_time1) / CLOCKS_PER_SEC << "s" << endl;
//	cout << "ͼ1��������������" << keyPoints1.size() << endl;
//	cout << "ͼ2��������������" << keyPoints2.size() << endl;
//
//	//����������(�ؼ���)
//	Mat feature_pic1, feature_pic2;
//	drawKeypoints(srcImg1, keyPoints1, feature_pic1, Scalar(0, 0, 255));
//	drawKeypoints(srcImg2, keyPoints2, feature_pic2, Scalar(0, 0, 255));
//	//drawKeypoints(srcImg1, keyPoints1, feature_pic1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);//��ɫ��������з���
//	//drawKeypoints(srcImg2, keyPoints2, feature_pic2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
//	//��ʾԭͼ
//	imshow("src1", srcImg1);
//	imshow("src2", srcImg2);
//	//��ʾ���
//	imshow("feature1", feature_pic1);
//	imwrite("Asiftfeature1.png", feature_pic1);
//	imshow("feature2", feature_pic2);
//	imwrite("Asiftfeature2.png", feature_pic2);
//
//	waitKey(0);
//	return 0;
//}