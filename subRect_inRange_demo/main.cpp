#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat a;
    a=imread("../data/test1.jpg");
    for(int i=0;i<a.cols;++i)
    {
//        Mat rect = a(Range(i,i+150),Range(i,i+150)); //! will crash.
//        imshow("rect demo",rect);
//        waitKey(20);
    }
    a.convertTo(a,CV_32F);
    imshow("convertTo demo",a);
//    Mat b;
////    b.create(4,3,CV_32F);
//    Mat invert_b;
//    invert_b.create(3,4,CV_32F);
    Mat b=(Mat_<float>(4,3)<<"1,0,0,  0,2,0, 0,0,3, 0,0,0");

    imshow("invert demo",b.inv());
    waitKey(0);
    return 0;
}
