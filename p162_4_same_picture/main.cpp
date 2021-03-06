#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;

//#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"
#define DATA_PATH "..\\data\\"


int main(int argc, char *argv[])
{
    Mat src1,src2;
    String src_path1,src_path2;
    src_path1+=DATA_PATH;
    src_path1 += "162_4_demo1.jpg";
    src_path2+=DATA_PATH;
    src_path2 += "162_4_demo2.jpg";
    src1 = imread(src_path1);
    if(src1.empty())
    {
        cout<<"src1 error..."<<endl;
        return 0;
    }
    src2 = imread(src_path2);
    if(src2.empty())
    {
        cout<<"src2 error..."<<endl;
        return 0;
    }
    imshow("src1 demo",src1);
    imshow("src2 demo",src2);
    Mat diff_a;
    absdiff(src1,src2,diff_a);
    imshow("diff_a",diff_a);

    Mat diff_b;
    Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3));
    erode(diff_a,diff_b,kernel);
    dilate(diff_b,diff_b,kernel);
    imshow("cleandiff diff_b",diff_b);


    Mat diff_c;
    dilate(diff_a,diff_c,kernel);
    erode(diff_c,diff_c,kernel);
    imshow("dirty diff_c",diff_c);

    waitKey(0);
















    return 0;
}
