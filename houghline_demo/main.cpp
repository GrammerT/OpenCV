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

    String srcpath = DATA_PATH;
    //! line
//    srcpath+="162_4_demo1.jpg";
    //! circle
    srcpath+="test_circles.jpg";
    Mat srcImage = imread(srcpath);
    imshow("src demo",srcImage);
    if(srcImage.empty())
    {
        cout<<"src image error..."<<endl;
        return 0 ;
    }
    Mat midImage,dstImage;
    Canny(srcImage,midImage,50,200);
    imshow("midImage demo",midImage);
    waitKey(0);
    //! houghlines demo
    /*
    cvtColor(midImage,dstImage,CV_GRAY2BGR);
    imshow("dstImage demo",dstImage);

    waitKey(0);
    vector<Vec2f> lines;
    HoughLines(midImage,lines,1,CV_PI/180,150,0,0);
    for(int i=0;i<lines.size();++i)
    {
        float rho = lines[i][0],theta=lines[i][1];
        Point pt1,pt2;
        double a = cos(theta),b=sin(theta);
        double x0=a*rho,y0=b*rho;
        pt1.x=cvRound(x0+1000*(-b));
        pt1.y=cvRound(y0+1000*(a));
        pt2.x=cvRound(x0-1000*(-b));
        pt2.y=cvRound(y0-1000*(a));
        line(dstImage,pt1,pt2,Scalar(55,100,195),1,CV_AA);
        imshow("dstImage line",dstImage);
        waitKey(0);
    }
    imshow("end dstImage line",dstImage);
    waitKey(0);
    */
    //! end
    //! houghlinesp demo
    //!
    /*
    vector<Vec4i> plines;
    HoughLinesP(midImage,plines,1,CV_PI/180,80,50,10);
    for(int i=0;i<plines.size();++i)
    {
        line(midImage, Point(plines[i][0],plines[i][1]),Point(plines[i][2],plines[i][3]),Scalar(55,100,195),8);
        imshow("HoughLinesP srcImage",midImage);
        waitKey(0);
    }
    waitKey(0);
    */
    //! end
//    HoughCircles demo
    cvtColor(srcImage,midImage,CV_BGR2GRAY);
    GaussianBlur(midImage,dstImage,Size(9,9),2,2);

    vector<Vec3f> circles;
    HoughCircles(midImage,circles,CV_HOUGH_GRADIENT,1.5,10,
                 200,100,0,0);
    for(int i=0;i<circles.size();++i)
    {
        Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        circle(srcImage,center,3,Scalar(0,255,0),-1,8,0);
        circle(srcImage,center,radius,Scalar(155,50,255),3,8,0);
        imshow("dst image",srcImage);
        waitKey(0);
    }
    imshow("dst image",srcImage);
    waitKey(0);
    return 0;
}
