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
//	//��VideoCaptureʵ�����ٳ�ʼ��
//	//VideoCapture capture;
//	//capture.open("Megamind.avi");
//	//��VideoCaptureʵ������ͬʱ��ʼ��
//	VideoCapture capture("C:/Users/10310/Videos/Captures/A_GroupA.mp4");
//	if (!capture.isOpened())
//	{
//		return;
//	}
//	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
//	double frameRate = capture.get(CV_CAP_PROP_FPS);
//	double frameTime = 1 / frameRate;
//	cout << "��Ƶ��֡��:" << totalFrameNumber << endl;
//	cout << "��Ƶ֡��:" << frameRate << endl;
//	cout << "ÿ֡ͼ���ʱ��:" << frameTime<<"s" << endl;
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
