#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;
#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"

int main(int argc, char *argv[])
{
    Mat grad_x,grad_y;
    Mat grad_xy;
    Mat abs_grad_x,abs_grad_y;
    String src_path;
    src_path+=DATA_PATH;
    src_path+="test1.jpg";
    Mat src = imread(src_path);
    Scharr(src,grad_x,CV_16S,1,0,1,0);
    convertScaleAbs(grad_x,abs_grad_x);
    imshow("grad_x",abs_grad_x);
    Scharr(src,grad_y,CV_16S,0,1,1,0);
    convertScaleAbs(grad_y,abs_grad_y);
    imshow("grad_y",abs_grad_y);

    addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,grad_xy);
    imshow("grad_xy",grad_xy);



    waitKey(0);
    return 0;
}
