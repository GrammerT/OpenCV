#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;

Mat g_srcImage,g_dstImage;
int g_nTrackbarNum=0;
int g_nStructElementSize = 3;

void process();
void on_trackbarNumChanged(int ,void *);
void on_elementSizeChanged(int , void *);


int main(int argc, char *argv[])
{
    g_srcImage = imread("../data/test1.jpg");
    if(g_srcImage.empty())
    {
        cout<<"src image error...";
        return 0;
    }
    namedWindow("src demo");
    imshow("src demo",g_srcImage);

    namedWindow("dst demo");
    Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),
                                        Point(g_nStructElementSize,g_nStructElementSize));
    erode(g_srcImage,g_dstImage,element);
    imshow("dst demo",g_dstImage);

    createTrackbar("erode/dilation","dst demo",&g_nTrackbarNum,1,on_trackbarNumChanged);

    createTrackbar("element","dst demo",&g_nStructElementSize,21,on_elementSizeChanged);

    while(char(waitKey(1))!='q'){

    }

    return 0;
}


void process()
{
    Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),
                                        Point(g_nStructElementSize,g_nStructElementSize));
    if(g_nTrackbarNum==0)
    {
        erode(g_srcImage,g_dstImage,element);
    }
    else
    {
        dilate(g_srcImage,g_dstImage,element);
    }
    imshow("dst demo" ,g_dstImage);
}

void on_trackbarNumChanged(int ,void *)
{
    process();
}

void on_elementSizeChanged(int , void *)
{
    process();
}
