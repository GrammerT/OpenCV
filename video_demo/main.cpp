#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;

double getPSNR(const Mat& I1, const Mat& I2);
Scalar getMSSIM(const Mat& I1, const Mat& I2);

int main(int argc, char *argv[])
{

    stringstream conv;
    const string sourceReference = "../data/Megamind.avi";
    const string sourceCompareWith = "../data/Megamind_bugy.avi";
    int psnrTriggerValue,delay;
    psnrTriggerValue = 1;
    delay = 1;
    int frameNum = -1;
     VideoCapture captRefrnc(sourceReference);
     VideoCapture captUndTst(sourceCompareWith);
    if(!captRefrnc.isOpened())
    {
        cout<<"refrnc open error..."<<endl;
        return -1;
    }
    if(!captUndTst.isOpened())
    {
        cout<<"captUndTst open error..."<<endl;
        return -1;
    }

    Size refS = Size((int)captRefrnc.get(CAP_PROP_FRAME_WIDTH),
                                (int)captRefrnc.get(CAP_PROP_FRAME_HEIGHT));
    Size utSi = Size((int)captUndTst.get(CAP_PROP_FRAME_WIDTH),
                                (int)captUndTst.get(CAP_PROP_FRAME_HEIGHT));
    if(refS!=utSi)
    {
        cout << "Inputs have different size!!! Closing." << endl;
        return -1;
    }

    const char* WIN_UT = "Under Test";
    const char* WIN_RF = "Reference";

    // Windows
    namedWindow(WIN_RF, WINDOW_AUTOSIZE);
    namedWindow(WIN_UT, WINDOW_AUTOSIZE);
    moveWindow(WIN_RF, 400    , 0);         //750,  2 (bernat =0)
    moveWindow(WIN_UT, refS.width, 0);         //1500, 2


    cout << "Reference frame resolution: Width=" << refS.width << "  Height=" << refS.height
         << " of nr#: " << captRefrnc.get(CAP_PROP_FRAME_COUNT) << endl;
    cout << "PSNR trigger value " << setiosflags(ios::fixed) << setprecision(3)
         << psnrTriggerValue << endl;
    Mat frameReference,frameUnderTest;
    double psnrV;
    Scalar mssimV;

    for(;;)
    {
        captRefrnc>>frameReference;
        captUndTst>>frameUnderTest;
        if(frameReference.empty()||frameUnderTest.empty())
        {
            cout<<"Game over...."<<endl;
            break;
        }
        ++frameNum;
    }


    return 0;
}



double getPSNR(const Mat& I1, const Mat& I2)
{
    return 0;
}

Scalar getMSSIM(const Mat& I1, const Mat& I2)
{
    return Scalar(0,0,0);
}
