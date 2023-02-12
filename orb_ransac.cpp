#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<ctime>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat obj = imread("E:/biyesheji/Main/imagePairs/A1.png");   //����Ŀ��ͼ��
	Mat scene = imread("C:/Users/10310/Desktop/010635.png"); //���볡��ͼ��
	if (obj.empty() || scene.empty())
	{
		cout << "Can't open the picture!\n";
		return 0;
	}
	vector<KeyPoint> obj_keypoints, scene_keypoints;
	Mat obj_descriptors, scene_descriptors;
	//ORB detector;     //����ORB�㷨��ȡ������
	//ORB orb;
	Ptr<ORB> detector = ORB::create(200, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 50);
	//Ptr<ORB> detector1 = ORB::create(508);//����ͼһ������������(A1:534,B1:510,C1:568)
	//Ptr<ORB> detector2 = ORB::create(530);//����ͼ��������������(A2:610,B2:527,C2:590)
	detector->setFastThreshold(0);
	detector->setFastThreshold(0);
	
	clock_t detect_start, detect_finish;
	detect_start = clock();

	detector->detectAndCompute(obj, Mat(), obj_keypoints, obj_descriptors);
	detector->detectAndCompute(scene, Mat(), scene_keypoints, scene_descriptors);

	//Rect re1((obj.cols) / 2, 0, (obj.cols) / 2, obj.rows);
	//	Mat roi1 = obj(re1);
	//	Rect re2(0, 0, (obj.cols) / 2, obj.rows);
	//	Mat roi2 = scene(re2);
	//detector1->detectAndCompute(roi1, Mat(), obj_keypoints, obj_descriptors);//ֻ���ص�������������ȡ
	//detector2->detectAndCompute(roi2, Mat(), scene_keypoints, scene_descriptors);
	//for (int i = 0; i < obj_keypoints.size(); i++)
	//{
	//	obj_keypoints[i].pt.x += (obj.cols) / 2; //ֻ���ص�������������ȡ�����Ե�ԭͼ���������������Ҫ����ͼ���ȵ�1/2
	//}
	detect_finish = clock();
	cout << "���������ʱ��" << (double)(detect_finish - detect_start) / CLOCKS_PER_SEC << "s" << endl;

	Mat img1_with_features, img2_with_features;

	drawKeypoints(obj, obj_keypoints, img1_with_features);
	drawKeypoints(scene, scene_keypoints, img2_with_features);
	imshow("img1_with_features", img1_with_features);
	imwrite("imgC1_with_features_new.png", img1_with_features);
	imshow("img2_with_features", img2_with_features);
	imwrite("A.png", img2_with_features);

	BFMatcher matcher(NORM_HAMMING); //����������Ϊ���ƶȶ���

	//ƥ��������matches����
	vector<DMatch> matches;
	vector<DMatch>good_matches;
	matcher.match(obj_descriptors, scene_descriptors, matches);

	cout << "ͼ��1����������" << obj_keypoints.size() << endl;
	cout << "ͼ��2����������" << scene_keypoints.size() << endl;
	cout << "����ƥ�����" << matches.size() << endl;

	//����ƥ���ϵ��ͼ������������ͼΪmatch_img
	Mat match_img;
	drawMatches(obj, obj_keypoints, scene, scene_keypoints, matches, match_img);
	imshow("all_matches", match_img);
	//imwrite("C__NewORB_RANSAC.png", match_img);

	//����ƥ������
	vector<int> queryIdxs(matches.size()), trainIdxs(matches.size());
	for (size_t i = 0; i < matches.size(); i++)
	{
		queryIdxs[i] = matches[i].queryIdx;//ȡ����ѯͼƬ��ƥ��ĵ�Ե�������id�ţ���ôqueryIdxs��trainIdxs��Ϊ257
		trainIdxs[i] = matches[i].trainIdx;//ȡ��ѵ��ͼƬ��ƥ��ĵ�Ե�������id�ţ�
	}

	Mat H12;   //�任����

	vector<Point2f> points1;
	KeyPoint::convert(obj_keypoints, points1, queryIdxs);//KeyPoint��������תpoint2f����
	vector<Point2f> points2;
	KeyPoint::convert(scene_keypoints, points2, trainIdxs);//ͬ��
	int ransacReprojThreshold = 2;  //�ܾ���ֵ,����ͶӰ���

	cout << "matches size = " << matches.size() << endl;
	H12 = findHomography(Mat(points1), Mat(points2), CV_RANSAC, ransacReprojThreshold);//���㵥Ӧ����
	vector<char> matchesMask(matches.size(), 0);//�����ڵ���ʹ��
	Mat points1t;
	perspectiveTransform(Mat(points1), points1t, H12);//�������ά����͸�ӱ任���任��Ľ��������points1t��

	int sz = matches.size();

	double max_dist = 0; double min_dist = 100;

	for (int i = 0; i < sz; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	cout << "\n-- Max dist : " << max_dist << endl;
	cout << "\n-- Min dist : " << min_dist << endl;

	for (int i = 0; i < sz; i++)
	{
		if (matches[i].distance < 0.5*max_dist)//���ƴ�ƥ�����������
		{
			good_matches.push_back(matches[i]);
		}
	}

	cout << "��ƥ��������" << good_matches.size() << endl;
	//��������ƥ����

	Mat ShowGoodMatches;

	drawMatches(obj, obj_keypoints, scene, scene_keypoints, good_matches, ShowGoodMatches, Scalar::all(-1), Scalar::all(-1), Mat(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("goodMatches", ShowGoodMatches);
	imwrite("C_NewORB_RANSAC.png", ShowGoodMatches);


	int inliers = 0;
	for (size_t i1 = 0; i1 < points1.size(); i1++)  //���桮�ڵ㡯
	{
		if (norm(points2[i1] - points1t.at<Point2f>((int)i1, 0)) <= ransacReprojThreshold) //���ڵ������
		{
			matchesMask[i1] = 1;
			inliers++;
		}
	}


	Mat match_img2;   //�˳�����㡯��
	drawMatches(obj, obj_keypoints, scene, scene_keypoints, matches, match_img2, Scalar::all(-1), Scalar::all(-1), matchesMask,DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	cout << "�ڵ�������" << inliers << endl;
	//����Ŀ��λ��
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(obj.cols, 0);
	obj_corners[2] = cvPoint(obj.cols, obj.rows); obj_corners[3] = cvPoint(0, obj.rows);
	std::vector<Point2f> scene_corners(4);

	cout << "��Ӧ����Ϊ��" << H12 << endl;
	//perspectiveTransform(obj_corners, scene_corners, H12);
	//line(match_img2, scene_corners[0] + Point2f(static_cast<float>(obj.cols), 0),
	//	scene_corners[1] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);
	//line(match_img2, scene_corners[1] + Point2f(static_cast<float>(obj.cols), 0),
	//	scene_corners[2] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);
	//line(match_img2, scene_corners[2] + Point2f(static_cast<float>(obj.cols), 0),
	//	scene_corners[3] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);
	//line(match_img2, scene_corners[3] + Point2f(static_cast<float>(obj.cols), 0),
	//	scene_corners[0] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);

	imshow("�˳���ƥ���", match_img2);
	waitKey(0);

	return 0;
}
