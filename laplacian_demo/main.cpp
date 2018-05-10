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
    Mat src,src_gray,dst,abs_dst;
    String src_path;
    src_path+=DATA_PATH;
//    src_path+="test1.jpg";
//    src_path+="Back_Projection_Theory0.jpg";
    src_path+="dog.jpg";

    src=imread(src_path);
    imshow("src_demo",src);
    GaussianBlur(src,src,Size(3,3),0,0);
    imshow("src_gau_demo",src);
    cvtColor(src,src_gray,CV_RGB2GRAY);
    imshow("src_gray demo",src_gray);
    Laplacian(src_gray,dst,CV_16S,3,1,0);
    imshow("dst demo",dst);
    convertScaleAbs(dst,abs_dst);
    imshow("abs_dst",abs_dst);
    waitKey(0);
    return 0;
}
