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
    Mat src;
    String src_path;
    src_path+=DATA_PATH;
    src_path += "test1.jpg";
    src = imread(src_path);

    if(src.empty())
    {
        cout<<"open error.."<<endl;
        return 0;
    }
    Mat out_3_3;
    blur(src,out_3_3,Size(3,3));
    imshow("src",src);
    imshow("out_3_3",out_3_3);
    Mat out_5_5;
    blur(src,out_5_5,Size(5,5));
    imshow("out_5_5",out_5_5);
    Mat midOut;
    medianBlur(src,midOut,5);
    imshow("midOut",midOut);
    Mat gauOutMat;
    GaussianBlur(src,gauOutMat,Size(9,9),3,8);
    imshow("gauOutMat",gauOutMat);
    Mat bilateralMat;
    bilateralFilter(src,bilateralMat,25,25*2,25/2);
    imshow("bilateralMat",bilateralMat);

    waitKey(0);
    return 0;
}
