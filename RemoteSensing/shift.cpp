#include"shift.h"
#include<opencv2\features2d\features2d.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2\imgproc\types_c.h>
#include<vector>
#include<corecrt_math.h>

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

void shift::find_space_extrema(const vector<Mat> &harris_fun, const vector<Mat> &amplit, const vector<Mat> &orient, vector<KeyPoint> &keys)
{
	// vector�������������ж���
	keys.clear();
	// ���������
	// ͨ���ǵ���Ӧֵȷ����������
	int num_rows = harris_fun[0].rows;
	int num_cols = harris_fun[0].cols;
	const int n = SAR_SIFT_ORI_BINS;
	// opencv�Զ����Ĭ�ϵ����꣬�洢�������ꡢ�Ƕȡ����ȡ���Ӧֵ������
	KeyPoint keypoint;
	// ���������,����ǵ�������Ϣ
	for (int i = 0; i < Mmax; ++i)
	{
		const Mat &cur_harris_fun = harris_fun[i];
		const Mat &cur_amplit = amplit[i];
		const Mat& cur_orient = orient[i];
		// �����뾶

		for (int r = SAR_SIFT_BORDER_CONSTANT; r < num_rows - SAR_SIFT_BORDER_CONSTANT; ++r)
		{   // ӳ��������������
			const float* ptr_up = cur_harris_fun.ptr<float>(r - 1);
			const float* ptr_cur = cur_harris_fun.ptr<float>(r);
			const float* ptr_nex = cur_harris_fun.ptr<float>(r+1);

			for (int c = SAR_SIFT_BORDER_CONSTANT; c < num_cols - SAR_SIFT_BORDER_CONSTANT; ++c)
			{
				// ��ȡ��ǰֵ
				float cur_value = ptr_cur[c];
				// �ж���ǰֵ����ֵ���ܱ�ֵ�Ĵ�С
				if (cur_value > threshold &&
					cur_value > ptr_cur[c - 1] && cur_value > ptr_cur[c + 1] &&
					cur_value > ptr_up[c - 1] && cur_value > ptr_up[c] && cur_value > ptr_up[c + 1] &&
					cur_value > ptr_nex[c - 1] && cur_value > ptr_nex[c] && cur_value > ptr_nex[c + 1]
					)
				{   // �������������������¼��λֵ�Լ�ͼ��λ��
					float x = c * 1.0f; float y = r * 1.0f; int layer = i;
					// ��¼��ǰͼ��߶Ȳ���
					float scale = (float)(sigma * pow(ratio, layer * 1.0));
					// ��ʼ������ֱ��ͼ
					float hist[n];
					//��ʼ��������
					float max_val;
					max_val = calc_orient_hist(amplit[layer], orient[layer], Point2f(x, y), scale, hist, n);
					// 
					float mag_thr = max_val * SAR_SIFT_ORI_RATIO;
					//
					for (int k = 0; k < n; ++k)
					{
						int k_left = k <= 0 ? n - 1 : k - 1;
						int k_right = k >= n - 1 ? 0 : k + 1;
						// Ѱ��������
						if (hist[k] > mag_thr && hist[k] >= hist[k_left] && hist[k_right])
						{
							float bin = (float)k + 0.5f * (hist[k_left] - hist[k_right]) / (hist[k_left] + hist[k_right] - 2 * hist[k]);
							if (bin < 0)
								bin = bin + n;
							if (bin > n)
								bin = bin - n;
							keypoint.pt.x = x * 1.0f;
							keypoint.pt.y = y * 1.0f;
							keypoint.size = scale;
							keypoint.octave = i;
							keypoint.angle = (360.f / n) * bin;
							keypoint.response = cur_value;
							keys.push_back(keypoint);

						}

					}
				}
			}
		}
	}
}

/*�ú�������matlab�е�meshgrid����*/
/*x_range��ʾx����ķ�Χ
y_range��ʾy����ķ�Χ
X��ʾ���ɵ���x��仯������
Y��ʾ������y��任������
*/
static void meshgrid(const Range& x_range, const Range y_range, Mat& X, Mat& Y)
{
	int x_start = x_range.start, x_end = x_range.end;
	int y_start = y_range.start, y_end = y_range.end;
	int width = x_end - x_end + 1;
	int height = y_end - y_start + 1;
	//��������ֵ
	X.create(height, width, CV_32FC1);
	Y.create(height, width, CV_32FC1);
	// X�������������,Y�����ϵ���ֵ��ͬ
	for (int i = y_start; i < y_end; ++i)
	{
		float* ptr_1 = X.ptr<float>(i - y_start);
		for (int j = x_start; j < x_end; ++j)
		{
			ptr_1[j - x_start] = j * 1.0f;
		}
	}
	// Y�������������,X�����ϵ���ֵ��ͬ
	for (int i = x_start; i < x_end; ++i)
	{
		float* ptr_1 = X.ptr<float>(i - y_start);
		for (int j = y_start; j < y_end; ++j)
		{
			ptr_1[j - y_start] = j * 1.0f;
		}
	}
}

static void calc_gloh_descriptor(const Mat& amplit, const Mat& orient, Point2f pt, float scale,float main_ori, int d, int n, float* ptr_des)
{
	Point point(cvRound(pt.x), cvRound(pt.y));
	//�������ҡ�����ֵ
	float cos_t = cosf(-main_ori / 180.f * (float)CV_PI);
	float sin_t = sinf(-main_ori / 180.f * (float)CV_PI);
	int num_rows = amplit.rows;
	int num_cols = amplit.cols;

	int radius = cvRound(SAR_SIFT_RADIUS_DES * scale);

	radius = min(radius, min(num_rows / 2, num_cols / 2));

	int radius_x_left = point.x - radius;

	int radius_x_right = point.x + radius;
	int radius_y_up = point.y - radius;
	int radius_y_down = point.y + radius;

	// ��ֹԽ��
	if (radius_x_left < 0)
		radius_x_left = 0;
	if (radius_x_right > num_cols - 1)
		radius_x_right = num_cols - 1;
	if (radius_y_up < 0)
		radius_y_up = 0;
	if (radius_y_down > num_rows - 1)
		radius_y_down = num_rows - 1;
	// ����������ĵ�����
	int center_x = point.x - radius_x_left;
	int center_y = point.y - radius_y_up;
	// ��������Χ�����������ݶȣ��Ƕ�
	Mat sub_amplit = amplit(Range(radius_y_up, radius_y_down), Range(radius_x_left, radius_x_right));
	Mat sub_orient = orient(Range(radius_y_up, radius_y_down), Range(radius_x_left, radius_x_right));

	// 
	Range x_rng(-(point.x - radius_x_left), (radius_x_right - point.x));
	Range y_rng(-(point.y - radius_y_up), (radius_y_down - point.x));
	Mat X, Y;
	meshgrid(x_rng, y_rng, X, Y);
	// ��ά�������ת��
	Mat c_rot = X * cos_t - Y * sin_t;
	Mat r_rot = X * sin_t + Y * cos_t;
	Mat GLOH_angle, GLOH_amplit;
	// ������ϵ�µĽǶ�������
	// ����������ģ
	phase(c_rot, r_rot, GLOH_angle, true);//�Ƕ���0-360��֮��
	// λ��
	GLOH_amplit = c_rot.mul(c_rot) + r_rot.mul(r_rot);//Ϊ�˼ӿ��ٶȣ�û�м��㿪��
	//����Բ�뾶ƽ��
	float R1_pow = (float)radius * radius;//��Բ�뾶ƽ��
	float R2_pow = pow(radius * SAR_SIFT_GLOH_RATIO_R1_R2, 2.f);//�м�Բ�뾶ƽ��
	float R3_pow = pow(radius * SAR_SIFT_GLOH_RATIO_R1_R3, 2.f);//��Բ�뾶ƽ��

	int sub_rows = sub_amplit.rows;
	int sub_cols = sub_amplit.cols;

	//��ʼ����������,�ڽǶȷ���������ӽ��в�ֵ
	int len = (d * 2 + 1) * n;
	AutoBuffer<float> hist(len);
	for (int i = 0; i < len; ++i)//����
		hist[i] = 0;
	// 
	for (int i = 0; i < sub_rows; ++i)
	{
		float* ptr_amplit = sub_amplit.ptr<float>(i);
		float* ptr_orient = sub_orient.ptr<float>(i);
		float* ptr_GLOH_amp = GLOH_amplit.ptr<float>(i);
		float* ptr_GLOH_ang = GLOH_angle.ptr<float>(i);
		for (int j = 0; j < sub_cols; ++j)
		{
			// �����Բ��Χ
			if (((i - center_y) * (i - center_y) + (j - center_x) * (j - center_x)) < radius * radius)
			{
				// ��¼�뾶��Χ����Ϣ
				float pix_amplit = ptr_amplit[j];//�����ص��ݶȷ���
				float pix_orient = ptr_orient[j];//�����ص��ݶȷ���
				float pix_GLOH_amp = ptr_GLOH_amp[j];//��������GLOH�����еİ뾶λ��
				float pix_GLOH_ang = ptr_GLOH_ang[j];//��������GLOH�����е�λ�÷���

				int rbin, cbin, obin;
				// ȷ���뾶��Χ
				rbin = pix_GLOH_amp < R3_pow ? 0 : (pix_GLOH_amp > R2_pow ? 2 : 1);//rbin={0,1,2}
				// ����Ƕ�
				cbin = cvRound(pix_GLOH_ang * d / 360.f);
				// ������������������
				cbin = cbin > d ? cbin - d : (cbin <= 0 ? cbin + d : cbin);//cbin=[1,d]
				// ��
				obin = cvRound(pix_orient * n / 360.f);
				// n?
				obin = obin > n ? obin - n : (obin <= 0 ? obin + n : obin);//obin=[1,n]

				if (rbin == 0)//��Բ�ڣ����ȼ�¼��׼
					hist[obin - 1] += pix_amplit;
				else
				{
					int idx = ((rbin - 1) * d + cbin - 1) * n + n + obin - 1;
					hist[idx] += pix_amplit;
				}
			}
		}
	}
	//�������ӽ��й�һ��
	float norm = 0;
	for (int i = 0; i < len; ++i)
	{
		norm = norm + hist[i] * hist[i];
	}
	norm = sqrt(norm);
	for (int i = 0; i < len; ++i)
	{
		hist[i] = hist[i] / norm;
	}

	// ��ֵ�ض�
	for (int i = 0; i < len; ++i)
	{
		hist[i] = min(hist[i], DESCR_MAG_THR);
	}

	// �ٴι�һ��
	norm = 0;
	for (int i = 0; i < len; ++i)
	{
		norm = norm + hist[i] * hist[i];
	}
	norm = sqrt(norm);
	for (int i = 0; i < len; ++i)
	{
		ptr_des[i] = hist[i] / norm;
	}


}