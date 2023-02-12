#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"  
#include "opencv2/features2d/features2d.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include  "opencv2/legacy/legacy.hpp" // ����ƥ���ͷ�ļ�
#include  "opencv2/nonfree/nonfree.hpp"
#include <iostream>  
#include <vector> 
#include <ctime>


using namespace std;
using namespace cv;

void main() {


	Mat img_1 = imread("E:/biyesheji/Main/imagePairs/C1.png");
	Mat img_2 = imread("E:/biyesheji/Main/imagePairs/C2.png");
	
	Rect re1((img_1.cols) / 2, 0, (img_1.cols) / 2, img_1.rows);
	Mat roi1 = img_1(re1);
	Rect re2(0, 0, (img_1.cols) / 2, img_1.rows);
	Mat roi2 = img_2(re2);

	if (!img_1.data || !img_2.data)
	{
		cout << "error reading images " << endl;
		return;
	}

	vector<KeyPoint> keyPoints_1, keyPoints_2;
	Mat descriptors_1, descriptors_2;

	//-----------------SIFT featrue Point----------------
	/*SIFT sift;*/
	clock_t start, finish;
	start = clock();
	//sift(roi1, Mat(), keyPoints_1, descriptors_1);//��ͼ���ص��������������ȡ��ƥ��
	//sift(roi2, Mat(), keyPoints_2, descriptors_2);
	

	//-----------------SURF featrue Point----------------
	SURF surf;
	surf(roi1, Mat(), keyPoints_1, descriptors_1);
	surf(roi2, Mat(), keyPoints_2, descriptors_2);

	finish = clock();
	cout << "��������ʱ��" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;

	for (int i = 0; i < keyPoints_1.size(); i++)
	{
		keyPoints_1[i].pt.x += (img_1.cols) / 2; //ֻ���ص�������������ȡ�����Ե�ԭͼ���������������Ҫ����ͼ���ȵ�1/2
	}


	/*-----------------ORB featrue Point----------------
	MSER mesr;
	 */

	 /*-----------------FAST featrue Point----------------
	 FastFeatureDetector fast1(100);   // ������ֵΪ40
	 FastFeatureDetector fast2(100);

	 fast1.detect(img_1, keyPoints_1);
	 fast2.detect(img_2, keyPoints_2);
	 //SurfDescriptorExtractor extrator;           // another surf sift operation
	 //extrator.compute(img_1, keyPoints_1, descriptors_1);
	 //extrator.compute(img_2, keyPoints_2, descriptors_2);

	 OrbDescriptorExtractor extrator;
	 extrator.compute(img_1, keyPoints_1, descriptors_1);
	 extrator.compute(img_2, keyPoints_2, descriptors_2);
	 */

	 //����������(�ؼ���)
	Mat feature_pic1, feature_pic2;
	drawKeypoints(img_1, keyPoints_1, feature_pic1, Scalar::all(-1));
	drawKeypoints(img_2, keyPoints_2, feature_pic2, Scalar::all(-1));
	
	imshow("show1", feature_pic1);
	imwrite("C1_SURF.png", feature_pic1);
	imshow("show2", feature_pic2);
	imwrite("C2_SURF.png", feature_pic2);

	//BruteForceMatcher<HammingLUT> matcher;// orb ��float�͵�
	cout << "ͼ��1������������" << keyPoints_1.size() << endl;
	cout << "ͼ��2������������" << keyPoints_2.size() << endl;

	FlannBasedMatcher matcher;   // ֻ�� ��uchar�ĵ����ƥ��,����SIFT��SURF

	vector< DMatch > matches;

	clock_t start1, finish1;
	start1 = clock();

	matcher.match(descriptors_1, descriptors_2, matches);

	finish1 = clock();

	cout << "����ƥ���ʱ��" << (double)(finish1 - start1) / CLOCKS_PER_SEC << "s" << endl;

//
//	double max_dist = 0; double min_dist = 100;
//	//-- Quick calculation of max and min distances between keypoints  
//	for (int i = 0; i < descriptors_1.rows; i++)
//	{
//		double dist = matches[i].distance;
//		if (dist < min_dist) min_dist = dist;
//		if (dist > max_dist) max_dist = dist;
//	}
//	cout << "-- Max dist :" << max_dist << endl;
//	cout << "-- Min dist :" << min_dist << endl;
//
//	//-- Draw only "good" matches (i.e. whose distance is less than 0.6*max_dist )  
//	//-- PS.- radiusMatch can also be used here.  
//	
//	vector< DMatch > good_matches;
//	for (int i = 0; i < descriptors_1.rows; i++)
//	{
//		if (matches[i].distance < 0.65*max_dist)
//		{
//			good_matches.push_back(matches[i]);
//		}
//	}
//	finish = clock();
//
//	cout << "����ƥ���ʱ��" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
//
//	// vector<KeyPoint> m_LeftKey;
//	// vector<KeyPoint> m_RightKey;
//	// vector<DMatch> m_Matches;
//	// �������������Ѿ�������������ֱ�����ȡ�Ĺؼ��㼰��ƥ�䣬����ֱ�Ӽ���F
//
//	// ����ռ�
//	int ptCount = (int)matches.size();
//	Mat p1(ptCount, 2, CV_32F);
//	Mat p2(ptCount, 2, CV_32F);
//
//	// ��Keypointת��ΪMat
//	Point2f pt;
//	for (int i = 0; i < ptCount; i++)
//	{
//		pt = keyPoints_1[matches[i].queryIdx].pt;
//		p1.at<float>(i, 0) = pt.x;
//		p1.at<float>(i, 1) = pt.y;
//
//		pt = keyPoints_2[matches[i].trainIdx].pt;
//		p2.at<float>(i, 0) = pt.x;
//		p2.at<float>(i, 1) = pt.y;
//	}
//
//
//	// ��RANSAC�������� ��������F
//	Mat m_Fundamental;
//	vector<uchar> m_RANSACStatus;
//
//	m_Fundamental = findFundamentalMat(p1, p2, m_RANSACStatus, FM_RANSAC);//?????????????????
//	cout << "��������Ϊ��" << m_Fundamental << endl;
//
//	// ����Ұ�����
//	int OutlinerCount = 0;
//	for (int i = 0; i < ptCount; i++)
//	{
//		if (m_RANSACStatus[i] == 0) // ״̬Ϊ0��ʾҰ��
//		{
//			OutlinerCount++;
//		}
//	}
//
//	// �����ڵ�
//	vector<Point2f> m_LeftInlier;
//	vector<Point2f> m_RightInlier;
//	vector<DMatch> m_InlierMatches;
//	// ���������������ڱ����ڵ��ƥ���ϵ
//	int InlinerCount = ptCount - OutlinerCount;
//	m_InlierMatches.resize(InlinerCount);
//	m_LeftInlier.resize(InlinerCount);
//	m_RightInlier.resize(InlinerCount);
//	InlinerCount = 0;
//	for (int i = 0; i < ptCount; i++)
//	{
//		if (m_RANSACStatus[i] != 0)
//		{
//			m_LeftInlier[InlinerCount].x = p1.at<float>(i, 0);
//			m_LeftInlier[InlinerCount].y = p1.at<float>(i, 1);
//			m_RightInlier[InlinerCount].x = p2.at<float>(i, 0);
//			m_RightInlier[InlinerCount].y = p2.at<float>(i, 1);
//			m_InlierMatches[InlinerCount].queryIdx = InlinerCount;
//			m_InlierMatches[InlinerCount].trainIdx = InlinerCount;
//			InlinerCount++;
//		}
//	}
//
//	// ���ڵ�ת��ΪdrawMatches����ʹ�õĸ�ʽ
//	vector<KeyPoint> key1(InlinerCount);
//	vector<KeyPoint> key2(InlinerCount);
//	KeyPoint::convert(m_LeftInlier, key1);
//	KeyPoint::convert(m_RightInlier, key2);
//
//	// ��ʾ����F������ڵ�ƥ��
//	 //Mat m_matLeftImage;
//	 //Mat m_matRightImage;
//	// ���������������������������ͼ��
//	Mat OutImage;
//	drawMatches(img_1, key1, img_2, key2, m_InlierMatches, OutImage);
//
//	cout << "�ڵ�������" << m_InlierMatches.size() << endl;
//	
//	//��KeyPointת��ΪPoint2f���㵥Ӧ����
//	vector<Point2f>points1, points2;
//	for (vector<DMatch>::const_iterator it = m_InlierMatches.begin(); it != m_InlierMatches.end(); ++it)
//	{
//		float x = key1[it->trainIdx].pt.x;
//		float y = key1[it->trainIdx].pt.y;
//		points1.push_back(Point2f(x, y));
//
//		x = key2[it->trainIdx].pt.x;
//		y = key2[it->trainIdx].pt.y;
//		points2.push_back(Point2f(x, y));
//	}
//	vector<uchar>inliers;
//	Mat homography = findHomography(points1, points2, inliers, RANSAC,1.);
//
//
//	cout << "��Ӧ����Ϊ��" << homography << endl;
//
//	//stereoRectifyUncalibrated();
//
//	Mat img_matches;
//	drawMatches(img_1, keyPoints_1, img_2, keyPoints_2,
//		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
//		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
//	cout << "good_matches:" << good_matches.size() << endl;
//
//
//	imwrite("FASTResult.jpg", img_matches); //��ƥ���ƥ��ͼ
//	imshow("Match", img_matches);
//	//imwrite("C_ORE_RANSAC_Match.png", img_matches);
//
//	imwrite("FmatrixResult.jpg", OutImage); //�ڵ��ƥ��ͼ
//	imshow("Match2", OutImage);
//	imwrite("C_ORE_RANSAC_Match.png", OutImage);
	waitKey(0);

	return ;
}
