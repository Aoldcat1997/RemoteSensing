///*
//* decolor.cpp
//*
//* Author:
//* Siddharth Kherada <siddharthkherada27[at]gmail[dot]com>
//*
//* This tutorial demonstrates how to use OpenCV Decolorization Module.
//*
//* Input:
//* Color Image
//*
//* Output:
//* 1) Grayscale image
//* 2) Color boost image
//*
//*/
//
//#include "opencv2/photo.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/core.hpp"
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int main(int argc, char* argv[])
//{
//    // 命令行输入
//    CommandLineParser parser(argc, argv, "{@input | E:\\gdal\\gdal-master\\data\\gdalicon.png | input image}");
//    //读取影像存入矩阵中
//    Mat src = imread(samples::findFile(parser.get<String>("@input")), IMREAD_COLOR);
//    //检查影像是否读取成功
//    if (src.empty())
//    {
//        cout << "Could not open or find the image!\n" << endl;
//        cout << "Usage: " << argv[0] << " <Input image>" << endl;
//        return EXIT_FAILURE;
//    }
//    // 定义灰度图像矩阵与颜色增强矩阵
//    Mat gray, color_boost;
//    // 执行灰度操作，利用应用来访问数据内存，可以修改数据
//    decolor(src, gray, color_boost);
//    imshow("Source Image", src);
//    imshow("grayscale", gray);
//    imshow("color_boost", color_boost);
//    waitKey(0);
//}
