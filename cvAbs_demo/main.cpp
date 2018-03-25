#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat m = Mat::ones(4,3,CV_8U);
    m.at<char>(1,1)=-4;
    cout<<m<<std::flush<<endl;
    Mat m1 = Mat::ones(4,3,CV_8S);
    m1.at<char>(1,1)=-4;
    cout<<m1<<std::flush<<endl;
    cout<<std::flush;
    cout<<std::flush;
    cout<<std::flush;
    waitKey(0);
    return 0;
}
