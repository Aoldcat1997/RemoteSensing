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
//	////opencv �б����ʽ��
//	//template<typename _Tp, int cn>;
//	//��һ���Ǳ������ͣ��ڶ����Ǹ�����
//	//	eg��һЩ������Ѿ����˱���
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
//	// �ɱ�����ģ���࣬
//	vector<Vec4i> hierarchy;
//	hierarchy.push_back(temp1);// ���Ԫ��
//	hierarchy.push_back(temp2);// ���Ԫ��
//	cout << "temp1��" << hierarchy[0] << endl;
//	cout << "temp1��һ��Ԫ��" << hierarchy[0][0] << endl;
//	cout << "hierarchy�Ĵ�С" << hierarchy.size() << endl;
//	cout << "---------------------" << endl;
//	//Point p;
//	//p = { 1,2 };
//	//cout << "P:" << p << endl;
//	//cout << "---------------------" << endl;
//	Point p(0, 1), p1(0, 2), p3(1, 4);
//	cout << "p:" << p << endl;
//	p = { 1,2 };
//	cout << "P:" << p << endl;
//	// vector������opencv������STD�е�һ������
//	vector<Point> pArray;
//	pArray.push_back(p);
//	pArray.push_back(p1);
//	pArray.push_back(p3);
//
//	cout << pArray.size() << endl;//���Ϊ3
//	cout << pArray.at(0) << endl; //���Ϊ{1,2}
//	cout << pArray.at(1) << endl; //���Ϊ{0,2}
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