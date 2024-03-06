#include"shift.h"
#include<opencv2\features2d\features2d.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2\imgproc\types_c.h>
#include<vector>

/*********�ú������ݳ߶Ⱥʹ��ڰ뾶����ROEWA�˲�ģ��************/
/*size��ʾ�˰뾶����˺˿����2*size+1
 scale��ʾָ��Ȩ�ز���
 kernel��ʾ���ɵ��˲���
 */

static void roewa_kernal(int size, float scale, Mat& kernal)
{
	kernal.create(2 * size + 1, 2 * size + 1, CV_32FC1);
	for (int i = -size; i <= size; ++i)
	{
		// ��i + size��Ŀ���ǽ�������Χ��[0, 2 * size]ӳ�䵽[-size, size]��
		float* ptr_k = kernal.ptr<float>(i + size);
		for (int j = -size; j <= size; ++j)
		{
			ptr_k[j + size] = exp(-1.f * (abs(i) + abs(j)) / scale);
	
		}
	}
}

/*�ú������ݴ��ڰ뾶����׼�����Բ�θ�˹�˲�ģ�壬����������*/
/*size��ʾԲ�뾶
 scale��ʾ��˹��׼��
 gauss_kernel��ʾ���ɵ�Բ�θ�˹��
 ��ά��˹��������ʽ��1/(2*pi*scale*scale)*exp(-(x*x+y*y)/(2*scale*scale))
 */

static void gauss_circle(int size, float scale, Mat& gauss_kernal)
{
	gauss_kernal.create(2 * size + 1, 2 * size + 1, CV_32FC1);
	float exp_temp = -1.f / (2 * scale * scale);
	float sum = 0;
	for (int i = -size; i <= size; ++i)
	{
		float* ptr = gauss_kernal.ptr<float>(i + size);
		for (int j = -size; j <= size; ++j)
		{
			if ((i * i + j * j) <= size * size)
			{
				float value = exp((i * i + j * j) * exp_temp);
				sum += value;
				ptr[j + size] = value;
			}
			else
				ptr[j + size] = 0.f;
		}
	}

	for (int i = -size; i <= size; ++i)
	{
		float* ptr = gauss_kernal.ptr<float>(i + size);
		for (int j = -size; j <= size; ++j)
		{
			ptr[j + size] = ptr[j + size] / sum;
		}
	}
}

/*************�����Ա��������SAR_SIFT�߶ȿռ�*****************/
/*image��ʾ�����ԭʼͼ��
 sar_harris_fun��ʾ�߶ȿռ��Sar_harris����
 amplit��ʾ�߶ȿռ����ص��ݶȷ���
 orient��ʾ�߶ȿռ����ص��ݶȷ���
 */
void shift::build_sar_shift_space(const Mat& image, vector<Mat>& sar_harris_func, vector<Mat>& amplit, vector<Mat>& orient)
{
	// ת������ͼ���ʽ
	Mat gray_img;
	if (image.channels() != 1)
		cvtColor(image, gray_img, CV_RGB2GRAY);
	else
		gray_img = image;
	// ����ͼ������
	Mat float_img;
	gray_img.convertTo(float_img, CV_32FC1, 1, 0.f);// ����������ת��λ������������

	//���������Ĵ�С���൱���ڵ���ά��repeat
	sar_harris_func.resize(Mmax);
	amplit.resize(Mmax);
	orient.resize(Mmax);

	for (int i = 0; i < Mmax; ++i)
	{
		//����sigma��ratio����
		float scale = (float)sigma * (float)pow(ratio, i);
		int radius = cvRound(2 * scale);
		Mat kernal;
		// ���������
		roewa_kernal(radius, scale, kernal);

		// �ĸ��˲�ģ��
		Mat W34 = Mat::zeros(2 * radius + 1, 2 * radius + 1, CV_32FC1);
		Mat W12 = Mat::zeros(2 * radius + 1, 2 * radius + 1, CV_32FC1);
		Mat W14 = Mat::zeros(2 * radius + 1, 2 * radius + 1, CV_32FC1);
		Mat W23 = Mat::zeros(2 * radius + 1, 2 * radius + 1, CV_32FC1);
		// ����������ֵʵ���˲�ģ�洰�ڵ��趨
		// ����������ȫ����
		kernal(Range(radius + 1, 2 * radius + 1), Range::all()).copyTo(W34(Range(radius + 1, 2 * radius + 1), Range::all()));
		kernal(Range(0, radius), Range::all()).copyTo(W12(Range(0, radius), Range::all()));
		// ����������ȫ����
		kernal(Range::all(), Range(radius+1,2*radius+1)).copyTo(W14(Range::all(), Range(radius + 1, 2 * radius + 1)));
		kernal(Range::all(), Range(0,radius)).copyTo(W23(Range::all(), Range(0, radius)));

		// ִ���˲�����
		Mat M34, M12, M14, M23;
		double eps = 0.00001;
		filter2D(float_img, M34, CV_32FC1, W34, Point(-1, -1), eps);
		filter2D(float_img, M12, CV_32FC1, W12, Point(-1, -1), eps);
		filter2D(float_img, M14, CV_32FC1, W14, Point(-1, -1), eps);
		filter2D(float_img, M23, CV_32FC1, W23, Point(-1, -1), eps);
		// ����ˮƽ�ݶ�����ֱ�ݶ�
		Mat Gx, Gy;
		log((M14) / (M23), Gx);
		log((M34) / (M12), Gy);

		// ������Ⱥ���λ����
		magnitude(Gx, Gy, amplit[i]);
		phase(Gx, Gy, orient[i], true);

		//����harris�ǵ���Ӧֵ
		Mat Csh_11 = scale * scale * Gx.mul(Gx);
		Mat Csh_12 = scale * scale * Gx.mul(Gy);
		Mat Csh_22 = scale * scale * Gy.mul(Gy);

		// ��˹Ȩ��
		float gauss_sigma = sqrt(2.f) * scale;
		int size = cvRound(3 * gauss_sigma);

		Size Kern_size(2 * size + 1, 2 * size + 1);
		// ʹ���Զ���˵ĸ�˹�˲�
		GaussianBlur(Csh_11, Csh_11, Kern_size, gauss_sigma);
		GaussianBlur(Csh_12, Csh_12, Kern_size, gauss_sigma);
		GaussianBlur(Csh_22, Csh_22, Kern_size, gauss_sigma);

		Mat Csh_21 = Csh_12;

		// ����harris�ǵ���Ӧֵ
		Mat temp_add = Csh_11 + Csh_22;//��
		// ����ʽ��Csh_11.mul(Csh_22) - Csh_21.mul(Csh_12)
		sar_harris_func[i] = Csh_11.mul(Csh_22) - Csh_21.mul(Csh_12) - (float)d * temp_add.mul(temp_add);
	}


}
/******************�ú�������������������*********************/
/*amplit��ʾ���������ڲ���ݶȷ���
 orient��ʾ���������ڲ���ݶȷ���0-360��
 point��ʾ����������
 scale��ʾ����������ڲ�ĳ߶�
 hist��ʾ���ɵ�ֱ��ͼ
 n��ʾ������ֱ��ͼbin����
 �ú�������ֱ��ͼ�����ֵ
 */
static float calc_orient_hist(const Mat& amplit, const Mat& orient, Point2f pt, float scale, float* hist, int n)
{
	int num_row = amplit.rows;
	int num_col = amplit.cols;
	// ͼ�����������Ͻ������Ϊ��ʼ��
	Point point(cvRound(pt.x), cvRound(pt.y));
	int radius = cvRound(SAR_SIFT_FACT_RADIUS_ORI * scale);
	radius = min(radius, min(num_row / 2, num_col / 2));
	float gauss_sig = 2 * scale;
	float exp_temp = -1.f / (2 * gauss_sig * gauss_sig);
	//
	int radius_x_left = point.x - radius;
	int radius_x_right = point.x + radius;
	int radius_y_up = point.y - radius;
	int radius_y_down = point.y + radius;

	// �޶��ǵ�����ͳ�Ʒ�Χ�����������ΧԽ��
	if (radius_x_left < 0)
		radius_x_left = 0;
	if (radius_x_right > num_col - 1)
		radius_x_right = num_col - 1;
	if (radius_y_up < 0)
		radius_y_up = 0;
	if (radius_y_down > num_row - 1)
		radius_y_down = num_row - 1;
	// ��ʱ�ǵ�����ͳ�Ʒ�Χ�����ĵ�����
	int center_x = point.x - radius_x_left;
	int center_y = point.y - radius_y_up;

	// ��������������Χ�ڵĸ�˹Ȩ��
	// ����һ��������������[-2.-1,0,1,2]
	Range x_rng(-(point.x - radius_x_left), radius_x_right - point.x);
	Range y_rng(-(point.y - radius_y_up), radius_y_down - point.y);
	Mat gauss_weight;
	// ����һ�������ξ���
	gauss_weight.create(y_rng.end - y_rng.start + 1,x_rng.end - x_rng.start+1,CV_32FC1);
	for (int i = y_rng.start; i <= y_rng.end; ++i)
	{
		// ����ֵ��Χ[-2:2]ӳ�䵽[0:4]
		float* ptr_gauss = gauss_weight.ptr<float>(i - y_rng.start);
			for (int j = x_rng.start; j <= x_rng.end; ++j)
			{
				// Ϊ��˹Ȩ�ظ�ֵ
				ptr_gauss[j - x_rng.start] = exp((i * i + j * j) * exp_temp);
		}
	}
	// ͳ�ƽǵ���Χ�����ݶȷ��������
	Mat sub_amplit = amplit(Range(radius_y_up, radius_y_down + 1), Range(radius_x_left, radius_x_right + 1));
	Mat sub_orient = orient(Range(radius_y_up, radius_y_down + 1), Range(radius_x_left, radius_x_right + 1));
	//Mat W = sub_amplit.mul(gauss_weight);//��Ӹ�˹Ȩ��
	Mat W = sub_amplit;//����Ӹ�˹Ȩ�ء�����
	// �ڴ��
	AutoBuffer<float> buffer(n + 4);
	// ʹ����ָ���������㣬�� temp_hist ָ��ָ���� buffer �������ĵ�����Ԫ��
	float* temp_hist = buffer + 2;
	// �����ʼ��
	for (int i = 0; i < n; ++i)
		temp_hist[i] = 0.f;
	for (int i = 0; i < sub_orient.rows; i++)
	{
		// ����ͼ
		float *ptr_1 = W.ptr<float>(i);
		float* ptr_2 = sub_orient.ptr<float>(i);
		for (int j = 0; j < sub_orient.cols; j++)
		{
			// ͳ��Բ�η�Χ�ڵ���ֵ
			if (((i - center_x) * (i - center_y) + (j - center_x) * (j - center_y)) < radius * radius)
			{
				//���ǶȻ���Ϊ�Ƕ�����
				int bin = cvRound(ptr_2[j] * n / 360.f);
				if (bin > n)
					bin = bin - n;
				if (bin < 0)
					bin = bin + n;
				temp_hist[bin] + ptr_1[j];
			}

		}
	}
	// ƽ��ֱ��ͼ���������ڣ�c++�����������ǿ���ȡ��ֵ��
	temp_hist[-1] = temp_hist[n - 1];
	temp_hist[-2] = temp_hist[n - 2];
	temp_hist[n] = temp_hist[0];
	temp_hist[n + 1] = temp_hist[1];
	// ����ȡ5��ֵ���м�Ȩ����
	for (int i = 0; i < n; ++i)
	{
		hist[i] = (temp_hist[i-2] + temp_hist[i+2])*(1.f/16.f)+
			(temp_hist[i - 1] + temp_hist[i + 1]) * (4.f / 16.f) +
			temp_hist[i] * (6.f / 16.f);
	}
	// ��ȡֱ��ͼ�����ֵ
	float max_value = hist[0];
	for (int i = 1; i < n; ++i)
	{
		if (hist[i] > max_value)
			max_value = hist[i];
	}
	return max_value;

}

/*************************�ú����ڳ߶ȿռ䶨λ������************************/
/*harris_fun��ʾ�߶ȿռ�Harris����
 amplit��ʾ�߶ȿռ������ݶȷ���
 orient��ʾ�߶ȿռ������ݶȽǶ�
 keys��ʾ�߶ȿռ��⵽��������
 */