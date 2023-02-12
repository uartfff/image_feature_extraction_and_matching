//#include <opencv2/opencv.hpp>
//#include <tchar.h> 
//#include <stdio.h>  
//#include <iostream>  
//#include <math.h>  
//#include <ostream> 
//using namespace std;
//using namespace cv;
//void main()
//{
//	//类VideoCapture实例化再初始化
//	//VideoCapture capture;
//	//capture.open("Megamind.avi");
//	//类VideoCapture实例化的同时初始化
//	VideoCapture capture("C:/Users/10310/Videos/Captures/A_GroupA.mp4");
//	if (!capture.isOpened())
//	{
//		return;
//	}
//	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
//	double frameRate = capture.get(CV_CAP_PROP_FPS);
//	double frameTime = 1 / frameRate;
//	cout << "视频总帧数:" << totalFrameNumber << endl;
//	cout << "视频帧率:" << frameRate << endl;
//	cout << "每帧图像的时长:" << frameTime<<"s" << endl;
//	int imgIndex = 0;
//	for (;;)
//	{
//		Mat frame;capture >> frame;
//		if (frame.empty())
//		{
//			break;
//		}
//		imgIndex++;
//		
//		imshow("singleFrame", frame);
//		int a = 0;
//	}
//}
