#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat a(3,3,CV_32FC1);
    Mat b(3,3,CV_32FC1);
    a=(Mat_<float>(3,3)<<1.3,3.4,2.2,
                                        5,5,6,
                                        7,6,5);
    b=(Mat_<float>(3,3)<<1,1,0,
                                        1,6,0,
                                        0,0,3);

    cout<<a<<endl;
    cout<<b<<endl;
    cout<< determinant(a) <<endl;//!must have CV_32FC1 or CV_64FC1 type and square size

    Mat src1,src2;
    src1 = imread("../data/test1.jpg");
    src2 = imread("../data/dog.jpg");
    cout<<flush;
    cout<<a.dot(b)<<endl;

    Mat out1,out2;
    cout<<endl;
    eigen(b,out1,out2);
    cout<<out1<<endl;
    cout<<out2<<endl;

    cv::divide(src1,src2,src1);
    imshow("div demo",src1);

    Mat outsrc2;
    while(1)
    {
        flip(src2,outsrc2,0);
        imshow("outsrc2 demo",outsrc2); //! X
        waitKey(1000);
        flip(src2,outsrc2,-1); //! X-Y
        imshow("outsrc2 demo",outsrc2);
        waitKey(1000);
        flip(src2,outsrc2,1);//! Y
        imshow("outsrc2 demo",outsrc2);
        waitKey(1000);
    }

    waitKey(0);
    return 0;
}
