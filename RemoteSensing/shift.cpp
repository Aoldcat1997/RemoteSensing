#include"shift.h"
#include<opencv2\features2d\features2d.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2\imgproc\types_c.h>
#include<vector>

/*********该函数根据尺度和窗口半径生成ROEWA滤波模板************/
/*size表示核半径，因此核宽度是2*size+1
 scale表示指数权重参数
 kernel表示生成的滤波核
 */

static void roewa_kernal(int size, float scale, Mat& kernal)
{
	kernal.create(2 * size + 1, 2 * size + 1, CV_32FC1);
	for (int i = -size; i <= size; ++i)
	{
		// 里i + size的目的是将索引范围从[0, 2 * size]映射到[-size, size]。
		float* ptr_k = kernal.ptr<float>(i + size);
		for (int j = -size; j <= size; ++j)
		{
			ptr_k[j + size] = exp(-1.f * (abs(i) + abs(j)) / scale);
	
		}
	}
}

/*该函数根据窗口半径，标准差，生成圆形高斯滤波模板，不是正方向*/
/*size表示圆半径
 scale表示高斯标准差
 gauss_kernel表示生成的圆形高斯核
 二维高斯函数的形式：1/(2*pi*scale*scale)*exp(-(x*x+y*y)/(2*scale*scale))
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

/*************该类成员函数构建SAR_SIFT尺度空间*****************/
/*image表示输入的原始图像
 sar_harris_fun表示尺度空间的Sar_harris函数
 amplit表示尺度空间像素的梯度幅度
 orient表示尺度空间像素的梯度方向
 */
void shift::build_sar_shift_space(const Mat& image, vector<Mat>& sar_harris_func, vector<Mat>& amplit, vector<Mat>& orient)
{
	// 转换输入图像格式
	Mat gray_img;
	if (image.channels() != 1)
		cvtColor(image, gray_img, CV_RGB2GRAY);
	else
		gray_img = image;
	// 更改图像类型
	Mat float_img;
	gray_img.convertTo(float_img, CV_32FC1, 1, 0.f);// 将整数数据转换位浮点数据数据

	//调整向量的大小，相当于在第三维度repeat
	sar_harris_func.resize(Mmax);
	amplit.resize(Mmax);
	orient.resize(Mmax);

	for (int i = 0; i < Mmax; ++i)
	{
		//根据sigma和ratio计算
		float scale = (float)sigma * (float)pow(ratio, i);
		int radius = cvRound(2 * scale);
		Mat kernal;
		// 创建卷积核
		roewa_kernal(radius, scale, kernal);

		// 四个滤波模版
		Mat W34 = Mat::zeros(2 * radius + 1, 2 * radius + 1, CV_32FC1);
		Mat W12 = Mat::zeros(2 * radius + 1, 2 * radius + 1, CV_32FC1);
		Mat W14 = Mat::zeros(2 * radius + 1, 2 * radius + 1, CV_32FC1);
		Mat W23 = Mat::zeros(2 * radius + 1, 2 * radius + 1, CV_32FC1);
		// 矩阵索引赋值实现滤波模版窗口的设定
		// 处理部分行与全部列
		kernal(Range(radius + 1, 2 * radius + 1), Range::all()).copyTo(W34(Range(radius + 1, 2 * radius + 1), Range::all()));
		kernal(Range(0, radius), Range::all()).copyTo(W12(Range(0, radius), Range::all()));
		// 处理部分列与全部行
		kernal(Range::all(), Range(radius+1,2*radius+1)).copyTo(W14(Range::all(), Range(radius + 1, 2 * radius + 1)));
		kernal(Range::all(), Range(0,radius)).copyTo(W23(Range::all(), Range(0, radius)));

		// 执行滤波函数
		Mat M34, M12, M14, M23;
		double eps = 0.00001;
		filter2D(float_img, M34, CV_32FC1, W34, Point(-1, -1), eps);
		filter2D(float_img, M12, CV_32FC1, W12, Point(-1, -1), eps);
		filter2D(float_img, M14, CV_32FC1, W14, Point(-1, -1), eps);
		filter2D(float_img, M23, CV_32FC1, W23, Point(-1, -1), eps);
		// 计算水平梯度与竖直梯度
		Mat Gx, Gy;
		log((M14) / (M23), Gx);
		log((M34) / (M12), Gy);

		// 计算幅度和相位方向
		magnitude(Gx, Gy, amplit[i]);
		phase(Gx, Gy, orient[i], true);

		//计算harris角点响应值
		Mat Csh_11 = scale * scale * Gx.mul(Gx);
		Mat Csh_12 = scale * scale * Gx.mul(Gy);
		Mat Csh_22 = scale * scale * Gy.mul(Gy);

		// 高斯权重
		float gauss_sigma = sqrt(2.f) * scale;
		int size = cvRound(3 * gauss_sigma);

		Size Kern_size(2 * size + 1, 2 * size + 1);
		// 使用自定义核的高斯滤波
		GaussianBlur(Csh_11, Csh_11, Kern_size, gauss_sigma);
		GaussianBlur(Csh_12, Csh_12, Kern_size, gauss_sigma);
		GaussianBlur(Csh_22, Csh_22, Kern_size, gauss_sigma);

		Mat Csh_21 = Csh_12;

		// 计算harris角点响应值
		Mat temp_add = Csh_11 + Csh_22;//迹
		// 行列式：Csh_11.mul(Csh_22) - Csh_21.mul(Csh_12)
		sar_harris_func[i] = Csh_11.mul(Csh_22) - Csh_21.mul(Csh_12) - (float)d * temp_add.mul(temp_add);
	}


}
/******************该函数计算特征点主方向*********************/
/*amplit表示特征点所在层的梯度幅度
 orient表示特征点所在层的梯度方向，0-360度
 point表示特征点坐标
 scale表示特征点的所在层的尺度
 hist表示生成的直方图
 n表示主方向直方图bin个数
 该函数返回直方图的最大值
 */
static float calc_orient_hist(const Mat& amplit, const Mat& orient, Point2f pt, float scale, float* hist, int n)
{
	int num_row = amplit.rows;
	int num_col = amplit.cols;
	// 图像坐标以左上角坐标点为起始点
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

	// 限定角点特征统计范围，避免检索范围越界
	if (radius_x_left < 0)
		radius_x_left = 0;
	if (radius_x_right > num_col - 1)
		radius_x_right = num_col - 1;
	if (radius_y_up < 0)
		radius_y_up = 0;
	if (radius_y_down > num_row - 1)
		radius_y_down = num_row - 1;
	// 此时角点特征统计范围的中心点坐标
	int center_x = point.x - radius_x_left;
	int center_y = point.y - radius_y_up;

	// 定义特征检索范围内的高斯权重
	// 创建一个横纵坐标序列[-2.-1,0,1,2]
	Range x_rng(-(point.x - radius_x_left), radius_x_right - point.x);
	Range y_rng(-(point.y - radius_y_up), radius_y_down - point.y);
	Mat gauss_weight;
	// 创建一个单波段矩阵
	gauss_weight.create(y_rng.end - y_rng.start + 1,x_rng.end - x_rng.start+1,CV_32FC1);
	for (int i = y_rng.start; i <= y_rng.end; ++i)
	{
		// 将数值范围[-2:2]映射到[0:4]
		float* ptr_gauss = gauss_weight.ptr<float>(i - y_rng.start);
			for (int j = x_rng.start; j <= x_rng.end; ++j)
			{
				// 为高斯权重赋值
				ptr_gauss[j - x_rng.start] = exp((i * i + j * j) * exp_temp);
		}
	}
	// 统计角点周围像素梯度方向与幅度
	Mat sub_amplit = amplit(Range(radius_y_up, radius_y_down + 1), Range(radius_x_left, radius_x_right + 1));
	Mat sub_orient = orient(Range(radius_y_up, radius_y_down + 1), Range(radius_x_left, radius_x_right + 1));
	//Mat W = sub_amplit.mul(gauss_weight);//添加高斯权重
	Mat W = sub_amplit;//不添加高斯权重、噪声
	// 内存池
	AutoBuffer<float> buffer(n + 4);
	// 使用了指针算术运算，将 temp_hist 指针指向了 buffer 缓冲区的第三个元素
	float* temp_hist = buffer + 2;
	// 数组初始化
	for (int i = 0; i < n; ++i)
		temp_hist[i] = 0.f;
	for (int i = 0; i < sub_orient.rows; i++)
	{
		// 幅度图
		float *ptr_1 = W.ptr<float>(i);
		float* ptr_2 = sub_orient.ptr<float>(i);
		for (int j = 0; j < sub_orient.cols; j++)
		{
			// 统计圆形范围内的数值
			if (((i - center_x) * (i - center_y) + (j - center_x) * (j - center_y)) < radius * radius)
			{
				//将角度换算为角度区间
				int bin = cvRound(ptr_2[j] * n / 360.f);
				if (bin > n)
					bin = bin - n;
				if (bin < 0)
					bin = bin + n;
				temp_hist[bin] + ptr_1[j];
			}

		}
	}
	// 平滑直方图，滑动窗口，c++中数组索引是可以取负值的
	temp_hist[-1] = temp_hist[n - 1];
	temp_hist[-2] = temp_hist[n - 2];
	temp_hist[n] = temp_hist[0];
	temp_hist[n + 1] = temp_hist[1];
	// 滑动取5个值进行加权计算
	for (int i = 0; i < n; ++i)
	{
		hist[i] = (temp_hist[i-2] + temp_hist[i+2])*(1.f/16.f)+
			(temp_hist[i - 1] + temp_hist[i + 1]) * (4.f / 16.f) +
			temp_hist[i] * (6.f / 16.f);
	}
	// 获取直方图中最大值
	float max_value = hist[0];
	for (int i = 1; i < n; ++i)
	{
		if (hist[i] > max_value)
			max_value = hist[i];
	}
	return max_value;

}

/*************************该函数在尺度空间定位特征点************************/
/*harris_fun表示尺度空间Harris函数
 amplit表示尺度空间像素梯度幅度
 orient表示尺度空间像素梯度角度
 keys表示尺度空间检测到的特征点
 */