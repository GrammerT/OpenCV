#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{

    Mat a;
    a.create(3,4,CV_8U);
    a=(Mat_<uchar>(3,4)<<1,2,3,4,5,6,7,8,9,10,11,12);
    Mat a1;
    a1.create(a.size(),CV_32S);
    cout<<a<<endl;
    cout<<flush;
    //! it's important to set Mat's type. such as : CV_32S && CV_8U
    reduce(a,a1,1,CV_REDUCE_SUM,CV_32S);
    cout<<a1<<endl;
    cout<<flush;
    a1.create(a.size(),CV_8U);
    reduce(a,a1,1,CV_REDUCE_MAX,CV_8U);
    cout<<a1<<endl;
    cout<<flush;
    a1.create(a.size(),CV_32S);
    reduce(a,a1,1,CV_REDUCE_AVG,CV_32S);
    cout<<a1<<endl;
    cout<<flush;
    a1.create(a.size(),CV_8U);
    reduce(a,a1,1,CV_REDUCE_MIN,CV_8U);
    cout<<a1<<endl;
    cout<<flush;
    //! end reduce;
    //! start repeat
    Mat src1,src2;
    src1=imread("../data/test1.jpg");
    src2= imread("../data/190_170.jpg");
    repeat(src2,3,5,src1);
    imshow("repeat demo",src1);
    //! end repeat

    src1 = imread("../data/dog.jpg");
    src1.convertTo(src1,CV_32F);
    src1.convertTo(src1,CV_8U);
    src1.convertTo(src1,CV_32S);
    imshow("SCALE demo",src1);

    waitKey(0);
    return 0;
}
