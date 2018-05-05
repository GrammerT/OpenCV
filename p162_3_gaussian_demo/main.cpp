#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src;
    src = imread("../data/test1.jpg");
    if(src.empty())
    {
        cout<<"src error..."<<endl;
        return 0;
    }
    imshow("src demo",src);
    Mat dst_a;
    GaussianBlur(src,dst_a,Size(9,9),1);
    imshow("dst demo a1",dst_a);
    GaussianBlur(src,dst_a,Size(9,9),4);
    imshow("dst demo a4",dst_a);
    GaussianBlur(src,dst_a,Size(9,9),146);
    imshow("dst demo a6",dst_a);

    Mat dst_b;
    GaussianBlur(src,dst_b,Size(0,0),1);
    imshow("dst demo b1",dst_b);
    GaussianBlur(src,dst_b,Size(0,0),4);
    imshow("dst demo b4",dst_b);
    GaussianBlur(src,dst_b,Size(0,0),6);
    imshow("dst demo b6",dst_b);

    Mat dst_c;
    GaussianBlur(src,dst_c,Size(0,0),1,9);
    imshow("dst demo c1_4",dst_c);

    Mat dst_d;
    GaussianBlur(src,dst_d,Size(0,0),9,1);
    imshow("dst demo d9_1",dst_d);

    Mat dst_e;
    GaussianBlur(src,dst_e,Size(0,0),1,9);
    GaussianBlur(dst_e,dst_e,Size(0,0),9,1);
    imshow("dst demo e1_9",dst_e);

    Mat dst_f;
    Mat dst_f1;
    GaussianBlur(src,dst_f,Size(0,0),9,9);
    GaussianBlur(dst_f,dst_f1,Size(0,0),0,0);
    imshow("dst demo f1_9",dst_f1);

    waitKey(0);
    return 0;
}
