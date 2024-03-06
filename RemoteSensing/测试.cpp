//#include<iostream> // c++标准头文件
//#include<stdio.h> // C语言标准头文件，包含".h"
//#include<ctime>
//#include<opencv2/opencv.hpp>
//// 命名空间，避免命名污染  
//using namespace std;
//using namespace cv;
//class Girlfriend
//{
//	int d = 4; // 默认私有属性
//public:// 共有属性
//	int a = 1;
//	int age;
//	// 构造函数
//	Girlfriend() {
//		cout << "默认构造函数" << endl;
//	}
//	Girlfriend(int age){
//		cout << "包含参数的构造函数" << endl;
//	}
//	void test(){}
//protected://保护属性
//	int b = 1;
//private: // 私有属性
//	int c = 1;
//};
//class Match {
//public:
//	Mat img_1;
//	Mat img_2;
//	Mat img_3;
//	Match()
//	{
//		Mat img_1 = imread("");
//		Mat img_2 = imread("");
//	}
//	// 获取模版匹配结果
//	void GetTemplateMatch()
//	{
//		matchTemplate(img_1, img_2, img_3,5);
//		double maxVal, minVal;
//		// double minLoc, manLoc;
//		minMaxLoc(img_3, &maxVal, &minVal, &minLoc, &maxLoc);
//		rectangle(img_1, Rect(maxLoc.x,maxLoc.y,img_3.cols,img_3.rows),Scalar(0,0,255),2);
//
//
//	}
//	void show()
//	{
//		imshow("im1", img_1);
//		imshow("im2", img_2);
//		waitKey(100);
//	}
//};
//int main()
//{
//	Girlfriend mm;
//	Girlfriend MM1;
//	Girlfriend* p = new Girlfriend(12);
//	p->test();
//
//	return 0;
//}
