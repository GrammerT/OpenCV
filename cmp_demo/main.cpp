#include <iostream>
#include"opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src;
    vector<Mat> channels;
    src = imread("../data/test1.jpg");
    if(src.channels()>1)
    {
        split(src,channels);
    }
    else
    {
        channels[0]=src.clone();
    }
    for(int i=0;i<src.channels();++i)
    {
//        imshow("channel"+i,channels[i]);
    }
    imshow("src",channels[0]);
    IplImage *pimg = &IplImage(channels[0]);
    IplImage *pimg1 = cvCloneImage(pimg);
    cvCmpS(pimg,100,pimg1,CV_CMP_EQ);
    Mat c1 = cvarrToMat(pimg1);
    imshow("CV_CMP_EQ",c1);
    cvCmpS(pimg,20,pimg1,CV_CMP_GT);
    Mat c2 = cvarrToMat(pimg1);
    imshow("CV_CMP_GT",c2);
    cvCmpS(pimg,40,pimg1,CV_CMP_GE);
    Mat c3 = cvarrToMat(pimg1);
    imshow("CV_CMP_GE",c3);
    cvCmpS(pimg,200,pimg1,CV_CMP_LT);
    Mat c4 = cvarrToMat(pimg1);
    imshow("CV_CMP_LT",c4);
    cvCmpS(pimg,150,pimg1,CV_CMP_LE);
    Mat c5 = cvarrToMat(pimg1);
    imshow("CV_CMP_LE",c5);
    cvCmpS(pimg,100,pimg1,CV_CMP_NE);
    Mat c6 = cvarrToMat(pimg1);
    imshow("CV_CMP_NE",c6);
    waitKey(0);
    return 0;
}
