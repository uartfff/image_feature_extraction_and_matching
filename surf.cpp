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
//{   Mat img = imread("C:/Users/10310/Desktop/IR16-1.png");    //读入图像      
//Ptr<FeaturesFinder> finder;    //定义FeaturesFinder类    
//finder = new SurfFeaturesFinder();    //应用SURF方法   
//									  
////finder = new OrbFeaturesFinder();    //应用ORB方法    
//ImageFeatures features;    //表示特征    
//(*finder)(img, features);    //特征检测    
//Mat output_img;   //调用drawKeypoints函数绘制特征   
//drawKeypoints(img, features.keypoints, output_img, Scalar::all(-1));    
//namedWindow("features");   
//imshow("features", output_img);   
//imwrite("surffeature.png", output_img);
//waitKey(0);    
//return 0;
//}
