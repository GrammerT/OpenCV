#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src;
    src = imread("../data/test1.jpg");
    int x = 203;
    int y = 104;
    int width = 190;
    int height = 170;
    int add = 210;
    IplImage *pSrc = cvCloneImage(&IplImage(src));
    cvSetImageROI(pSrc,cvRect(x,y,width,height));
    cvAddS(pSrc,cvScalar(add),pSrc);
    cvResetImageROI(pSrc);
    cvNamedWindow("roi demo");
    cvShowImage("roi demo",pSrc);
    waitKey(0);
    return 0;
}
