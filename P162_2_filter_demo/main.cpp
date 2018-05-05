#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat demo;
    demo.create(Size(200,200),CV_8UC1);
    demo = Mat::zeros(demo.size(),CV_8UC1);
    demo.ptr<uchar>(100)[100]=255;
    imshow("demo",demo);
    Mat dst_5x5;
    GaussianBlur(demo,dst_5x5,Size(5,5),0,0);
    imshow("dst 5x5",dst_5x5);
    Mat dst_9x9;
    GaussianBlur(demo,dst_9x9,Size(9,9),0,0);
    imshow("dst 9x9",dst_9x9);

    Mat dst_5x5_2;
    GaussianBlur(dst_5x5,dst_5x5_2,Size(5,5),0,0);
    imshow("dst 5x5_2",dst_5x5_2);


    waitKey(0);
    return 0;
}
