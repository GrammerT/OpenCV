#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;

//#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"
#define DATA_PATH "..\\data\\"

enum Color { BLUE, YELLOW, WHITE, UNKNOWN };

int plateColorLocate(Mat src);
int colorSearch(const Mat &src,const Color r,Mat &out);
int deskew(const Mat &src, const Mat &src_b,
                         vector<RotatedRect> &inRects, bool useDeteleArea, Color color);

Mat colorMatch(const Mat &src,Mat &match,const Color r,const bool adaptive_minsv);

int main(int argc, char *argv[])
{
    Mat src ;
    String src_path;
    src_path+=DATA_PATH;
    src_path+="QQ_test.jpg";

    return 0;
}

int colorSearch(const Mat &src,const Color r,Mat &out)
{
    Mat match_gray;
    //! width is important to the final results;
    const int color_morph_width = 10;
    const int color_morph_heigh = 2;

//    color

    return 0;
}

int deskew(const Mat &src, const Mat &src_b,
                         vector<RotatedRect> &inRects, bool useDeteleArea, Color color)
{
    return 0;
}

//! 可以识别蓝牌和黄牌
int plateColorLocate(Mat src)
{
    vector<RotatedRect> rects_color_blue;
    rects_color_blue.reserve(64);
    vector<RotatedRect> rects_color_yellow;
    rects_color_yellow.reserve(64);

    Mat src_clone = src.clone();

    Mat src_b_blue;
    Mat src_b_yellow;
    {
        colorSearch(src,YELLOW,src_b_yellow);
        deskew(src,src_b_yellow,rects_color_yellow,true,YELLOW);
    }
    {
        colorSearch(src_clone,BLUE,src_b_blue);
        deskew(src_clone,src_b_yellow,rects_color_blue,true,BLUE);
    }
    return 0;
}



Mat colorMatch(const Mat &src,Mat &match,const Color r,const bool adaptive_minsv)
{
    // if use adaptive_minsv
    // min value of s and v is adaptive to h
    const float max_sv = 255;
    const float minref_sv = 64;

    const float minabs_sv = 95; //95;
    // H range of blue

    const int min_blue = 100;  // 100
    const int max_blue = 140;  // 140

    // H range of yellow

    const int min_yellow = 15;  // 15
    const int max_yellow = 40;  // 40

    // H range of white

    const int min_white = 0;   // 15
    const int max_white = 30;  // 40

    Mat src_hsv;
    cvtColor(src,src_hsv,CV_BGR2HSV);
    imshow("cvtColor ---> src_hsv",src_hsv);
    waitKey(0);

    std::vector<Mat> hsvSplit;
    split(src_hsv,hsvSplit);
    for(int i=0;i<hsvSplit.size();++i)
    {

    }

}
