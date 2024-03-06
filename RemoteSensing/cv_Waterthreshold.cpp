//#include <opencv2/core/utility.hpp>
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//
//#include <cstdio>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//static void help(char** argv)
//{
//    cout << "\nThis program demonstrates the famous watershed segmentation algorithm in OpenCV: watershed()\n"
//        "Usage:\n" << argv[0] << " [image_name -- default is fruits.jpg]\n" << endl;
//
//
//    cout << "Hot keys: \n"
//        "\tESC - quit the program\n"
//        "\tr - restore the original image\n"
//        "\tw or SPACE - run watershed segmentation algorithm\n"
//        "\t\t(before running it, *roughly* mark the areas to segment on the image)\n"
//        "\t  (before that, roughly outline several markers on the image)\n";
//}
//// 全局变量
//Mat markerMask, img;
//Point prevPt(-1, -1);
//// 该函数接受一个鼠标事件
//static void onMouse(int event, int x, int y, int flags, void*)
//{
//    if (x < 0 || x >= img.cols || y < 0 || y >= img.rows)
//        return;
//    // 鼠标左键已经释放，！鼠标左键已经按下
//    if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
//        prevPt = Point(-1, -1);
//    // 鼠标左键已经按下
//    else if (event == EVENT_LBUTTONDOWN)
//        prevPt = Point(x, y);
//    // 鼠标已经移除窗口，鼠标左键已经按下
//    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
//    {   
//        Point pt(x, y);
//        if (prevPt.x < 0)
//            prevPt = pt;
//        // 在数组上绘制线
//        line(markerMask, prevPt, pt, Scalar::all(255), 5, 8, 0);
//        line(img, prevPt, pt, Scalar::all(255), 5, 8, 0);
//        prevPt = pt;
//        cv::imshow("image", img);
//    }
//}
//
//int main(int argc, char** argv)
//{
//    cv::CommandLineParser parser(argc, argv, "{help h | | }{ @input | E:\\opencv\\opencv-4.x\\samples\\data\\fruits.jpg | }");
//    if (parser.has("help"))
//    {
//        help(argv);
//        return 0;
//    }
//    string filename = samples::findFile(parser.get<string>("@input"));
//    Mat img0 = imread(filename, IMREAD_COLOR), imgGray;
//
//    if (img0.empty())
//    {
//        cout << "Couldn't open image ";
//        help(argv);
//        return 0;
//    }
//    help(argv);
//    cv::namedWindow("image", 1);
//    // 图像变换
//    img0.copyTo(img);
//    // 输入影像与输出影像
//    cv::cvtColor(img, markerMask, COLOR_BGR2GRAY);
//    cv::cvtColor(markerMask, imgGray, COLOR_GRAY2BGR);
//    markerMask = Scalar::all(0);
//    cv::imshow("image", img);
//    // 未为指定窗口设置鼠标句柄：为“image”窗口，调用鼠标事件
//    cv::setMouseCallback("image", onMouse, 0);
//    // 以上函数对markerMask进行了修改
//    // 无限循环
//    for (;;)
//    {
//        char c = (char)waitKey(0);
//
//        if (c == 27)
//            break;
//
//        if (c == 'r')
//        {
//            markerMask = Scalar::all(0);
//            img0.copyTo(img);
//            cv::imshow("image", img);
//        }
//
//        if (c == 'w' || c == ' ')
//        {
//            int i, j, compCount = 0;
//            vector<vector<Point> > contours;
//            vector<Vec4i> hierarchy;
//            // 二进制文件查找轮廓
//            findContours(markerMask, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//
//            if (contours.empty())
//                continue;
//            // 创建一个0维矩阵，用于绘制轮廓
//            Mat markers(markerMask.size(), CV_32S);
//            markers = Scalar::all(0);
//            int idx = 0;
//            // 绘制轮廓
//            for (; idx >= 0; idx = hierarchy[idx][0], compCount++)
//                drawContours(markers, contours, idx, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
//
//            if (compCount == 0)
//                continue;
//
//            vector<Vec3b> colorTab;
//            for (i = 0; i < compCount; i++)
//            {
//                int b = theRNG().uniform(0, 255);
//                int g = theRNG().uniform(0, 255);
//                int r = theRNG().uniform(0, 255);
//
//                colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
//            }
//
//            double t = (double)getTickCount();
//            cv::watershed(img0, markers);
//            t = (double)getTickCount() - t;
//            cout << "execution time = %gms\n" << t * 1000. / getTickFrequency() << endl;
//            // 创建一个三通道矩阵
//            Mat wshed(markers.size(), CV_8UC3);
//
//            // paint the watershed image
//            for (i = 0; i < markers.rows; i++)
//                for (j = 0; j < markers.cols; j++)
//                {
//                    int index = markers.at<int>(i, j);
//                    if (index == -1)
//                        wshed.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
//                    else if (index <= 0 || index > compCount)
//                        wshed.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
//                    else
//                        wshed.at<Vec3b>(i, j) = colorTab[index - 1];
//                }
//            // 叠加图像进行显示
//            wshed = wshed * 0.5 + imgGray * 0.5;
//            cv::imshow("watershed transform", wshed);
//        }
//    }
//
//    return 0;
//}
