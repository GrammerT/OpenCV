#include <iostream>
#include"opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src = imread("../data/test1.jpg");
    imshow("src",src);
    IplImage *pSrc = (&IplImage(src));
    CvScalar cs = cvAvg(pSrc);//!
    cout<<cs.val[0]<<endl; //！ R of mean
    cout<<cs.val[1]<<endl;//!       G of mean
    cout<<cs.val[2]<<endl;//!       B of mean
    cout<<cs.val[3]<<endl;//!       A of mean

    waitKey(0);
    return 0;
}
