//#include <opencv2/opencv.hpp>
//#include <iostream>
//
////定义命名空间
//using namespace std;
//using namespace cv;
//
//int main()
//{
//    //OpenCV版本号
//    cout << "OpenCV_Version: " << CV_VERSION << endl;
//
//    //读取图片
//    Mat img = imread("C:/Users/Chang/Pictures/Saved Pictures/154932fgo78nnwgnww4kve.jpg");
//
//    imshow("picture", img);
//    waitKey(0);
//    return 0;
//}
////#include <iostream>
////#include <opencv2/opencv.hpp>
//
////using namespace std;
//
////int main()
////{
////	float a[6] = { 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f };
////	float b[6] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
////	cv::Mat A(2, 3, CV_32FC1, a);
////	cv::Mat B(3, 2, CV_32FC1, b);
////	// 运算符的重载
////	cv::Mat C = A * B;
////
////	cout << "Matrix C = " << endl
////		<< C << endl;
////	return 0;
////}
///*c#inlude "gdal_priv.h"
//
//#include <iostream>
//
//using namespace std;
//
//int main()
//
//{
//
//	const char* pszFile;
//
//	GDALAllRegister();
//
//	pszFile = "E:\diphoto_design\data_j6\LDSC00639.JPG";
//
//	GDALDataset* poDataset = (GDALDataset*)GDALOpen(pszFile, GA_ReadOnly);
//
//	GDALRasterBand* poBand = poDataset->GetRasterBand(1);
//
//	int xsize = poBand->GetXSize();
//
//	int ysize = poBand->GetYSize();
//
//	cout << xsize << endl;
//
//	cout << ysize << endl;
//
//	system("pause");
//
//	return 0;
//
//}*/
