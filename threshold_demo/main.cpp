#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int threshold_type;
int maxValue;

int main(int argc, char *argv[])
{
    Mat src = imread("../data/test1.jpg");
    Mat dst;
    if(src.empty())
    {
        cout<<"image error..."<<endl;
        return 0;
    }
    imshow("src demo",src);

    while(waitKey(9)!='q')
    {
        threshold(src,dst,100,150,THRESH_BINARY);

    }
    return 0;
}
