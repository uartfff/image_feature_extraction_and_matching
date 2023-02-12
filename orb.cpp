//
//#include <iostream>
//
//#include <signal.h>
//
//#include <vector>
//
//
//
//#include <opencv2/opencv.hpp>
//
//
//
//using namespace cv;
//
//using namespace std;
//
//
//
//
//
//int main()
//
//{
//
//	Mat img_1 = imread("E:/biyesheji/Main/imagePairs/B1.png");
//
//	Mat img_2 = imread("E:/biyesheji/Main/imagePairs/B2.png");
//
//
//
//	if (!img_1.data || !img_2.data)
//
//	{
//
//		cout << "error reading images " << endl;
//
//		return -1;
//
//	}
//
//
//
//	vector<Point2f> recognized;
//
//	vector<Point2f> scene;
//
//
//
//	recognized.resize(500);
//
//	scene.resize(500);
//
//
//
//	Mat d_srcL, d_srcR;
//
//
//
//	Mat img_matches, des_L, des_R;
//
//	//ORB算法的目标必须是灰度图像
//
//	cvtColor(img_1, d_srcL, COLOR_BGR2GRAY);//CPU版的ORB算法源码中自带对输入图像灰度化，此步可省略
//
//	cvtColor(img_2, d_srcR, COLOR_BGR2GRAY);
//
//
//
//	Ptr<ORB> d_orb = ORB::create(300);
//	d_orb->setFastThreshold(0);
//
//
//	Mat d_descriptorsL, d_descriptorsR, d_descriptorsL_32F, d_descriptorsR_32F;
//
//
//
//	vector<KeyPoint> keyPoints_1, keyPoints_2;
//
//
//
//	//设置关键点间的匹配方式为NORM_L2，更建议使用 FLANNBASED = 1, BRUTEFORCE = 2, BRUTEFORCE_L1 = 3, BRUTEFORCE_HAMMING = 4, BRUTEFORCE_HAMMINGLUT = 5, BRUTEFORCE_SL2 = 6 
//
//
//	BFMatcher d_matcher(NORM_HAMMING);
//
//
//	std::vector<DMatch> matches;//普通匹配
//
//	std::vector<DMatch> good_matches;//通过keyPoint之间距离筛选匹配度高的匹配结果
//
//
//
//	d_orb->detectAndCompute(d_srcL, Mat(), keyPoints_1, d_descriptorsL);
//
//
//
//	d_orb->detectAndCompute(d_srcR, Mat(), keyPoints_2, d_descriptorsR);
//
//
//
//	d_matcher.match(d_descriptorsL, d_descriptorsR, matches);
//
//	/*cout << "matches:" << matches.size() << endl;*/
//
//
//
//
//	int sz = matches.size();
//
//	double max_dist = 0; double min_dist = 100;
//
//
//
//	for (int i = 0; i < sz; i++)
//
//	{
//
//		double dist = matches[i].distance;
//
//		if (dist < min_dist) min_dist = dist;
//
//		if (dist > max_dist) max_dist = dist;
//
//	}
//
//
//
//	cout << "\n-- Max dist : " << max_dist << endl;
//
//	cout << "\n-- Min dist : " << min_dist << endl;
//
//
//
//	for (int i = 0; i < sz; i++)
//
//	{
//
//		if (matches[i].distance < 0.6*max_dist)
//
//		{
//
//			good_matches.push_back(matches[i]);
//
//		}
//
//	}
//
//	//提取良好匹配结果中在待测图片上的点集，确定匹配的大概位置
//
//	for (size_t i = 0; i < good_matches.size(); ++i)
//
//	{
//
//		scene.push_back(keyPoints_2[good_matches[i].trainIdx].pt);
//
//	}
//
//
//
//	for (unsigned int j = 0; j < scene.size(); j++)
//
//		cv::circle(img_2, scene[j], 2, cv::Scalar(0, 255, 0), 2);
//
//	//画出普通匹配结果
//
//	Mat ShowMatches;
//
//	drawMatches(img_1, keyPoints_1, img_2, keyPoints_2, matches, ShowMatches);
//
//	imshow("matches", ShowMatches);
//
//	imwrite("matches.png", ShowMatches);
//
//	//画出良好匹配结果
//
//	Mat ShowGoodMatches;
//
//	drawMatches(img_1, keyPoints_1, img_2, keyPoints_2, good_matches, ShowGoodMatches);
//
//	imshow("good_matches", ShowGoodMatches);
//
//	imwrite("good_matches.png", ShowGoodMatches);
//
//	//画出良好匹配结果中在待测图片上的点集
//
//	imshow("MatchPoints_in_img_2", img_2);
//
//	imwrite("MatchPoints_in_img_2.png", img_2);
//
//	cout << "matches:" << matches.size() << endl; 
//	cout << "good_matches:" << good_matches.size() << endl;
//
//	waitKey(0);
//
//
//
//	return 0;
//
//}
