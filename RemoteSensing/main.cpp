#include<opencv2\features2d\features2d.hpp>// ������ȡ��
#include<opencv2/highgui/highgui.hpp>// ��������
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgproc/types_c.h>// ͼ�����
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	string path1 = "E:\\opencv\\Image-Registration\\test images\\PA-1.jpg"; // ��һ���ַ������� 
	string path2 = "E:\\opencv\\Image-Registration\\test images\\PA-2.jpg"; // �ڶ����ַ�������  
	string transtype = "similarity";// �ڶ����ַ�������
	// �жϱ任����
	if (string(transtype) != string("similarity") && string(transtype) != string("perspective") && string(transtype) != string("affine"))
	{
		cout << "����任���ʹ���" << endl;
		return -1;
	}
	// ��ȡӰ��
	Mat image1 = imread(path1, -1);
	Mat image2 = imread(path2, -1);
	// �ж϶�ȡӰ���Ƿ�ɹ�
	if (image1.empty() && image2.empty())
	{
		cout << "ͼ�����ݼ���ʧ�ܣ�" << endl;
		return -1;
	}
	// �㷨��ʱ
	double total_beg = (double)getTickCount();//

	//ͼ���С
	int nums_1 = image1.rows * image1.cols;
	int nums_2 = image2.rows * image2.cols;

	// ��ʼ������������
	int nFeature1 = cvRound((double)nums_1 * 0.008);
	int nFeature2 = cvRound((double)nums_2 * 0.008);


	return 0;
}
