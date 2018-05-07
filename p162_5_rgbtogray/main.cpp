#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

//#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"
#define DATA_PATH "..\\data\\"


int main(int argc, char *argv[])
{
    Mat src1;
    Mat src2;
    String src_path1;
    src_path1+=DATA_PATH;
    src_path1+="p163_5_rgbtogray.jpg";
    src1 = imread(src_path1);
    if(src1.empty())
    {
        cout<<"src1 error..."<<endl;
        return 0;
    }
    String src_path2;
    src_path2+=DATA_PATH;
    src_path2+="p163_5_rgbtogray_1.jpg";
    src2 = imread(src_path2);
    if(src2.empty())
    {
        cout<<"src2 error..."<<endl;
        return 0;
    }

    cvtColor(src1,src1,COLOR_RGB2GRAY);
    cvtColor(src2,src2,COLOR_RGB2GRAY);

    imshow("src1 demo",src1);
    imshow("src2 demo",src2);
    Mat diff_a;
    absdiff(src1,src2,diff_a);
    imshow("diff_a",diff_a);

    double minv;
    double maxv;
    minMaxLoc(diff_a,&minv,&maxv);
    Mat diff_b;
    threshold(diff_a,diff_b,0,255,THRESH_BINARY);

    imshow("diff_b",diff_b);
    Mat diff_c;
    Mat ker = getStructuringElement(MORPH_RECT,Size(3,3));
    morphologyEx(diff_a,diff_c,CV_MOP_OPEN,ker);

    imshow("diff_c",diff_c);
    waitKey(0);
    return 0;
}
