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
    a = imread("../data/test1.jpg");
    for(int i=0;i<a.cols;++i)
    {
        int right = i+80;
        if(right>a.cols)
        {
            right = a.cols;
        }
        Mat col = a.colRange(i,right);
        imshow("col i",col);
        waitKey(30);
    }
    cout<<"dims--->"<<a.dims<<endl;
    cout<<"dims size--->"<<a.size()<<endl;

    for(int i=-100;i<100;++i)
    {
        Mat diag =  a.diag(i);
        imshow("diag i",diag);
        waitKey(20);
    }
    waitKey(0);
    return 0;
}
