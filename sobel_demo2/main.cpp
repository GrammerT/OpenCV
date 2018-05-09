#include <iostream>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;

//#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"
#define DATA_PATH "..\\data\\"

int main(int argc, char *argv[])
{
    Mat grad_x,grad_y;
    Mat abs_grad_x,abs_grad_y,dst;
    String src_path;
    src_path+=DATA_PATH;
    src_path+="test1.jpg";
    Mat src = imread(src_path);
    if(src.empty())
    {
        cout<<"src error...\n";
        return 0;
    }
    imshow("src demo",src);
    Sobel(src,grad_x,CV_16S,1,0,3,4,1,BORDER_DEFAULT);
    convertScaleAbs(grad_x,abs_grad_x);
    imshow("x ---->sobel",abs_grad_x);
    Sobel(src,grad_y,CV_16S,0,1,3,1,1,BORDER_DEFAULT);
    convertScaleAbs(grad_y,abs_grad_y);
    imshow("y ---->sobel",abs_grad_y);
    addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst);
    imshow("dst demo x&y",dst);
    waitKey(0);
    return 0;
}
