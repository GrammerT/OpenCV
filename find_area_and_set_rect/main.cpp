#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;
#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"

int main(int argc, char *argv[])
{
    String img_path;
    img_path+=DATA_PATH;
    img_path+="162_4_demo2.jpg";
    Mat image = imread(img_path);
    imshow("image src",image);
    Mat gray(image.size(),CV_8U);
    cvtColor(image,gray,CV_RGB2GRAY);
    imshow("image gray",gray);
    threshold(gray,gray,128,255,THRESH_BINARY);
    imshow("gray_binary",gray);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(gray,
                 contours,
                 hierarchy,
                 CV_RETR_EXTERNAL,
                 CV_CHAIN_APPROX_NONE);
    Mat result(gray.size(),CV_8U,Scalar(255));
    int index = 0;
    for(;index>=0;index=hierarchy[index][0])
    {
        Scalar color(rand()&255,rand()&255,rand()&255);
        drawContours(result,contours,index,Scalar(0),1,8,hierarchy);
        Rect rect=boundingRect(contours[index]);
        rectangle(result,rect,Scalar(0,0,255),3);
    }
    imshow("result demo",result);
    Mat original=imread(img_path);
    index=0;
    for(;index>=0;index=hierarchy[index][0])
    {
        Scalar color(rand()&255,rand()&255,rand()&255);
        drawContours(original,contours,index,Scalar(255),1,8,hierarchy);
        Rect rect=boundingRect(contours[index]);
        rectangle(original,rect,Scalar(0,0,255),3);
    }
    imshow("original demo",original);

    waitKey(0);
    return 0;
}
