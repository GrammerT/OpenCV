#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
    // Declare the variables we are going to use;
    Mat src,src_gray,dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    const char *window_name = "laplace demo ";
    const char *imagename = "../data/test1.jpg";
    src = imread(imagename,IMREAD_COLOR);
    if(src.empty())
    {
        cout<<"image error...";
        return -1;
    }
    GaussianBlur(src,dst,Size(3,3),0,0,BORDER_DEFAULT);
    cvtColor(src,src_gray,COLOR_BGR2GRAY);
    Mat abs_dst;
    Laplacian(src_gray,dst,ddepth,kernel_size,scale,delta,BORDER_DEFAULT);

    convertScaleAbs(dst,abs_dst);
    imshow(window_name,abs_dst);
    waitKey(0);
    return 0;
}
