#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

void mat_open(Mat &src,Mat &dst);
void mat_close(Mat &src,Mat &dst);
void mat_morphological_radient(Mat &src,Mat &dst);
void top_hat(Mat &src,Mat &dst);
void black_hat(Mat &src,Mat &dst);


int main(int argc, char *argv[])
{
    Mat src_open = imread("../data/advanced_morphology.png");
    if(src_open.empty())
    {
        cout<<"src open error..."<<endl;
        return 0;
    }
    Mat dst_open;
    //! start open function.
    mat_open(src_open,dst_open);
    imshow("src_open demo",src_open);
    imshow("dst_open demo",dst_open);

    Mat dst_close;
    mat_close(src_open,dst_close);
    imshow("dst_close demo",dst_close);

    Mat src_gradient;
//    src_gradient = imread("../data/advanced_morphology_gradient.png");
    Mat dst_gradient;
    mat_morphological_radient(src_open,dst_gradient);
    imshow("dst_gradient demo",dst_gradient);

    Mat dst_topHat;
    Mat src_tophat;
    src_tophat = imread("../data/test1.jpg");
    top_hat(src_tophat,dst_topHat);
    imshow("dst top_hat",dst_topHat);


    Mat dst_blackhat;
//    black_hat(src_tophat,dst_blackhat);
    black_hat(src_open,dst_blackhat);

    imshow("dst black hat",dst_blackhat);
    waitKey(0);
    return 0;
}


void mat_open(Mat &src,Mat &dst)
{
    Mat element = getStructuringElement(MORPH_RECT,Size(11,11));
    erode(src,dst,element);
    dilate(dst,dst,element);
}


void mat_close(Mat &src,Mat &dst)
{
    Mat element = getStructuringElement(MORPH_RECT,Size(11,11));
    dilate(src,dst,element);
    erode(dst,dst,element);
}


void mat_morphological_radient(Mat &src,Mat &dst)
{
    Mat element = getStructuringElement(MORPH_RECT,Size(3,3));
    Mat dst1;
    erode(src,dst,element);
    dilate(src,dst1,element);
    dst=dst1-dst;
}


void top_hat(Mat &src,Mat &dst)
{
    mat_open(src,dst);
    dst=src-dst;
}


void black_hat(Mat &src,Mat &dst)
{
    mat_close(src,dst);
    dst = dst-src;
}
