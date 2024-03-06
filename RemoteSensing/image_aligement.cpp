///*
//* this sample demonstrates the use of the function
//* findtransformecc that implements the image alignment ecc algorithm
//*
//*
//* the demo loads an image (defaults to fruits.jpg) and it artificially creates
//* a template image based on the given motion type. when two images are given,
//* the first image is the input image and the second one defines the template image.
//* in the latter case, you can also parse the warp's initialization.
//*
//* input and output warp files consist of the raw warp (transform) elements
//*
//* authors: g. evangelidis, inria, grenoble, france
//*          m. asbach, fraunhofer iais, st. augustin, germany
//*/
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/video.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/core/utility.hpp>
//#include <stdio.h>
//#include <string>
//#include <time.h>
//#include <iostream>
//#include <fstream>
//using namespace cv;
//using namespace std;
////函数声明
//// 帮助文档函数
//static void help(const char** argv);
//// 文件读取
//static int readwarp(string ifilename, mat& warp, int motiontype);
//// 文件保存
//static int savewarp(string filename, const mat& warp, int motiontype);
//// 绘制roi
//static void draw_warped_roi(mat& image, const int width, const int height, mat& w);
//// 定义一个宏向函数
//#define homo_vector(h, x, y)\
//    h.at<float>(0,0) = (float)(x);\
//    h.at<float>(1,0) = (float)(y);\
//    h.at<float>(2,0) = 1.;
//#define get_homo_values(x, x, y)\
//    (x) = static_cast<float> (x.at<float>(0,0)/x.at<float>(2,0));\
//    (y) = static_cast<float> (x.at<float>(1,0)/x.at<float>(2,0));
//const std::string keys =
//"{@inputimage    | e:\\opencv\\opencv-4.x\\samples\\data\\fruits.jpg    | input image filename }"
//"{@templateimage |               | template image filename (optional)}"
//"{@inputwarp     |               | input warp (matrix) filename (optional)}"
//"{n numofiter    | 50            | ecc's iterations }"
//"{e epsilon      | 0.0001        | ecc's convergence epsilon }"
//"{o outputwarp   | e:\\opencv\\test\\outwarp.ecc   | output warp (matrix) filename }"
//"{m motiontype   | affine        | type of motion (translation, euclidean, affine, homography) }"
//"{v verbose      | 1             | display initial and final images }"
//"{w warpedimfile | e:\\opencv\\test\\warpedecc.png | warped input image }"
//"{h help | | print help message }"
//;
//static void help(const char** argv)
//{
//    cout << "\nthis file demonstrates the use of the ecc image alignment algorithm. when one image"
//        " is given, the template image is artificially formed by a random warp. when both images"
//        " are given, the initialization of the warp by command line parsing is possible. "
//        "if inputwarp is missing, the identity transformation initializes the algorithm. \n" << endl;
//    cout << "\nusage example (one image): \n"
//        << argv[0]
//        << " fruits.jpg -o=outwarp.ecc "
//        "-m=euclidean -e=1e-6 -n=70 -v=1 \n" << endl;
//    cout << "\nusage example (two images with initialization): \n"
//        << argv[0]
//        << " yourinput.png yourtemplate.png "
//        "yourinitialwarp.ecc -o=outwarp.ecc -m=homography -e=1e-6 -n=70 -v=1 -w=yourfinalimage.png \n" << endl;
//}
//static int readwarp(string ifilename, mat& warp, int motiontype) {
//    // it reads from file a specific number of raw values:
//    // 9 values for homography, 6 otherwise
//    cv_assert(warp.type() == cv_32fc1);
//    int numofelements;
//    if (motiontype == motion_homography)
//        numofelements = 9;
//    else
//        numofelements = 6;
//    int i;
//    int ret_value;
//    ifstream myfile(ifilename.c_str());
//    if (myfile.is_open()) {
//        float* matptr = warp.ptr<float>(0);
//        for (i = 0; i < numofelements; i++) {
//            myfile >> matptr[i];
//        }
//        ret_value = 1;
//    }
//    else {
//        cout << "unable to open file " << ifilename.c_str() << endl;
//        ret_value = 0;
//    }
//    return ret_value;
//}
//static int savewarp(string filename, const mat& warp, int motiontype)
//{
//    // it saves the raw matrix elements in a file
//    cv_assert(warp.type() == cv_32fc1);
//    const float* matptr = warp.ptr<float>(0);
//    int ret_value;
//    ofstream outfile(filename.c_str());
//    if (!outfile) {
//        cerr << "error in saving "
//            << "couldn't open file '" << filename.c_str() << "'!" << endl;
//        ret_value = 0;
//    }
//    else {//save the warp's elements
//        outfile << matptr[0] << " " << matptr[1] << " " << matptr[2] << endl;
//        outfile << matptr[3] << " " << matptr[4] << " " << matptr[5] << endl;
//        if (motiontype == motion_homography) {
//            outfile << matptr[6] << " " << matptr[7] << " " << matptr[8] << endl;
//        }
//        ret_value = 1;
//    }
//    return ret_value;
//}
//// 绘制roi
//static void draw_warped_roi(mat& image, const int width, const int height, mat& w)
//{
//    // 定义点变量
//    point2f top_left, top_right, bottom_left, bottom_right;
//    // 定义初始化函数
//    mat  h = mat(3, 1, cv_32f);
//    mat  u = mat(3, 1, cv_32f);
//    mat warp_mat = mat::eye(3, 3, cv_32f);
//    // 为变换矩阵赋值
//    for (int y = 0; y < w.rows; y++)
//        for (int x = 0; x < w.cols; x++)
//            warp_mat.at<float>(y, x) = w.at<float>(y, x);
//    //warp the corners of rectangle
//    // top-left
//    homo_vector(h, 1, 1);
//    gemm(warp_mat, h, 1, 0, 0, u);
//    get_homo_values(u, top_left.x, top_left.y);
//    // top-right
//    homo_vector(h, width, 1);
//    gemm(warp_mat, h, 1, 0, 0, u);
//    get_homo_values(u, top_right.x, top_right.y);
//    // bottom-left
//    homo_vector(h, 1, height);
//    gemm(warp_mat, h, 1, 0, 0, u);
//    get_homo_values(u, bottom_left.x, bottom_left.y);
//    // bottom-right
//    homo_vector(h, width, height);
//    gemm(warp_mat, h, 1, 0, 0, u);
//    get_homo_values(u, bottom_right.x, bottom_right.y);
//    // draw the warped perimeter：绘制变化边界
//    line(image, top_left, top_right, scalar(255));
//    line(image, top_right, bottom_right, scalar(255));
//    line(image, bottom_right, bottom_left, scalar(255));
//    line(image, bottom_left, top_left, scalar(255));
//}
//int main(const int argc, const char* argv[])
//{
//    commandlineparser parser(argc, argv, keys);
//    parser.about("ecc demo");
//    parser.printmessage();
//
//    help(argv);
//    string imgfile = parser.get<string>(0);
//    string tempimgfile = parser.get<string>(1);
//    string inwarpfile = parser.get<string>(2);
//    int number_of_iterations = parser.get<int>("n");
//    double termination_eps = parser.get<double>("e");
//    string warptype = parser.get<string>("m");
//    int verbose = parser.get<int>("v");
//    string finalwarp = parser.get<string>("o");
//    string warpedimfile = parser.get<string>("w");
//    if (!parser.check())
//    {
//        parser.printerrors();
//        return -1;
//    }
//    if (!(warptype == "translation" || warptype == "euclidean"
//        || warptype == "affine" || warptype == "homography"))
//    {
//        cerr << "invalid motion transformation" << endl;
//        return -1;
//    }
//    int mode_temp;
//    if (warptype == "translation")
//        mode_temp = motion_translation;
//    else if (warptype == "euclidean")
//        mode_temp = motion_euclidean;
//    else if (warptype == "affine")
//        mode_temp = motion_affine;
//    else
//        mode_temp = motion_homography;
//    mat inputimage = imread(samples::findfile(imgfile), imread_grayscale);
//    if (inputimage.empty())
//    {
//        cerr << "unable to load the inputimage" << endl;
//        return -1;
//    }
//    // 定义矩阵
//    mat target_image;
//    mat template_image;
//    if (tempimgfile != "") {
//        // 复制矩阵
//        inputimage.copyto(target_image);
//        // 读取影像
//        template_image = imread(samples::findfile(tempimgfile), imread_grayscale);
//        if (template_image.empty()) {
//            cerr << "unable to load the template i mage" << endl;
//            return -1;
//        }
//    }
//    else { //apply random warp to input image
//        resize(inputimage, target_image, size(216, 216), 0, 0, inter_linear_exact);
//        mat warpground;
//        rng rng(gettickcount());
//        double angle;
//        switch (mode_temp) {
//        case motion_translation:
//            warpground = (mat_<float>(2, 3) << 1, 0, (rng.uniform(10.f, 20.f)),
//                0, 1, (rng.uniform(10.f, 20.f)));
//            warpaffine(target_image, template_image, warpground,
//                size(200, 200), inter_linear + warp_inverse_map);
//            break;
//        case motion_euclidean:
//            angle = cv_pi / 30 + cv_pi * rng.uniform((double)-2.f, (double)2.f) / 180;
//            warpground = (mat_<float>(2, 3) << cos(angle), -sin(angle), (rng.uniform(10.f, 20.f)),
//                sin(angle), cos(angle), (rng.uniform(10.f, 20.f)));
//            warpaffine(target_image, template_image, warpground,
//                size(200, 200), inter_linear + warp_inverse_map);
//            break;
//        case motion_affine:
//            warpground = (mat_<float>(2, 3) << (1 - rng.uniform(-0.05f, 0.05f)),
//                (rng.uniform(-0.03f, 0.03f)), (rng.uniform(10.f, 20.f)),
//                (rng.uniform(-0.03f, 0.03f)), (1 - rng.uniform(-0.05f, 0.05f)),
//                (rng.uniform(10.f, 20.f)));
//            warpaffine(target_image, template_image, warpground,
//                size(200, 200), inter_linear + warp_inverse_map);
//            break;
//        case motion_homography:
//            warpground = (mat_<float>(3, 3) << (1 - rng.uniform(-0.05f, 0.05f)),
//                (rng.uniform(-0.03f, 0.03f)), (rng.uniform(10.f, 20.f)),
//                (rng.uniform(-0.03f, 0.03f)), (1 - rng.uniform(-0.05f, 0.05f)), (rng.uniform(10.f, 20.f)),
//                (rng.uniform(0.0001f, 0.0003f)), (rng.uniform(0.0001f, 0.0003f)), 1.f);
//            warpperspective(target_image, template_image, warpground,
//                size(200, 200), inter_linear + warp_inverse_map);
//            break;
//        }
//    }
//    const int warp_mode = mode_temp;
//    // initialize or load the warp matrix
//    mat warp_matrix;
//    if (warptype == "homography")
//        warp_matrix = mat::eye(3, 3, cv_32f);
//    else
//        warp_matrix = mat::eye(2, 3, cv_32f);
//    if (inwarpfile != "") {
//        int readflag = readwarp(inwarpfile, warp_matrix, warp_mode);
//        if ((!readflag) || warp_matrix.empty())
//        {
//            cerr << "-> check warp initialization file" << endl << flush;
//            return -1;
//        }
//    }
//    else {
//        printf("\n ->performance warning: identity warp ideally assumes images of "
//            "similar size. if the deformation is strong, the identity warp may not "
//            "be a good initialization. \n");
//    }
//    if (number_of_iterations > 200)
//        cout << "-> warning: too many iterations " << endl;
//    if (warp_mode != motion_homography)
//        warp_matrix.rows = 2;
//    // start timing
//    const double tic_init = (double)gettickcount();
//    double cc = findtransformecc(template_image, target_image, warp_matrix, warp_mode,
//        termcriteria(termcriteria::count + termcriteria::eps,
//            number_of_iterations, termination_eps));
//    if (cc == -1)
//    {
//        cerr << "the execution was interrupted. the correlation value is going to be minimized." << endl;
//        cerr << "check the warp initialization and/or the size of images." << endl << flush;
//    }
//    // end timing
//    const double toc_final = (double)gettickcount();
//    const double total_time = (toc_final - tic_init) / (gettickfrequency());
//    if (verbose) {
//        cout << "alignment time (" << warptype << " transformation): "
//            << total_time << " sec" << endl << flush;
//        //  cout << "final correlation: " << cc << endl << flush;
//    }
//    // save the final warp matrix
//    savewarp(finalwarp, warp_matrix, warp_mode);
//    if (verbose) {
//        cout << "\nthe final warp has been saved in the file: " << finalwarp << endl << flush;
//    }
//    // save the final warped image
//    mat warped_image = mat(template_image.rows, template_image.cols, cv_32fc1);
//    if (warp_mode != motion_homography)
//        warpaffine(target_image, warped_image, warp_matrix, warped_image.size(),
//            inter_linear + warp_inverse_map);
//    else
//        warpperspective(target_image, warped_image, warp_matrix, warped_image.size(),
//            inter_linear + warp_inverse_map);
//    // save the warped image
//    imwrite(warpedimfile, warped_image);
//    // display resulting images
//    if (verbose)
//    {
//        cout << "the warped image has been saved in the file: " << warpedimfile << endl << flush;
//        // 创建窗口
//        namedwindow("image", window_autosize);
//        namedwindow("template", window_autosize);
//        namedwindow("warped image", window_autosize);
//        namedwindow("error (black: no error)", window_autosize);
//        movewindow("image", 20, 300);
//        movewindow("template", 300, 300);
//        movewindow("warped image", 600, 300);
//        movewindow("error (black: no error)", 900, 300);
//        // draw boundaries of corresponding regions
//        // 绘制roi
//        mat identity_matrix = mat::eye(3, 3, cv_32f);
//        draw_warped_roi(target_image, template_image.cols - 2, template_image.rows - 2, warp_matrix);
//        draw_warped_roi(template_image, template_image.cols - 2, template_image.rows - 2, identity_matrix);
//        mat errorimage;
//        subtract(template_image, warped_image, errorimage);
//        double max_of_error;
//        minmaxloc(errorimage, null, &max_of_error);
//        // show images
//        cout << "press any key to exit the demo (you might need to click on the images before)." << endl << flush;
//        // 显示图像
//        imshow("image", target_image);
//        waitkey(200);
//        imshow("template", template_image);
//        waitkey(200);
//        imshow("warped image", warped_image);
//        waitkey(200);
//        imshow("error (black: no error)", abs(errorimage) * 255 / max_of_error);
//        waitkey(0);
//    }
//    // done
//    return 0;
//}