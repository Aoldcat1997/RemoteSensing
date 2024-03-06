#ifndef _SAR_SHIFT_H_
#define _SAR_SHIFT_H_

#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<iostream>

using namespace std;
using namespace cv;
//定义常量参数
const int SAR_SIFT_MAX_KEYPOINTS = 4000;//检测的特征点个数最大值，参见uniform robust sift

const int SAR_SIFT_LATERS = 8;//sar-sift算法尺度空间层数

const float SAR_SIFT_FACT_RADIUS_ORI = 6.0f;//计算主方向时候特征点邻域半径

const float SAR_SIFT_RADIUS_DES = 12.0f;//描述子邻域半径

const int SAR_SIFT_BORDER_CONSTANT = 2;//特征点检测时边界常量

const int SAR_SIFT_ORI_BINS = 36;//主方向直方图维度

const float SAR_SIFT_ORI_RATIO = 0.8f;//主方向直方图，峰值比例

/*原始sar-sift中GLOH在角度方向分为4个网格，8个网格效果更好*/
const int SAR_SIFT_GLOH_ANG_GRID = 8;//GLOH网格沿角度方向等分区间个数

const float SAR_SIFT_GLOH_RATIO_R1_R2 = 0.73f;//GLOH网格中间圆半径和外圆半径之比

const float SAR_SIFT_GLOH_RATIO_R1_R3 = 0.25f;//GLOH网格最内层圆半径和外圆半径之比

const int SAR_SIFT_DES_ANG_BINS = 8;//像素梯度方向在0-360度内等分区间个数

const float DESCR_MAG_THR = 0.2f;//描述子阈值

class shift
{
public:
	shift(int nFeature = 0, int Mmax = 8, double sigma = 2.0,
	double ratio = pow(2, 1.0 / 3),
	double threshold = 0.8, double d = 0.04) :
		nFeature(nFeature),Mmax(Mmax),sigma(sigma),ratio(ratio),
		threshold(threshold),d(d){}

	// 构建尺度空间
	void build_sar_shift_space(const Mat& image, vector<Mat>& sar_harris, vector<Mat>& gradient, vector<Mat>& orient);


	// 检测极值点 
	void find_space_extrema(const vector<Mat>& harris_fun, const vector<Mat>& amplit, const vector<Mat>& orient, vector<KeyPoint>& keys);

	// 计算特征点描述子
	void calc_descriptors(const vector<Mat>& amplit, const vector<Mat>& orient, const vector<KeyPoint>& keys, Mat& descriptors);

	// 检测特征点
	void detect_keys(const Mat& image, vector<KeyPoint>& keys, const vector<Mat>& amplit, const vector<Mat>& orient, Mat& des);
private:
	int nFeature; // 图像的像中采样的像素点个数
	int Mmax;// 尺度空间层数，默认是8
	double sigma;//初始值为2
	double ratio;// 相邻两层的尺度比
	double threshold; // 检测极值点的阈值
	double d = 0.04;
};
#endif