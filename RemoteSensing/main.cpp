#include<opencv2\features2d\features2d.hpp>// 特征提取库
#include<opencv2/highgui/highgui.hpp>// 交互窗口
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgproc/types_c.h>// 图像处理库
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	string path1 = "E:\\opencv\\Image-Registration\\test images\\PA-1.jpg"; // 第一个字符串参数 
	string path2 = "E:\\opencv\\Image-Registration\\test images\\PA-2.jpg"; // 第二个字符串参数  
	string transtype = "similarity";// 第二个字符串参数
	// 判断变换类型
	if (string(transtype) != string("similarity") && string(transtype) != string("perspective") && string(transtype) != string("affine"))
	{
		cout << "输入变换类型错误" << endl;
		return -1;
	}
	// 读取影像
	Mat image1 = imread(path1, -1);
	Mat image2 = imread(path2, -1);
	// 判断读取影像是否成功
	if (image1.empty() && image2.empty())
	{
		cout << "图像数据加载失败！" << endl;
		return -1;
	}
	// 算法计时
	double total_beg = (double)getTickCount();//

	//图像大小
	int nums_1 = image1.rows * image1.cols;
	int nums_2 = image2.rows * image2.cols;

	// 初始化特征点检测类
	int nFeature1 = cvRound((double)nums_1 * 0.008);
	int nFeature2 = cvRound((double)nums_2 * 0.008);


	return 0;
}
