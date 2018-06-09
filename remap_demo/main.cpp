#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;
#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"
//#define DATA_PATH "..\\data\\"


int main(int argc, char *argv[])
{
    Mat srcImage,dstImage;
    Mat map_x,map_y;
    String filepath = String(DATA_PATH)+String("test1.jpg");
    srcImage=imread(filepath);
    if(srcImage.empty())
    {
        cout<<"src Error...."<<endl;
        return 0;
    }
    imshow("src demo",srcImage);

    dstImage.create(srcImage.size(),srcImage.type());
    map_x.create(srcImage.size(),CV_32FC1);
    map_y.create(srcImage.size(),CV_32FC1);

    for(int j=0;j<srcImage.rows;++j)
    {
        for(int i=0;i<srcImage.cols;++i)
        {
            map_x.at<float>(j,i)=static_cast<float>(i);
            map_y.at<float>(j,i)=static_cast<float>(srcImage.rows-j);
        }
    }

    remap(srcImage,dstImage,
          map_x,map_y,CV_INTER_LINEAR,
          BORDER_CONSTANT,Scalar(0,0,0));

    imshow("dst demo",dstImage);
    waitKey(0);
    return 0;
}
