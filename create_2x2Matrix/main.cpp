#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
using namespace std;
using namespace cv;



int main(int argc, char *argv[])
{
    /**
     * to do : create a 2D Matrix(100*100) that have 3 channels.
     * @return
     */
    Mat src;
    Mat _src;
    src.create(100,100,CV_8UC3);
    src =Mat::zeros(src.size(),CV_8UC3);
    src.copyTo(_src);
    cout<<src.channels()<<endl;
    cout<<src.dims<<endl;
    imshow("zeros img",src);
//    waitKey(0);
    /**
     * to do : create a 2D Matrix(100*100) that have 3 channels.
     *          draw a rectangle top-left(20,5) and bottom-right(40,20)
     * @return
     */
    rectangle(src,Point(20,5),Point(40,20),Scalar(0,255,0),3);
    imshow("rect in Mat",src);
    /**
     * to do : create a 2D Matrix(100*100) that have 3 channels.
     *          draw a rectangle area top-left(20,5) and bottom-right(40,20)
     * @return
     */
    vector<Point> v_point;
    v_point.push_back(Point(20,5));
    v_point.push_back(Point(40,5));
    v_point.push_back(Point(40,20));
    v_point.push_back(Point(20,20));
    Point points[1][4];
    points[0][0] = Point( 20,5 );
    points[0][1] = Point( 40,5 );
    points[0][2] = Point( 40,20 );
    points[0][3] = Point( 20,20);
    const Point *pt[1] = {points[0]};
    int count[1] = {4};
    fillPoly(_src,pt,count,1,Scalar(0,255,0),LINE_8);
    imshow("area in Mat",_src);
    /**
     * to do : create a 2D Matrix(800*800) that have 1 channels.
     *          use ROI and set() function create a pyramid
     * @return
     */
    Mat roi_src;
    roi_src.create(210,210,CV_8UC1);
    roi_src = Mat::ones(roi_src.size(),CV_8UC1);
    int mid = roi_src.cols/2;
    int width = 10;
    for(int row=0;row<roi_src.rows;row+=10)
    {
        Rect rect1(mid-width/2,row,width,10);
        width+=10;
        rectangle(roi_src,rect1,Scalar(255,0,0),1);
    }
    imshow("ROI DEMO",roi_src);
    waitKey(0);
    return 0;
}
