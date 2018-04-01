#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src;
    src=imread("../data/dog.jpg");
    imshow("src",src);
    Mat dog = imread("../data/test1.jpg");
    dog = src-dog;
    imshow("sub mat demo",dog);
    Mat dst;
    dst=src-220;
    imshow("sub demo",dst);
    setIdentity(src);
    imshow("identity demo",src);
    Mat a=(Mat_<int>(3,8)<<1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12);
    setIdentity(a);
    cout<<a<<endl;


    waitKey(0);
    return 0;
}
