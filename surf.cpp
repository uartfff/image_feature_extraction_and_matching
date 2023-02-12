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
//using namespace cv;
//using namespace std;
//using namespace detail;
//int main(int argc, char** argv)
//{   Mat img = imread("C:/Users/10310/Desktop/IR16-1.png");    //����ͼ��      
//Ptr<FeaturesFinder> finder;    //����FeaturesFinder��    
//finder = new SurfFeaturesFinder();    //Ӧ��SURF����   
//									  
////finder = new OrbFeaturesFinder();    //Ӧ��ORB����    
//ImageFeatures features;    //��ʾ����    
//(*finder)(img, features);    //�������    
//Mat output_img;   //����drawKeypoints������������   
//drawKeypoints(img, features.keypoints, output_img, Scalar::all(-1));    
//namedWindow("features");   
//imshow("features", output_img);   
//imwrite("surffeature.png", output_img);
//waitKey(0);    
//return 0;
//}
