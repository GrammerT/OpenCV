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

    //! cvAvgSdv can calculate the mean and Standard deviation
    CvScalar mean,deviation;
    cvAvgSdv(pSrc,&mean,&deviation);
    cout<<mean.val[0]<<endl; //！ R of mean
    cout<<mean.val[1]<<endl;//!       G of mean
    cout<<mean.val[2]<<endl;//!       B of mean
    cout<<mean.val[3]<<endl;//!       A of mean
    cout<<deviation.val[0]<<endl; //！ R of  Standard deviation
    cout<<deviation.val[1]<<endl;//!       G of  Standard deviation
    cout<<deviation.val[2]<<endl;//!       B of  Standard deviation
    cout<<deviation.val[3]<<endl;//!       A of  Standard deviation
    waitKey(0);
    return 0;
}
