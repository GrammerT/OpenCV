#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;
//#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"
#define DATA_PATH "..\\data\\"

int plateLocate(Mat src,vector<Mat> &resultVec);


int main(int argc, char *argv[])
{


    return 0;
}

int plateLocate(Mat src,vector<Mat> &resultVec)
{
    Mat src_blur,src_gray;
    Mat grad;

    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    if(src.empty())
    {
        return -1;
    }
    //! 1. 高斯模糊：去除噪声.Size():影响识别精度
    GaussianBlur(src,src_blur,Size(5,5),0);
    {
        //! save temp jpg
        stringstream ss(stringstream::in|stringstream::out);
        ss<<"tmp/debug_gauss.jpg";
        imwrite(ss.str(),src_blur);
    }
    //! 2.转化为灰度图像.为边缘检测算法提供灰度化环境
    cvtColor(src_blur,src_gray,CV_RGB2GRAY);
    {
        stringstream ss(stringstream::in|stringstream::out);
        ss<<"tmp/debug_gray.jpg";
        imwrite(ss.str(),src_gray);
    }
    //! sobel算子:检测图像中的垂直边缘,便于区分车牌
    Mat grad_x,grad_y;
    Mat abs_grad_x,abs_grad_y;

    Sobel(src_gray,grad_x,ddepth,1,0,3,scale,delta);
    convertScaleAbs(grad_x,abs_grad_x);//! 将-256 — 255的导数值，转成0 — 255的无符号8位类型
    Sobel(src_gray,grad_y,ddepth,0,1,3,scale,delta);
    convertScaleAbs(grad_y,abs_grad_y);
    addWeighted(abs_grad_x,1,abs_grad_y,0,0,grad);//! 融合两个方向的方向导数求出的图像
    {
        stringstream ss(stringstream::in|stringstream::out);
        ss<<"tmp/debug_grad.jpg";
        imwrite(ss.str(),grad);
    }
    //! 二值化:threshold.
    Mat img_threshold;
    //! 大律法
    threshold(grad,img_threshold,0,255,CV_THRESH_OTSU + CV_THRESH_BINARY);
    {
        stringstream ss(stringstream::in|stringstream::out);
        ss<<"tmp/debug_threshold.jpg";
        imwrite(ss.str(),img_threshold);
    }
    //! Size(): 影响定位
    Mat element = getStructuringElement(MORPH_RECT,Size(10,3));
    //! 闭操作:用于去除小孔（黑暗区域）,形成一个车牌的大致轮廓
    morphologyEx(img_threshold,img_threshold,MORPH_CLOSE,element);
    {
        stringstream ss(stringstream::in | stringstream::out);
        ss << "tmp/debug_morphology_close" << ".jpg";
        imwrite(ss.str(), img_threshold);
    }
    //! 发现轮廓
    vector<vector<Point>> contours;
    findContours(img_threshold,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    Mat result;
    {
        //// Draw blue contours on a white image
        src.copyTo(result);
        drawContours(result, contours,
                     -1, // draw all contours
                     Scalar(0,0,255), // in blue
                     1); // with a thickness of 1
        stringstream ss(stringstream::in | stringstream::out);
        ss << "tmp/debug_Contours" << ".jpg";
        imwrite(ss.str(), result);
    }
    vector<vector<Point>>::iterator itc = contours.begin();
    vector<RotatedRect> rects;
}
