#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src = imread("../data/test1.jpg");
    //! line demo
    int linetype[4]={-1,4,8,16};
//    FILLED  = -1,
//    LINE_4  = 4, //!< 4-connected line
//    LINE_8  = 8, //!< 8-connected line
//    LINE_AA = 16 //!< antialiased line
    for(int i=0;i<32;++i)
    {
        int j=i%4;
        Mat re ;
        src.copyTo(re);
        line(re,Point(0+i,0+i),Point(i+20,i+20),Scalar(255,0,0),20,linetype[j]);
        imshow("line demo",re);
        waitKey(500);
    }
    //! end line
    //! circle demo

    for(int i=0;i<32;++i)
    {
        Mat re;
        src.copyTo(re);
        circle(re,Point(re.rows/2,re.cols/2),i,Scalar(i+32,58-i,i),i%6,linetype[i%4]);
        imshow("circle demo",re);
        waitKey(500);
    }
    //! end circle
    waitKey(0);
    return 0;
}
