//#include<iostream>
//#include <opencv2/core/utility.hpp>
//
//
//
//using namespace std;
//using namespace cv;
//int main()
//
//{
//	////opencv 中表达形式是
//	//template<typename _Tp, int cn>;
//	//第一个是变量类型，第二个是个数。
//	//	eg：一些特殊的已经做了别名
//	//	typedef Vec<int, 4> Vec4i;
//	Vec4i int4, temp;
//	temp = { 2,3,4,5 };
//	int4 = {1,2,3,4};
//	cout << "int4:" << int4 << endl;
//	int4[0] = 0;
//	cout << "temp:" << temp << endl;
//	cout << "int4:" << int4 << endl;
//	cout << "int4+temp:" << int4 + temp << endl;
////int4: [1, 2, 3, 4]
////temp : [2, 3, 4, 5]
////int4 : [0, 2, 3, 4]
////int4 + temp : [2, 5, 7, 9]
//	cout << "---------------------"  << endl;
//	Vec4i temp1, temp2;
//	temp1 = { 2,3,4,5 };
//	temp2 = { 1,2,3,4 };
//	// 可变数组模版类，
//	vector<Vec4i> hierarchy;
//	hierarchy.push_back(temp1);// 添加元素
//	hierarchy.push_back(temp2);// 添加元素
//	cout << "temp1：" << hierarchy[0] << endl;
//	cout << "temp1第一个元素" << hierarchy[0][0] << endl;
//	cout << "hierarchy的大小" << hierarchy.size() << endl;
//	cout << "---------------------" << endl;
//	//Point p;
//	//p = { 1,2 };
//	//cout << "P:" << p << endl;
//	//cout << "---------------------" << endl;
//	Point p(0, 1), p1(0, 2), p3(1, 4);
//	cout << "p:" << p << endl;
//	p = { 1,2 };
//	cout << "P:" << p << endl;
//	// vector不属于opencv，他是STD中的一个容器
//	vector<Point> pArray;
//	pArray.push_back(p);
//	pArray.push_back(p1);
//	pArray.push_back(p3);
//
//	cout << pArray.size() << endl;//输出为3
//	cout << pArray.at(0) << endl; //输出为{1,2}
//	cout << pArray.at(1) << endl; //输出为{0,2}
//	
//	cout << "---------------------" << endl;
//	vector<Point> pArrary, pArrary1, pArrary2;
//
//	pArrary.push_back(p);
//	pArrary.push_back(p1);
//	pArrary.push_back(p3);
//
//
//	pArrary1.push_back(p1);
//	pArrary2.push_back(p3);
//
//	vector<vector<Point>> contours;
//	contours.push_back(pArrary);
//	contours.push_back(pArrary1);
//	contours.push_back(pArrary2);
//	cout << contours.at(0) << endl;
//	cout << contours.size() << endl;
//
//	return 0;
//}