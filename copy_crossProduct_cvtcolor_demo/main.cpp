#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src1,copySrc;
    src1 = imread("../data/test1.jpg");
    src1.copyTo(copySrc);
    imshow("src1",src1);
    imshow("src copy",copySrc);
    vector<Mat> c;
    split(src1,c);
//    IplImage *p = &IplImage(src1);
//    p = cvCloneImage(p);
//    cout<< cvCountNonZero(p)<<endl;
//    cout<< countNonZero(src1)<<endl;//! error: only support 1 channel.
    cout<< countNonZero(c[0])<<endl;//! only support 1 channel.

    Mat ar1=
    (Mat_<int>(3,1) <<
                        1,
                        1,
                        1);
    Mat ar2=
    (Mat_<int>(3,1) <<
                        1,
                        1,
                        1);
    cout<<ar1.cross(ar2)<<endl;
    Point3d p1(1,1,1);
    Point3d p2(1,-1,2);
    cout<<p1.cross(p2)<<endl;

    Mat sr,OUT;
    sr = imread("../data/test_2gray.jpg");
    sr.convertTo(OUT,CV_8UC1);
    imshow("pangpang1",OUT);
    cout<<sr.channels()<<"---"<<endl;
    Mat color1;
    if(OUT.type()==CV_8UC1)//! NOTE
    {
        cvtColor(OUT,color1,CV_GRAY2BGR);
        imshow("pangpang",OUT);
    }
    waitKey(0);
    return 0;
}
