#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
    double alpha = 0.5;
    double beta;
    double input;
    Mat src1,src2,dst;
    while(1)
    {
        cin>>input;
        if(input>=0&&input<=1)
        {
            alpha = input;
        }
        src1 = imread("F:\\openCV\\workspace\\Tests\\data\\test.jpg");
        src2 = imread("F:\\openCV\\workspace\\Tests\\data\\test1.jpg");
        cout<<src1.channels()<<endl;
        cout<<src2.channels()<<endl;
        if(src1.empty())
            return -1;
        if(src2.empty())
            return -1;
        beta = 1.0-alpha;
        addWeighted(src1,alpha,src2,beta,0.0,dst);
//        namedWindow("Linear Blend");
        imshow("Linear Blend",dst);
        waitKey(0);
    }
    return 0;
}
