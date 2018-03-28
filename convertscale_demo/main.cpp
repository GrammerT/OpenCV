#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src1,src2,output;
    src1 = imread("../data/test1.jpg");
    src2 = imread("../data/dog.jpg");
    cout<<src1.type()<<endl;
    cout<<src2.type()<<endl;
    cout<<src1.channels()<<endl;
    cout<<src2.channels()<<endl;
    IplImage *pimg = &IplImage(src1);
    IplImage *outp = cvCloneImage(pimg);
    cvConvertScale(pimg,outp,1,-60);//! pimg's pixel*2+(-40)
    Mat c1 = cvarrToMat(outp);
    imshow("src",src1);
    imshow("output",c1);

    //! ConvertScaleAbs() function.
    Mat c2;

    imshow("src2",src2);
    int i = 0;
    while(1)
    {
        convertScaleAbs(src2,c2,1,-(i%255));
        imshow("output1",c2);
        i++;
        waitKey(50);
    }

    waitKey(0);
    return 0;
}
