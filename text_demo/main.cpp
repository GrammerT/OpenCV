#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat src;
    src = imread("../data/test1.jpg");
    putText(src,"OpenCV",Point(50,20),FONT_HERSHEY_SIMPLEX,1.0,Scalar(1.0,0,0));
    putText(src,"OpenCV",Point(50,40),FONT_HERSHEY_PLAIN,1.0,Scalar(1.0,0,0));
    putText(src,"OpenCV",Point(50,60),FONT_HERSHEY_DUPLEX,1.0,Scalar(1.0,0,0));
    putText(src,"OpenCV",Point(50,80),FONT_HERSHEY_COMPLEX,1.0,Scalar(1.0,0,0));
    putText(src,"OpenCV",Point(50,100),FONT_HERSHEY_TRIPLEX,1.0,Scalar(1.0,0,0));

    imshow("src",src);
    waitKey(0);
    return 0;
}
