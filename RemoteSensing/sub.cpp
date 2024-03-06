//#include<opencv2/opencv.hpp>
//#include<iostream>
//
//using namespace std;
//using namespace cv;
//void function1(Mat& a, Mat& b);
//void function1(Mat & a,Mat & b)
//{
//	// 数组具有连续性
//	for (int i = 0; i <= 0; i++)
//	{
//		for (int j = 0; j < a.cols* a.rows; j++)
//		{
//			cout << "A1[" << i << "," << j << "]:" << (int)a.data[i, j] << endl;
//			a.data[i, j+i] = 3;
//			cout << "A1[" << i << "," << j << "]:" << (int)a.data[i, j] << endl;
//		}
//		
//	}
//	b = a;
//}
//void function2(Mat& a, Mat& b)
//{
//	for (int i = 0; i <= 0; i++)
//	{
//		for (int j = 0; j < a.cols * a.rows; j++)
//		{
//			cout << "A1[" << i << "," << j << "]:" << (int)a.data[i, j] << endl;
//			a.data[i, j + i] = 3;
//			cout << "A1[" << i << "," << j << "]:" << (int)a.data[i, j] << endl;
//		}
//
//	}
//	b = a;
//}
//int main()
//{
//    // CV_8SC1:CV_位深_通道
//	Mat A1(2,3, CV_8SC1, Scalar(1));
//	cout << "A1:\n" << A1 << endl;
//	Mat B1=-A1;
//	cout << "B1:\n" << B1 << endl;
//	cout << "B1:\n" << B1.data[0,0] << endl;
//	Mat B2;
//	// c++利用引用来传递与修改变量参数
//	function1(A1,B2);
//	cout << "A1:\n" << B2 << endl;
//	return 0;
//}