//#include<iostream> // c++��׼ͷ�ļ�
//#include<stdio.h> // C���Ա�׼ͷ�ļ�������".h"
//#include<ctime>
//#include<opencv2/opencv.hpp>
//// �����ռ䣬����������Ⱦ  
//using namespace std;
//using namespace cv;
//class Girlfriend
//{
//	int d = 4; // Ĭ��˽������
//public:// ��������
//	int a = 1;
//	int age;
//	// ���캯��
//	Girlfriend() {
//		cout << "Ĭ�Ϲ��캯��" << endl;
//	}
//	Girlfriend(int age){
//		cout << "���������Ĺ��캯��" << endl;
//	}
//	void test(){}
//protected://��������
//	int b = 1;
//private: // ˽������
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
//	// ��ȡģ��ƥ����
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
