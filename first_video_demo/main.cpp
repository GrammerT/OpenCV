#include <iostream>
#include "opencv2/video.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;


void onCaptureFrame(int pos,void* userdata);

int main(int argc, char *argv[])
{
    String filename("../data/test_video.mp4");
    VideoCapture capture(filename);
    if(!capture.isOpened())
    {
        cout<<"open error"<<endl;
        return -1;
    }
    //! get video's info
    double rate = capture.get(CV_CAP_PROP_FPS);
    int total =capture.get(CV_CAP_PROP_FRAME_COUNT);
    cout<<"rate : "<<rate<<endl;
    cout<<"total : "<<total<<endl;

    Mat frame;
    namedWindow("video demo");
    createTrackbar("position","video demo",0,total,onCaptureFrame,(void*)&capture);
    double position = 0;
    capture.set(CV_CAP_PROP_POS_FRAMES,position);
    Mat r_frame;
    Mat detect_edges;

    while(1)
    {
        if(!capture.read(frame))
            break;
        setTrackbarPos("position","video demo",capture.get(CV_CAP_PROP_POS_FRAMES));
        Size size(frame.size());
        resize(frame,r_frame,size);
        cvtColor(r_frame,detect_edges,COLOR_RGB2GRAY);
        Canny(detect_edges,detect_edges,30,90);
        imshow("video demo",detect_edges);
        char c = waitKey(20);
        if(c==27)
            break;
    }
    return 0;
}


void onCaptureFrame(int pos, void *userdata)
{
    VideoCapture *capture = reinterpret_cast<VideoCapture*>(userdata);
    capture->set(CV_CAP_PROP_POS_FRAMES,pos);
}
