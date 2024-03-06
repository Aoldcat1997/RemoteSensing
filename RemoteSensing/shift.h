#ifndef _SAR_SHIFT_H_
#define _SAR_SHIFT_H_

#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<iostream>

using namespace std;
using namespace cv;
//���峣������
const int SAR_SIFT_MAX_KEYPOINTS = 4000;//����������������ֵ���μ�uniform robust sift

const int SAR_SIFT_LATERS = 8;//sar-sift�㷨�߶ȿռ����

const float SAR_SIFT_FACT_RADIUS_ORI = 6.0f;//����������ʱ������������뾶

const float SAR_SIFT_RADIUS_DES = 12.0f;//����������뾶

const int SAR_SIFT_BORDER_CONSTANT = 2;//��������ʱ�߽糣��

const int SAR_SIFT_ORI_BINS = 36;//������ֱ��ͼά��

const float SAR_SIFT_ORI_RATIO = 0.8f;//������ֱ��ͼ����ֵ����

/*ԭʼsar-sift��GLOH�ڽǶȷ����Ϊ4������8������Ч������*/
const int SAR_SIFT_GLOH_ANG_GRID = 8;//GLOH�����ؽǶȷ���ȷ��������

const float SAR_SIFT_GLOH_RATIO_R1_R2 = 0.73f;//GLOH�����м�Բ�뾶����Բ�뾶֮��

const float SAR_SIFT_GLOH_RATIO_R1_R3 = 0.25f;//GLOH�������ڲ�Բ�뾶����Բ�뾶֮��

const int SAR_SIFT_DES_ANG_BINS = 8;//�����ݶȷ�����0-360���ڵȷ��������

const float DESCR_MAG_THR = 0.2f;//��������ֵ

class shift
{
public:
	shift(int nFeature = 0, int Mmax = 8, double sigma = 2.0,
	double ratio = pow(2, 1.0 / 3),
	double threshold = 0.8, double d = 0.04) :
		nFeature(nFeature),Mmax(Mmax),sigma(sigma),ratio(ratio),
		threshold(threshold),d(d){}

	// �����߶ȿռ�
	void build_sar_shift_space(const Mat& image, vector<Mat>& sar_harris, vector<Mat>& gradient, vector<Mat>& orient);


	// ��⼫ֵ�� 
	void find_sapce_extream(const vector<Mat>& harris_fun, const vector<Mat>& amplit, const vector<Mat>& orient, vector<KeyPoint>& keys);

	// ����������������
	void calc_descriptors(const vector<Mat>& amplit, const vector<Mat>& orient, const vector<KeyPoint>& keys, Mat& descriptors);

	// ���������
	void detect_keys(const Mat& image, vector<KeyPoint>& keys, const vector<Mat>& amplit, const vector<Mat>& orient, Mat& des);
private:
	int nFeature; // ͼ������в��������ص����
	int Mmax;// �߶ȿռ������Ĭ����8
	double sigma;//��ʼֵΪ2
	double ratio;// ��������ĳ߶ȱ�
	double threshold; // ��⼫ֵ�����ֵ
	double d = 0.04;
};
#endif