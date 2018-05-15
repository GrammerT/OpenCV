#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;
//#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"
#define DATA_PATH "..\\data\\"

int plateLocate(Mat src,vector<Mat> &resultVec);
bool verifySizes(RotatedRect &minRect);
Mat showResultMat(Mat src,
                   Size rect_size,
                   Point2f center,
                   int index);

int main(int argc, char *argv[])
{
    Mat src ;
    String src_path;
    src_path+=DATA_PATH;
    src_path+="car_plate.jpg";
    src=imread(src_path);
    if(src.empty())
    {
        cout<<"src error"<<endl;
        return -1;
    }
    vector<Mat> result;
    plateLocate(src,result);
    for(int i=0;i<result.size();++i) {
        imshow("----result "+i,result[i]);
    }
    waitKey(0);
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
       cout<< imwrite(ss.str(),src_blur)<<endl;
    }
    //! 2.转化为灰度图像.为边缘检测算法提供灰度化环境
    cvtColor(src_blur,src_gray,CV_RGB2GRAY);
    {
        stringstream ss(stringstream::in|stringstream::out);
        ss<<"tmp/debug_gray.jpg";
        cout<<imwrite(ss.str(),src_gray)<<endl;
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
        cout<<imwrite(ss.str(),grad)<<endl;
    }
    //! 二值化:threshold.
    Mat img_threshold;
    //! 大律法
    //! 为后续的形态学算子Morph等准备二值化的图像
    threshold(grad,img_threshold,0,255,CV_THRESH_OTSU + CV_THRESH_BINARY);
    {
        stringstream ss(stringstream::in|stringstream::out);
        ss<<"tmp/debug_threshold.jpg";
        cout<<imwrite(ss.str(),img_threshold);
    }
    //! Size(): 影响定位
    Mat element = getStructuringElement(MORPH_RECT,Size(10,3));
    //! 闭操作:用于去除小孔（黑暗区域）,形成一个车牌的大致轮廓
    morphologyEx(img_threshold,img_threshold,MORPH_CLOSE,element);
    {
        stringstream ss(stringstream::in | stringstream::out);
        ss << "tmp/debug_morphology_close" << ".jpg";
        cout<<imwrite(ss.str(), img_threshold)<<endl;
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
       cout<< imwrite(ss.str(), result)<<endl;
    }
    vector<vector<Point>>::iterator itc = contours.begin();
    //! RotatedRect: 包含质心，边长，旋转角度
    vector<RotatedRect> rects;
    {
        //! 移除不符合要求的Rect
        int t=0;
        while(itc!=contours.end())
        {
            // itc: 每一条等高线.mr:这条等高线的最小外接矩形
            RotatedRect mr = minAreaRect(Mat(*itc));
            if(!verifySizes(mr))
            {
                itc=contours.erase(itc);
            }
            else
            {
                ++itc;
                rects.push_back(mr);
            }
        }
    }
    int k = 1;
    for(int i=0;i<rects.size();++i)
    {
        RotatedRect minRect = rects[i];
        if(verifySizes(minRect))
        {
            {
                Point2f rect_points[4];
                minRect.points(rect_points);
                for(int j=0;j<4;++j)
                {
                    line(result,rect_points[j],rect_points[(j+1)%4],
                            Scalar(0,255,255),1,8);
                    imshow("result line",result);
                    waitKey(0);
                }
            }
            float r=(float)minRect.size.width/(float)minRect.size.height;
            float angle = minRect.angle;
            float t_angle=angle;
            Size rect_size = minRect.size;
            Size t_rect_size = rect_size;
            if(r<1)
            {
                angle += 90;
                swap(rect_size.width,rect_size.height);
                minRect.angle=angle;
                minRect.size=rect_size;
                Point2f rect_points[4];
                minRect.points(rect_points);
                for(int j=0;j<4;++j)
                {
                    line(result,rect_points[j],rect_points[(j+1)%4],
                            Scalar(255,0,0),1,8);
//                    imshow("result line",result);
//                    waitKey(0);
                }
            }
            minRect.angle=t_angle;
            minRect.size=t_rect_size;
            //! 如果抓取方块旋转超过m_angle角度，
            //! 则不是车牌，放弃处理
            if(angle-15.0<0&&angle+15.0>0)
            {
                Mat rotMat = getRotationMatrix2D(minRect.center,angle,1);
                Mat img_rotated;
//                imshow("src demo",src);
//                waitKey(0);
                warpAffine(src,img_rotated,rotMat,src.size(),CV_INTER_CUBIC);
//                imshow("src img_rotated",img_rotated);
//                waitKey(0);
                Mat resultMat;
                resultMat = showResultMat(img_rotated,
                                                        rect_size,minRect.center,
                                                            k++);
                resultVec.push_back(resultMat);
            }
        }
    }
    {
        stringstream ss(stringstream::in | stringstream::out);
        ss << "tmp/debug_result" << ".jpg";
       cout<< imwrite(ss.str(), result)<<endl;
    }
}


//!
//! \brief verifySizes
//! \param minRect
//! \return
//! 1.设立一个偏差率error，根据这个偏差率计算最大和最小的宽高比rmax、rmin。
//! 判断矩形的r是否满足在rmax、rmin之间。
//! 2.设定一个面积最大值max与面积最小值min。
//! 判断矩形的面积area是否满足在max与min之间。
//!
bool verifySizes(RotatedRect &minRect)
{
    float error = 0.9f;
    // China car plate size: 440mm*140mm，aspect 3.142857
    // Real car plate size: 136 * 32, aspect 4
    float aspect = 3.75f;
    float verifyMin = 1;
    float verifyMax = 24;
    //Set a min and max area. All other patchs are discarded
    int min = 44*14*verifyMin;
    int max = 44*14*verifyMax;
    float rmin = aspect-aspect*error;
    float rmax = aspect+aspect*error;
    int area = minRect.size.height*minRect.size.width;
    float r = (float)minRect.size.width/(float)minRect.size.height;
    if(r<1)
    {
        r=(float)minRect.size.height/(float)minRect.size.width;
    }

    if((area<min||area>max)||(r<rmin||r>rmax))
        return false;
    return true;
}

Mat showResultMat(Mat src,
                   Size rect_size,
                   Point2f center,
                   int index)
{
    Mat img_crop;
    getRectSubPix(src,rect_size,center,img_crop);

    {
        stringstream ss(stringstream::in | stringstream::out);
        ss << "tmp/debug_crop_" <<index<< ".jpg";
        cout<<imwrite(ss.str(), img_crop)<<endl;
    }
    Mat resultResized;
    resultResized.create(36,136,CV_32FC3);
    resize(img_crop,resultResized,resultResized.size(),0,0,INTER_CUBIC);
    {
        stringstream ss(stringstream::in | stringstream::out);
        ss << "tmp/debug_resize_" <<index<< ".jpg";
        cout<<imwrite(ss.str(), resultResized)<<endl;
    }
    return resultResized;
}
