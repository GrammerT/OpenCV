#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;

void Sharpen(const Mat &myImage,Mat &Result);

int main(int argc, char *argv[])
{
    const char *fileName = "F:\\openCV\\workspace\\Tests\\data\\test.jpg";
    Mat src,dst0,dst1;
    src = imread(fileName);
    if(src.empty())
    {
        cout<<"Can't open image...";
        return -1;
    }
    namedWindow("Input",WINDOW_AUTOSIZE);
    namedWindow("Output",WINDOW_AUTOSIZE);
    namedWindow("Output1",WINDOW_AUTOSIZE);
    imshow("Input",src);
    double t =(double)getTickCount();
    Sharpen(src,dst0);
    t = ((double)getTickCount()-t)/getTickFrequency();
    cout<<"Hand written function time passed in seconds: "<<t<<endl;
    imshow("Output",dst0);

    Mat kernel = (Mat_<char>(3,3)<<0,-1,0,
                                                             -1,6,-1,
                                                               0,-1,0);
    t = (double)getTickCount();
    filter2D(src,dst1,src.depth(),kernel);
    t = ((double)getTickCount()-t)/getTickFrequency();
    cout<<"filter2D function time passed in seconds: "<<t<<endl;
    imshow("Output1",dst1);
    waitKey();
    return 0;
}


void Sharpen(const Mat &myImage,Mat &Result)
{
    CV_Assert(myImage.depth()==CV_8U);
    const int nChannels = myImage.channels();
    Result.create(myImage.size(),myImage.type());
    for(int j=1;j<myImage.rows-1;++j)
    {
        const uchar *previous = myImage.ptr<uchar>(j-1);
        const uchar *current = myImage.ptr<uchar>(j);
        const uchar *next = myImage.ptr<uchar>(j+1);
        uchar *output = Result.ptr<uchar>(j);
        for(int i=nChannels;i<nChannels*(myImage.cols-1);++i)
        {
            *output++ = saturate_cast<uchar>(
                        5*current[i]-current[i-nChannels]-
                        current[i+nChannels]-previous[i]-next[i]);
        }
    }
    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows-1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols-1).setTo(Scalar(0));
}
