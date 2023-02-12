//#include "opencv2/core/core.hpp"
//#include "highgui.h"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/nonfree/nonfree.hpp"
//#include "opencv2/legacy/legacy.hpp" 
//#include "opencv2/stitching/detail/autocalib.hpp"
//#include "opencv2/stitching/detail/blenders.hpp"
//#include "opencv2/stitching/detail/camera.hpp"
//#include "opencv2/stitching/detail/exposure_compensate.hpp"
//#include "opencv2/stitching/detail/matchers.hpp"
//#include "opencv2/stitching/detail/motion_estimators.hpp"
//#include "opencv2/stitching/detail/seam_finders.hpp"
//#include "opencv2/stitching/detail/util.hpp"
//#include "opencv2/stitching/detail/warpers.hpp"
//#include "opencv2/stitching/warpers.hpp" 
//#include <iostream>
//#include <fstream> 
//#include <string>
//#include <iomanip> 
//#include<vector>
//using namespace cv;
//using namespace std;
//using namespace detail; 
//int main(int argc, char** argv)
//{      
//	vector<Mat> imgs;    //表示待拼接的图像矢量队列   
//	Mat img = imread("E:/biyesheji/Main/imagePairs/A1.png");    //读取两幅图像，并存入队列   
//	imgs.push_back(img);   
//	img = imread("E:/biyesheji/Main/imagePairs/A2.png");   
//	imgs.push_back(img);    
//	Ptr<FeaturesFinder> finder;    //特征检测
//
//	clock_t feature_find_time1, feature_find_time2;
//
//	/*finder = new SurfFeaturesFinder();*/
//	finder = new OrbFeaturesFinder();
//	vector<ImageFeatures> features(2);
//
//	feature_find_time1 = clock();
//
//	(*finder)(imgs[0], features[0]);
//
//	//feature_find_time2 = clock();
//
//	(*finder)(imgs[1], features[1]); 
//
//	cout << "图像1的特征点数量：" << features[0].keypoints.size() << endl;
//	cout << "图像2的特征点数量：" << features[1].keypoints.size() << endl;
//
//	//cout << "特征点检测耗时：" << (double)(feature_find_time2 - feature_find_time1) / CLOCKS_PER_SEC << "s" << endl;
//
//	vector<Mat>img_with_features(2);
//	for (int i = 0; i < 2; i++)
//	{
//		drawKeypoints(imgs[i], features[i].keypoints, img_with_features[i], Scalar(0, 0, 255));
//		namedWindow("img" + to_string(i + 1) + "WithFeatures");
//		imshow("img" + to_string(i + 1) + "WithFeatures", img_with_features[i]);
//		imwrite("img" + to_string(i + 1) + "WithFeatures.png", img_with_features[i]);
//	}
//
//	vector<MatchesInfo> pairwise_matches;    //特征匹配   
//	BestOf2NearestMatcher matcher(false, 0.2f);    //定义特征匹配器，2NN方法   
//	matcher(features, pairwise_matches);    //进行特征匹配   
//
//	feature_find_time2 = clock();
//	cout << "特征点检测耗时：" << (double)(feature_find_time2 - feature_find_time1) / CLOCKS_PER_SEC << "s" << endl;
//	Mat dispimg;    //两幅图像合并成一幅图像显示   
//	dispimg.create(Size(imgs[0].cols+imgs[1].cols, max(imgs[1].rows,imgs[1].rows)), CV_8UC3);  
//	Mat imgROI = dispimg(Rect(0, 0, (int)(imgs[0].cols), (int)(imgs[0].rows)));     
//	resize(imgs[0], imgROI, Size((int)(imgs[0].cols), (int)(imgs[0].rows)));    
//	imgROI = dispimg(Rect((int)(imgs[0].cols), 0, (int)(imgs[1].cols), (int)(imgs[1].rows)));     
//	resize(imgs[1], imgROI, Size((int)(imgs[1].cols), (int)(imgs[1].rows)));	  
//	Point2f p1, p2;    //分别表示两幅图像内的匹配点对   
//	int j=0;   
//	for (size_t i = 0; i < pairwise_matches[1].matches.size(); ++i)    //遍历匹配点对   
//	{     
//		if (!pairwise_matches[1].inliers_mask[i])    //不是内点，则继续下一次循环         
//			continue;       
//		const DMatch& m = pairwise_matches[1].matches[i];    //得到内点的匹配点对      
//		p1 = features[0].keypoints[m.queryIdx].pt;      
//		p2 = features[1].keypoints[m.trainIdx].pt;     
//		p2.x += features[0].img_size.width;    //p2在合并图像上的坐标             
//		line(dispimg, p1, p2, Scalar(0,0,255), 1, CV_AA);    //画直线       
//		//if(j++==10)    //内点数量较多，我们只显示10个        
//		//	break;   
//	}    //在终端显示内点数量和单应矩阵  
//	cout << "内点数量：" << endl;
//	cout << pairwise_matches[1].num_inliers << endl;
//	cout<<"好的匹配的数量："<<endl;   
//	cout<<pairwise_matches[1].matches.size()<<endl<<endl;    
//	const double* h = reinterpret_cast<const double*>(pairwise_matches[1].H.data);   
//	cout<<"单应矩阵："<<endl;
//	/*for (int i = 0; i < 9; i++)
//	{
//		cout << *(h + i) << ',';
//		if ((i + 1) % 3 == 0)
//			cout << endl;
//	}*/
//	cout<<setw(10)<<(int)(h[0]+0.5)<<setw(6)<<(int)(h[1]+0.5)<<setw(6)<<(int)(h[2]+0.5)<<endl;  
//	cout<<setw(10)<<(int)(h[3]+0.5)<<setw(6)<<(int)(h[4]+0.5)<<setw(6)<<(int)(h[5]+0.5)<<endl;  
//	cout<<setw(10)<<(int)(h[6]+0.5)<<setw(6)<<(int)(h[7]+0.5)<<setw(6)<<(int)(h[8]+0.5)<<endl;    
//	imshow("匹配显示", dispimg);    //显示匹配图像
//	imwrite("ransacMatch.png", dispimg);
//	waitKey(0);    
//	return 0;
//}
