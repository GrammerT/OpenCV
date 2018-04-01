#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src1,src2;
    src1 = imread("../data/test1.jpg");
    src2 = imread("../data/dog.jpg");
    vector<Mat> v_src1;
    vector<Mat> v_src2;

    split(src1,v_src1);
    split(src2,v_src2);
    vector<Mat> src;
    src.push_back(v_src1[0]);
    src.push_back(v_src1[1]);
    src.push_back(v_src2[0]);
    src.push_back(v_src2[2]);
    Mat dst;
    merge(src,dst);
    cout<<src1.channels()<<"----"<<src1.type()<<endl;
    cout<<dst.channels()<<"----"<<dst.type()<<endl;
    imshow("merge demo",dst);
    waitKey(0);
    return 0;
}
