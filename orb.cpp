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
//	//ORB�㷨��Ŀ������ǻҶ�ͼ��
//
//	cvtColor(img_1, d_srcL, COLOR_BGR2GRAY);//CPU���ORB�㷨Դ�����Դ�������ͼ��ҶȻ����˲���ʡ��
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
//	//���ùؼ�����ƥ�䷽ʽΪNORM_L2��������ʹ�� FLANNBASED = 1, BRUTEFORCE = 2, BRUTEFORCE_L1 = 3, BRUTEFORCE_HAMMING = 4, BRUTEFORCE_HAMMINGLUT = 5, BRUTEFORCE_SL2 = 6 
//
//
//	BFMatcher d_matcher(NORM_HAMMING);
//
//
//	std::vector<DMatch> matches;//��ͨƥ��
//
//	std::vector<DMatch> good_matches;//ͨ��keyPoint֮�����ɸѡƥ��ȸߵ�ƥ����
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
//	//��ȡ����ƥ�������ڴ���ͼƬ�ϵĵ㼯��ȷ��ƥ��Ĵ��λ��
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
//	//������ͨƥ����
//
//	Mat ShowMatches;
//
//	drawMatches(img_1, keyPoints_1, img_2, keyPoints_2, matches, ShowMatches);
//
//	imshow("matches", ShowMatches);
//
//	imwrite("matches.png", ShowMatches);
//
//	//��������ƥ����
//
//	Mat ShowGoodMatches;
//
//	drawMatches(img_1, keyPoints_1, img_2, keyPoints_2, good_matches, ShowGoodMatches);
//
//	imshow("good_matches", ShowGoodMatches);
//
//	imwrite("good_matches.png", ShowGoodMatches);
//
//	//��������ƥ�������ڴ���ͼƬ�ϵĵ㼯
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
