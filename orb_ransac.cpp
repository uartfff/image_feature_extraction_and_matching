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
	Mat obj = imread("E:/biyesheji/Main/imagePairs/A1.png");   //载入目标图像
	Mat scene = imread("C:/Users/10310/Desktop/010635.png"); //载入场景图像
	if (obj.empty() || scene.empty())
	{
		cout << "Can't open the picture!\n";
		return 0;
	}
	vector<KeyPoint> obj_keypoints, scene_keypoints;
	Mat obj_descriptors, scene_descriptors;
	//ORB detector;     //采用ORB算法提取特征点
	//ORB orb;
	Ptr<ORB> detector = ORB::create(200, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 50);
	//Ptr<ORB> detector1 = ORB::create(508);//控制图一的特征点数量(A1:534,B1:510,C1:568)
	//Ptr<ORB> detector2 = ORB::create(530);//控制图二的特征点数量(A2:610,B2:527,C2:590)
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
	//detector1->detectAndCompute(roi1, Mat(), obj_keypoints, obj_descriptors);//只对重叠区域做特征提取
	//detector2->detectAndCompute(roi2, Mat(), scene_keypoints, scene_descriptors);
	//for (int i = 0; i < obj_keypoints.size(); i++)
	//{
	//	obj_keypoints[i].pt.x += (obj.cols) / 2; //只对重叠区域做特征提取，所以到原图里面坐标横坐标需要增加图像宽度的1/2
	//}
	detect_finish = clock();
	cout << "特征点检测耗时：" << (double)(detect_finish - detect_start) / CLOCKS_PER_SEC << "s" << endl;

	Mat img1_with_features, img2_with_features;

	drawKeypoints(obj, obj_keypoints, img1_with_features);
	drawKeypoints(scene, scene_keypoints, img2_with_features);
	imshow("img1_with_features", img1_with_features);
	imwrite("imgC1_with_features_new.png", img1_with_features);
	imshow("img2_with_features", img2_with_features);
	imwrite("A.png", img2_with_features);

	BFMatcher matcher(NORM_HAMMING); //汉明距离做为相似度度量

	//匹配结果放在matches里面
	vector<DMatch> matches;
	vector<DMatch>good_matches;
	matcher.match(obj_descriptors, scene_descriptors, matches);

	cout << "图像1的特征点数" << obj_keypoints.size() << endl;
	cout << "图像2的特征点数" << scene_keypoints.size() << endl;
	cout << "特征匹配对数" << matches.size() << endl;

	//按照匹配关系将图画出来，背景图为match_img
	Mat match_img;
	drawMatches(obj, obj_keypoints, scene, scene_keypoints, matches, match_img);
	imshow("all_matches", match_img);
	//imwrite("C__NewORB_RANSAC.png", match_img);

	//保存匹配对序号
	vector<int> queryIdxs(matches.size()), trainIdxs(matches.size());
	for (size_t i = 0; i < matches.size(); i++)
	{
		queryIdxs[i] = matches[i].queryIdx;//取出查询图片中匹配的点对的索引即id号；那么queryIdxs、trainIdxs都为257
		trainIdxs[i] = matches[i].trainIdx;//取出训练图片中匹配的点对的索引即id号；
	}

	Mat H12;   //变换矩阵

	vector<Point2f> points1;
	KeyPoint::convert(obj_keypoints, points1, queryIdxs);//KeyPoint根据索引转point2f坐标
	vector<Point2f> points2;
	KeyPoint::convert(scene_keypoints, points2, trainIdxs);//同上
	int ransacReprojThreshold = 2;  //拒绝阈值,即重投影误差

	cout << "matches size = " << matches.size() << endl;
	H12 = findHomography(Mat(points1), Mat(points2), CV_RANSAC, ransacReprojThreshold);//计算单应矩阵
	vector<char> matchesMask(matches.size(), 0);//用于内点标记使用
	Mat points1t;
	perspectiveTransform(Mat(points1), points1t, H12);//对输入二维点做透视变换，变换后的结果保存在points1t中

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
		if (matches[i].distance < 0.5*max_dist)//控制粗匹配的特征点数
		{
			good_matches.push_back(matches[i]);
		}
	}

	cout << "粗匹配数量：" << good_matches.size() << endl;
	//画出良好匹配结果

	Mat ShowGoodMatches;

	drawMatches(obj, obj_keypoints, scene, scene_keypoints, good_matches, ShowGoodMatches, Scalar::all(-1), Scalar::all(-1), Mat(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("goodMatches", ShowGoodMatches);
	imwrite("C_NewORB_RANSAC.png", ShowGoodMatches);


	int inliers = 0;
	for (size_t i1 = 0; i1 < points1.size(); i1++)  //保存‘内点’
	{
		if (norm(points2[i1] - points1t.at<Point2f>((int)i1, 0)) <= ransacReprojThreshold) //给内点做标记
		{
			matchesMask[i1] = 1;
			inliers++;
		}
	}


	Mat match_img2;   //滤除‘外点’后
	drawMatches(obj, obj_keypoints, scene, scene_keypoints, matches, match_img2, Scalar::all(-1), Scalar::all(-1), matchesMask,DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	cout << "内点数量：" << inliers << endl;
	//画出目标位置
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(obj.cols, 0);
	obj_corners[2] = cvPoint(obj.cols, obj.rows); obj_corners[3] = cvPoint(0, obj.rows);
	std::vector<Point2f> scene_corners(4);

	cout << "单应矩阵为：" << H12 << endl;
	//perspectiveTransform(obj_corners, scene_corners, H12);
	//line(match_img2, scene_corners[0] + Point2f(static_cast<float>(obj.cols), 0),
	//	scene_corners[1] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);
	//line(match_img2, scene_corners[1] + Point2f(static_cast<float>(obj.cols), 0),
	//	scene_corners[2] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);
	//line(match_img2, scene_corners[2] + Point2f(static_cast<float>(obj.cols), 0),
	//	scene_corners[3] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);
	//line(match_img2, scene_corners[3] + Point2f(static_cast<float>(obj.cols), 0),
	//	scene_corners[0] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);

	imshow("滤除误匹配后", match_img2);
	waitKey(0);

	return 0;
}
