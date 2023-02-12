//#include "gms_matcher.h"
//
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
//	Mat img1 = imread("E:/biyesheji/Main/imagePairs/C1.png");
//	Mat img2 = imread("E:/biyesheji/Main/imagePairs/C2.png");
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
//	//create()���ĸ�������FAST����������ֵ��Ĭ��ֵ31
//	Ptr<ORB> orb1 = ORB::create(508);//����ͼһ������������(A1:534,B1:510,C1:568)
//	Ptr<ORB> orb2 = ORB::create(530);//����ͼ��������������(A2:610,B2:527,C2:590)
//
//	orb1->setFastThreshold(0);
//	orb2->setFastThreshold(0);
//	
//	clock_t feature_find_time1, feature_find_time2;
//
//	feature_find_time1 = clock();
//
//	orb1->detectAndCompute(roi1, Mat(), kp1, d1);//ֻ���ص�������������ȡ
//	orb2->detectAndCompute(roi2, Mat(), kp2, d2);
//	for (int i = 0; i < kp1.size(); i++)
//	{
//		kp1[i].pt.x += (img1.cols) / 2; //ֻ���ص�������������ȡ�����Ե�ԭͼ���������������Ҫ����ͼ���ȵ�1/2
//	}
//	//orb1->detectAndCompute(img1, Mat(), kp1, d1);//��img1ȫͼ��ORB������ȡ
//	//orb2->detectAndCompute(img2, Mat(), kp2, d2);//��img2ȫͼ��ORB������ȡ
//
//	feature_find_time2 = clock();
//	cout << "���������ʱ��" << (double)(feature_find_time2 - feature_find_time1) / CLOCKS_PER_SEC << "s" << endl;
//	cout << "ͼ1������������kp1��" << kp1.size() << endl;
//	cout << "ͼ2������������kp2��" << kp2.size() << endl;
//
//	Mat show1, show2;
//	drawKeypoints(img1, kp1, show1);
//	imshow("IORBfeatures1", show1);
//	//imwrite("IORBfeatures1.png", show1);
//	drawKeypoints(img2, kp2, show2);
//	imshow("IORBfeatures2", show2);
//	//imwrite("IORBfeatures2.png", show2);
//
//#ifdef USE_GPU
//	GpuMat gd1(d1), gd2(d2);
//	Ptr<cuda::DescriptorMatcher> matcher = cv::cuda::DescriptorMatcher::createBFMatcher(NORM_HAMMING);
//	matcher->match(gd1, gd2, matches_all);
//#else
//	clock_t t1, t2;
//	t1 = clock();
//	BFMatcher matcher(NORM_HAMMING);
//	matcher.match(d1, d2, matches_all);
//	t2 = clock();
//	cout << "����ƥ���ʱ��" << (double)(t2 - t1) / CLOCKS_PER_SEC << "s" << endl;
//#endif
//
//	cout << "ƥ��������"<<matches_all.size() << endl;
//	// GMS filter
//	std::vector<bool> vbInliers;
//	clock_t start, finish;
//	start = clock();
//	gms_matcher gms(kp1, img1.size(), kp2, img2.size(), matches_all);
//	/*finish = clock();
//	cout << "GMS��ʱ��" << (double)(finish - start) / CLOCKS_PER_SEC <<"s"<< endl;*/
//
//	int num_inliers = gms.GetInlierMask(vbInliers, false, false);
//	finish = clock();
//	cout << "GMS consumes��" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
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
//	////����GMS�õ��ڵ��������RANSAC���㵥Ӧ����
//	//vector<int> queryIdxs(matches_gms.size()), trainIdxs(matches_gms.size());
//	//for (size_t i = 0; i < matches_gms.size(); i++)
//	//{
//	//	queryIdxs[i] = matches_gms[i].queryIdx;//ȡ����ѯͼƬ��ƥ��ĵ�Ե�������id�ţ���ôqueryIdxs��trainIdxs��Ϊ257
//	//	trainIdxs[i] = matches_gms[i].trainIdx;//ȡ��ѵ��ͼƬ��ƥ��ĵ�Ե�������id�ţ�
//	//}
//
//	//vector<Point2f>points1, points2;
//	//KeyPoint::convert(kp1, points1, queryIdxs);
//	//KeyPoint::convert(kp2, points2, trainIdxs);
//
//	//Mat homoMat;
//
//	//homoMat = findHomography(Mat(points1), Mat(points2), CV_RANSAC);//���㵥Ӧ����
//
//	//vector<Point2f>img1_corners(4);
//	//img1_corners[0] = cvPoint(0, 0); img1_corners[1] = cvPoint(img1.cols, 0);
//	//img1_corners[2] = cvPoint(0, img1.rows); img1_corners[3] = cvPoint(img1.cols, img1.rows);
//
//	//vector<Point2f>img1_wraped_corners(4);
//	//perspectiveTransform(img1_corners, img1_wraped_corners, homoMat);
//
//	//Mat img1_wrap;
//	//
//	//float xOffset=0, yOffset=0;
//	//for (int i = 0; i < 4; i++)
//	//{
//	//	if (img1_wraped_corners[i].x < xOffset)
//	//		xOffset = img1_wraped_corners[i].x;
//	//	if (img1_wraped_corners[i].y < yOffset)
//	//		yOffset = img1_wraped_corners[i].y;
//	//}
//
//	//cout << "xOffset��" << xOffset << endl;
//	//cout << "yOffset��" << yOffset << endl;
//
//	//Mat transMat = Mat::eye(3, 3, CV_64FC1);
//	//transMat.at<double>(0, 2) = -xOffset;
//	//transMat.at<double>(1, 2) = -yOffset;
//
//	//homoMat = transMat * homoMat;
//	//warpPerspective(img1, img1_wrap, homoMat, Size(1.5*img1.cols,15*img1.rows));
//	//imshow("img1_wrap", img1_wrap);
//
//	// draw matching
//	Mat show = DrawInlier(img1, img2, kp1, kp2, matches_gms, 1);
//	//Mat showMatch;
//	//drawMatches(img1, kp1, img2, kp2, matches_gms, showMatch, Scalar(0,0,255), Scalar(0,0,255), Mat(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
//	//namedWindow("show", 0);
//	//cvResizeWindow("show", img1.cols / 4, img1.rows / 8);
//	imshow("show", show);
//	imwrite("C_NewORB_GMS.png", show);
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
