#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src,dst,output;
    Mat srcROI;
    src = imread("../data/test1.jpg");
    dst = imread("../data/190_170.jpg");
    cout<<src.type()<<endl;
    cout<<dst.type()<<endl;
    cout<<src.channels()<<endl;
    cout<<dst.channels()<<endl;


    srcROI = src(Rect(220,90,190,170));
    addWeighted(srcROI,0.4,dst,0.6,0.0,srcROI);


    namedWindow("src img");
    namedWindow("dst img");
    namedWindow("complex");
    imshow("src img",src);
    imshow("dst img",dst);
//    imshow("complex",output);

    waitKey(0);
    return 0;
}
