#ifndef _SAR_SHIFT_H_
#define _SAR_SHIFT_H_

#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<iostream>

using namespace std;
using namespace cv;












class shift
{
public:
	shift(int nFeature = 0, int Mmax = 8, double sigma = 2.0,
	double ratio = pow(2, 1.0 / 3),
	double threshold = 0.8, double d = 0.04) :
		nFeature(nFeature),Mmax(Mmax),sigma(sigma),ratio(ratio),
		threshold(threshold),d(d){}

	void build_sar_shift_space(const Mat& image, vector<Mat>& sar_harris, vector<Mat>& gradient, vector<Mat>& orient);



	void calc_descriptors(const vector<Mat>& amplit, const vector<Mat>& orient, const vector<KeyPoint>& keys, Mat& descriptors);

	void detect_keys(const Mat& image, vector<KeyPoint>& keys, const vector<Mat>& amplit, const vector<Mat>& orient, Mat& des);
private:
	double d = 0.04;
};
#endif